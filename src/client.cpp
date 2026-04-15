#include <chrono>

#include <pvxs/client.h>

#include "exceptions.hpp"
#include "pva_labview_export.h"
#include "utils.hpp"

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
createClient(pvxs::client::Context** client)
{
    try {
        *client = new pvxs::client::Context(pvxs::client::Context::fromEnv());
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
closeClient(pvxs::client::Context* client)
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
get(pvxs::client::Context* client,
    char pv_name[],
    double timeout,
    pvxs::Value** value)
{
    try {
        if (client == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        *value = new pvxs::Value{ client->get(pv_name).exec()->wait(timeout) };
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
put(pvxs::client::Context* client,
    char pv_name[],
    double timeout,
    pvxs::Value* value)
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

struct SubHandle
{
    std::shared_ptr<pvxs::client::Subscription> ptr;
};

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
monitor(pvxs::client::Context* client, char pv_name[], SubHandle** handle)
{
    try {
        if (client == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        *handle = new SubHandle;
        if (strlen(pv_name) > 0)
            (*handle)->ptr = client->monitor(pv_name).maskDisconnected().exec();
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
subscriptionNextValue(SubHandle* handle,
                      double timeout,
                      labview::LStrHandle pvName,
                      pvxs::Value** value,
                      int16_t* timedOut)
{
    try {
        if (handle == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);
        auto sub = handle->ptr;
        if (sub == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto timeoutDuration = std::chrono::duration<double>(timeout);
        auto t0 = std::chrono::system_clock::now().time_since_epoch();
        auto t1 = t0;
        pvxs::Value update;

        do {
            t1 = std::chrono::system_clock::now().time_since_epoch();
            update = sub->pop();
        } while (!update && (t1 - t0 < timeoutDuration));
        if (update) {
            pvName = sub->name();
            *timedOut = 0;
            *value = new pvxs::Value{ update };
        } else {
            *timedOut = 1;
        }
    } catch (std::exception& e) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
closeSubscription(SubHandle* handle)
{
    try {
        if (handle == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);
        auto sub = handle->ptr;
        if (sub == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        sub->cancel();
        delete handle;
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}
