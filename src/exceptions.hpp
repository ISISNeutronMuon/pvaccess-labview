#pragma once

#include <pvxs/client.h>

#include "lv_interop.hpp"

enum PVALVError : labview::ErrCode
{
    no_err = 0,
    unspecified = 502450,
    interrupted = 502451,
    timeout = 502452,
    field_missing = 502453,
    cannot_convert_value = 502454,
    type_mismatch = 502455,
    server_post_pv_not_found = 502456,
    null_ptr = 502457,
    empty_pv_name = 502458,
};

template<typename F>
labview::ErrCode
err2code(F&& fn)
{
    try {
        fn();
        return PVALVError::no_err;
    } catch (const labview::lv_err& e) {
        return e.code;
    } catch (const pvxs::NoConvert&) {
        return PVALVError::cannot_convert_value;
    } catch (const pvxs::LookupError&) {
        return PVALVError::field_missing;
    } catch (const pvxs::client::Interrupted&) {
        return PVALVError::interrupted;
    } catch (const pvxs::client::Timeout&) {
        return PVALVError::timeout;
    } catch (...) {
        return PVALVError::unspecified;
    }
}
