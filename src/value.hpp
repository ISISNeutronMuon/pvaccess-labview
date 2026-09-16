#pragma once

struct Timestamp
{
    int64_t secondsPastEpoch;
    int32_t nanoseconds;
    int32_t userTag;
};
