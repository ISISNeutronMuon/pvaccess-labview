#include <chrono>
#include <memory>
#include <thread>

#include <pvxs/client.h>

#include "exceptions.hpp"
#include "pva_labview_export.h"
#include "utils.hpp"

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
createClient(pvxs::client::Context** client)
{
    return err2code([&] {
        *client = new pvxs::client::Context(pvxs::client::Context::fromEnv());
    });
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
closeClient(const pvxs::client::Context* client)
{
    return err2code([&] {
        if (client == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);
        delete client;
    });
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
get(pvxs::client::Context* client,
    const char pv_name[],
    const double timeout,
    pvxs::Value** value)
{
    return err2code([&] {
        if (client == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);
        if (strlen(pv_name) == 0)
            throw labview::lv_err(PVALVError::empty_pv_name);

        *value = new pvxs::Value{ client->get(pv_name).exec()->wait(timeout) };
    });
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
put(pvxs::client::Context* client,
    const char pv_name[],
    const double timeout,
    pvxs::Value* value)
{
    return err2code([&] {
        if (client == nullptr || value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);
        if (strlen(pv_name) == 0)
            throw labview::lv_err(PVALVError::empty_pv_name);

        std::unique_ptr<pvxs::Value> guard(value);

        client->put(pv_name)
          .build([value](pvxs::Value&& prototype) {
              return prototype.assign(*value);
          })
          .exec()
          ->wait(timeout);
    });
}

struct SubHandle
{
    std::shared_ptr<pvxs::client::Subscription> ptr;
};

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
monitor(pvxs::client::Context* client, const char pv_name[], SubHandle** handle)
{
    return err2code([&] {
        if (client == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);
        if (strlen(pv_name) == 0)
            throw labview::lv_err(PVALVError::empty_pv_name);

        *handle = new SubHandle;
        (*handle)->ptr = client->monitor(pv_name).maskDisconnected().exec();
    });
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
subscriptionNextValue(const SubHandle* handle,
                      const double timeout,
                      labview::LStrHandle pv_name,
                      pvxs::Value** value,
                      int16_t* timed_out)
{
    return err2code([&] {
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
            if (!update)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (!update && (t1 - t0 < timeoutDuration));
        if (update) {
            pv_name = sub->name();
            *timed_out = 0;
            *value = new pvxs::Value{ update };
        } else {
            *timed_out = 1;
        }
    });
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
closeSubscription(const SubHandle* handle)
{
    return err2code([&] {
        if (handle == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);
        auto sub = handle->ptr;
        if (sub == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        sub->cancel();
        delete handle;
    });
}
