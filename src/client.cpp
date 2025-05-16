#include <pvxs/client.h>

#include "exceptions.hpp"
#include "pva_labview_export.h"
#include "utils.hpp"

using namespace pvxs;

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
createClient(client::Context** client)
{
    try {
        *client = new client::Context(client::Context::fromEnv());
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
closeClient(client::Context* client)
{
    try {
        if (client == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);
        delete client;
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
get(client::Context* client, char pv_name[], double timeout, Value** value)
{
    try {
        if (client == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        *value = new Value{ client->get(pv_name).exec()->wait(timeout) };
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
put(client::Context* client, char pv_name[], double timeout, Value* value)
{
    try {
        if (client == nullptr || value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        client->put(pv_name)
          .set("value", (*value)["value"])
          .exec()
          ->wait(timeout);
        delete value;
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}
