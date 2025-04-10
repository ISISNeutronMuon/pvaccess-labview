#pragma once

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
};

labview::ErrCode
err2code();
