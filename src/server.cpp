#include <pvxs/nt.h>
#include <pvxs/server.h>
#include <pvxs/sharedpv.h>

#include "exceptions.hpp"
#include "pva_labview_export.h"
#include "utils.hpp"

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
createServer(pvxs::server::Server** server, pvxs::server::StaticSource** source)
{
    try {
        *server = new pvxs::server::Server(pvxs::server::Server::fromEnv());
        *source =
          new pvxs::server::StaticSource(pvxs::server::StaticSource::build());
        (**server).addSource("labview", (**source).source());
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
startServer(pvxs::server::Server* server)
{
    try {
        if (server == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        server->start();
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
stopServer(pvxs::server::Server* server)
{
    try {
        if (server == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        server->stop();
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
closeServer(pvxs::server::Server* server)
{
    try {
        if (server == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        server->stop();
        delete server;
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
addPV(pvxs::server::StaticSource* source,
      char pv_name[],
      pvxs::Value* value,
      int16_t read_only)
{
    try {
        if (source == nullptr || value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto pv{ pvxs::server::SharedPV::buildReadonly() };

        if (read_only == 0) {
            pv = pvxs::server::SharedPV::buildMailbox();
        }

        pv.open(*value);
        source->add(pv_name, pv);
        delete value;
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

pvxs::server::SharedPV
getPV(pvxs::server::StaticSource* source, std::string pv_name)
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
fetch(pvxs::server::StaticSource* source, char pv_name[], pvxs::Value** value)
{
    try {
        if (source == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto pv = getPV(source, pv_name);
        *value = new pvxs::Value{ pv.fetch() };
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
post(pvxs::server::StaticSource* source, char pv_name[], pvxs::Value* value)
{
    try {
        if (source == nullptr || value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto pv = getPV(source, pv_name);
        pv.post(*value);
        delete value;
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}
