#include <chrono>

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

typedef void* SubHandle;
using SP = std::shared_ptr<client::Subscription>;

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
monitor(client::Context* client, char pv_name[], SubHandle* handle)
{
    try {
        if (client == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto sub = client->monitor(pv_name).maskDisconnected().exec();
        *handle = reinterpret_cast<SubHandle>(new SP(sub));
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
subscriptionNextValue(SubHandle handle,
                      double timeout,
                      Value** value,
                      int16_t* timedOut)
{
    try {
        SP& sub = *reinterpret_cast<SP*>(handle);
        if (sub == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto timeoutDuration = std::chrono::duration<double>(timeout);
        auto t0 = std::chrono::system_clock::now().time_since_epoch();
        auto t1 = t0;
        Value update;

        while (!update && (t1 - t0 < timeoutDuration)) {
            t1 = std::chrono::system_clock::now().time_since_epoch();
            update = sub->pop();
        }
        if (update) {
            *timedOut = 0;
            *value = new Value{ update };
        } else {
            *timedOut = 1;
        }
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
closeSubscription(SubHandle handle)
{
    try {
        SP& sub = *reinterpret_cast<SP*>(handle);
        if (sub == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        sub->cancel();
        delete reinterpret_cast<SP*>(handle);
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}
