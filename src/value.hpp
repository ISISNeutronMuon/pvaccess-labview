#pragma once

#include "lv_interop.hpp"

struct Timestamp
{
    int64_t secondsPastEpoch;
    int32_t nanoseconds;
    int32_t userTag;
};

enum AlarmSeverity : int32_t
{
    NoAlarm = 0,
    MinorAlarm,
    MajorAlarm,
    RecordAlarm,
    InvalidAlarm,
    UndefinedAlarm,
};

enum AlarmStatus : int32_t
{
    NoStatus = 0,
    DeviceStatus,
    DriverStatus,
    RecordStatus,
    DbStatus,
    ConfStatus,
    UndefinedStatus,
    ClientStatus,
};

struct Alarm
{
    AlarmSeverity severity;
    AlarmStatus status;
    labview::LStrHandle message;
};

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

struct Display
{
    double limitLow;
    double limitHigh;
    labview::LStrHandle description;
    labview::LStrHandle units;
    int32_t precision;
    DisplayForm form;
};
