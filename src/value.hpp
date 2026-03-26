#pragma once

#include "lv_interop.hpp"

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
    AlarmSeverity severity;
    AlarmStatus status;
    labview::LStrHandle message;
};

struct AlarmLimit
{
    int16_t active;
    double lowAlarmLimit;
    double lowWarningLimit;
    double highWarningLimit;
    double highAlarmLimit;
    AlarmSeverity lowAlarmSeverity;
    AlarmSeverity lowWarningSeverity;
    AlarmSeverity highWarningSeverity;
    AlarmSeverity highAlarmSeverity;
    double hysteresis;
};

struct DisplayMetadata
{
    double limitLow;
    double limitHigh;
    labview::LStrHandle description;
    labview::LStrHandle units;
    int32_t precision;
    DisplayForm form;
};

struct ControlMetadata
{
    double limitLow;
    double limitHigh;
    double minStep;
};
