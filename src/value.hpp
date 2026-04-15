#pragma once

#include "lv_interop.hpp"

enum DisplayForm : int32_t
{
    Default = 0,
    String,
    Binary,
    Decimal,
    Hex,
    Exponential,
    Engineering,
};

struct Timestamp
{
    int64_t secondsPastEpoch;
    int32_t nanoseconds;
    int32_t userTag;
};

struct Alarm
{
    int32_t severity;
    int32_t status;
    labview::LStrHandle message;
};
