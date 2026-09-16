#include <memory>

#include <pvxs/nt.h>
#include <pvxs/server.h>
#include <pvxs/sharedpv.h>

#include "exceptions.hpp"
#include "pva_labview_export.h"
#include "utils.hpp"

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
createServer(pvxs::server::Server** server, pvxs::server::StaticSource** source)
{
    return err2code([&] {
        *server = new pvxs::server::Server(pvxs::server::Server::fromEnv());
        *source =
          new pvxs::server::StaticSource(pvxs::server::StaticSource::build());
        (**server).addSource("labview", (**source).source());
    });
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
startServer(pvxs::server::Server* server)
{
    return err2code([&] {
        if (server == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        server->start();
    });
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
stopServer(pvxs::server::Server* server)
{
    return err2code([&] {
        if (server == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        server->stop();
    });
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
closeServer(pvxs::server::Server* server)
{
    return err2code([&] {
        if (server == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        server->stop();
        delete server;
    });
}

void
updateTimestamp(pvxs::Value& value)
{
    // If the timestamp has not been modified
    if (auto ts = value["timeStamp"]; !ts.isMarked(true, true)) {
        // Replace it with the current time
        if (epicsTimeStamp now; !epicsTimeGetCurrent(&now)) {
            ts["secondsPastEpoch"] =
              now.secPastEpoch + POSIX_TIME_AT_EPICS_EPOCH;
            ts["nanoseconds"] = now.nsec;
        }
    }
}

void
raiseAlarm(const pvxs::Value& value,
           const int32_t severity,
           const std::string& message)
{
    auto alarm = value.lookup("alarm");
    alarm["severity"] = severity;
    alarm["status"] = 0;
    alarm["message"] = message;
}

void
processAlarmLimits(const pvxs::Value& current, pvxs::Value& next)
{
    if (auto limits_field = current["valueAlarm"];
        limits_field && limits_field["active"].as<bool>()) {
        auto value = next.lookup("value").as<double>();

        if (auto severity =
              limits_field.lookup("highAlarmSeverity").as<int32_t>();
            severity > 0) {
            if (auto level = limits_field.lookup("highAlarmLimit").as<double>();
                value >= level) {
                return raiseAlarm(next, severity, "high alarm");
            }
        }
        if (auto severity =
              limits_field.lookup("lowAlarmSeverity").as<int32_t>();
            severity > 0) {
            if (auto level = limits_field.lookup("lowAlarmLimit").as<double>();
                value <= level) {
                return raiseAlarm(next, severity, "low alarm");
            }
        }
        if (auto severity =
              limits_field.lookup("highWarningSeverity").as<int32_t>();
            severity > 0) {
            if (auto level =
                  limits_field.lookup("highWarningLimit").as<double>();
                value >= level) {
                return raiseAlarm(next, severity, "high warning");
            }
        }
        if (auto severity =
              limits_field.lookup("lowWarningSeverity").as<int32_t>();
            severity > 0) {
            if (auto level =
                  limits_field.lookup("lowWarningLimit").as<double>();
                value <= level) {
                return raiseAlarm(next, severity, "low warning");
            }
        }
        return raiseAlarm(next, 0, "");
    }
}

void
processControlLimits(const pvxs::Value& current, pvxs::Value& next)
{
    if (auto control_field = current["control"]) {
        // Is the value field being changed?
        if (auto value_field = next["value"];
            value_field.isMarked(true, true)) {
            auto limit_low = control_field.lookup("limitLow").as<double>();
            auto limit_high = control_field.lookup("limitHigh").as<double>();
            // Do nothing unless the high limit is above the low
            if (limit_low < limit_high) {
                auto value = value_field.as<double>();
                if (value > limit_high) {
                    value_field = limit_high;
                } else if (value < limit_low) {
                    value_field = limit_low;
                }
            }
        }
    }
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
addPV(pvxs::server::StaticSource* source,
      const char pv_name[],
      pvxs::Value* value,
      const int16_t read_only)
{
    return err2code([&] {
        if (source == nullptr || value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);
        if (strlen(pv_name) == 0)
            throw labview::lv_err(PVALVError::empty_pv_name);

        std::unique_ptr<pvxs::Value> guard(value);
        auto pv{ pvxs::server::SharedPV::buildReadonly() };

        if (read_only == 0) {
            auto id = value->id();
            pv.onPut([id](pvxs::server::SharedPV& pv,
                          std::unique_ptr<pvxs::server::ExecOp>&& op,
                          pvxs::Value&& top) {
                updateTimestamp(top);
                if (id.starts_with("epics:nt/NTScalar:")) {
                    auto current = pv.fetch();
                    processControlLimits(current, top);
                    processAlarmLimits(current, top);
                }
                pv.post(top);
                op->reply();
            });
        }

        pv.open(*value);
        source->add(pv_name, pv);
    });
}

pvxs::server::SharedPV
getPV(pvxs::server::StaticSource* source, const std::string& pv_name)
{
    if (source == nullptr)
        throw labview::lv_err(PVALVError::null_ptr);

    auto pvs = source->list();
    if (pvs.find(pv_name) == pvs.end()) {
        throw labview::lv_err(PVALVError::server_post_pv_not_found);
    }
    return pvs[pv_name];
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
fetch(pvxs::server::StaticSource* source,
      const char pv_name[],
      pvxs::Value** value)
{
    return err2code([&] {
        if (source == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);
        if (strlen(pv_name) == 0)
            throw labview::lv_err(PVALVError::empty_pv_name);

        auto pv = getPV(source, pv_name);
        *value = new pvxs::Value{ pv.fetch() };
    });
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
post(pvxs::server::StaticSource* source,
     const char pv_name[],
     pvxs::Value* value)
{
    return err2code([&] {
        if (source == nullptr || value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);
        if (strlen(pv_name) == 0)
            throw labview::lv_err(PVALVError::empty_pv_name);

        std::unique_ptr<pvxs::Value> guard(value);
        auto pv = getPV(source, pv_name);

        if (value->idStartsWith("epics:nt/NTScalar:")) {
            auto current = pv.fetch();
            processControlLimits(current, *value);
            processAlarmLimits(current, *value);
        }

        pv.post(*value);
    });
}
