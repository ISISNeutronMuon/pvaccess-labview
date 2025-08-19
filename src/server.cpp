#include <pvxs/nt.h>
#include <pvxs/server.h>
#include <pvxs/sharedpv.h>

#include "exceptions.hpp"
#include "pva_labview_export.h"
#include "utils.hpp"

using namespace pvxs;

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
createServer(server::Server** server, server::StaticSource** source)
{
    try {
        *server = new server::Server(server::Server::fromEnv());
        *source = new server::StaticSource(server::StaticSource::build());
        (**server).addSource("labview", (**source).source());
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
startServer(server::Server* server)
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
stopServer(server::Server* server)
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
closeServer(server::Server* server, server::StaticSource* source)
{
    try {
        if (server == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        server->stop();
        delete server;
        delete source;
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
addPV(server::StaticSource* source, char pv_name[], Value* value)
{
    try {
        if (source == nullptr || value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto pv{ server::SharedPV::buildMailbox() };
        pv.open(*value);
        source->add(pv_name, pv);
        delete value;
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

server::SharedPV
getPV(server::StaticSource* source, std::string pv_name)
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
fetch(server::StaticSource* source, char pv_name[], Value** value)
{
    try {
        if (source == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto pv = getPV(source, pv_name);
        *value = new Value{ pv.fetch() };
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
post(server::StaticSource* source, char pv_name[], Value* value)
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
