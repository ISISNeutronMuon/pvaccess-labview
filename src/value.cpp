#include <pvxs/nt.h>
#include <pvxs/server.h>
#include <pvxs/sharedpv.h>

#include "exceptions.hpp"
#include "pva_labview_export.h"
#include "utils.hpp"

struct Timestamp
{
    int64_t secondsPastEpoch;
    int32_t nanoseconds;
    int32_t userTag;
};

pvxs::TypeCode
convertTypeCode(LVTypeCode code)
{
    switch (code) {
        case 1:
            return pvxs::TypeCode::Bool;
        case 2:
            return pvxs::TypeCode::BoolA;
        case 3:
            return pvxs::TypeCode::Int8;
        case 4:
            return pvxs::TypeCode::Int8A;
        case 5:
            return pvxs::TypeCode::Int16;
        case 6:
            return pvxs::TypeCode::Int16A;
        case 7:
            return pvxs::TypeCode::Int32;
        case 8:
            return pvxs::TypeCode::Int32A;
        case 9:
            return pvxs::TypeCode::Int64;
        case 10:
            return pvxs::TypeCode::Int64A;
        case 11:
            return pvxs::TypeCode::UInt8;
        case 12:
            return pvxs::TypeCode::UInt8A;
        case 13:
            return pvxs::TypeCode::UInt16;
        case 14:
            return pvxs::TypeCode::UInt16A;
        case 15:
            return pvxs::TypeCode::UInt32;
        case 16:
            return pvxs::TypeCode::UInt32A;
        case 17:
            return pvxs::TypeCode::UInt64;
        case 18:
            return pvxs::TypeCode::UInt64A;
        case 19:
            return pvxs::TypeCode::Float32;
        case 20:
            return pvxs::TypeCode::Float32A;
        case 21:
            return pvxs::TypeCode::Float64;
        case 22:
            return pvxs::TypeCode::Float64A;
        case 23:
            return pvxs::TypeCode::String;
        case 24:
            return pvxs::TypeCode::StringA;
        default:
            return pvxs::TypeCode::Null;
    }
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
createNTScalar(LVTypeCode type_code, pvxs::Value** value)
{
    try {
        *value = new pvxs::Value{
            pvxs::nt::NTScalar{ convertTypeCode(type_code) }.create()
        };
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
readFieldType(const pvxs::Value* value,
              const char* field_name,
              pvxs::TypeCode* type_code)
{
    try {
        if (value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto field = value->lookup(field_name);
        *type_code = field.type();
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

template<typename T>
labview::ErrCode
readField(const pvxs::Value* value,
          const char* field_name,
          const pvxs::TypeCode type_code,
          T* result)
{
    try {
        if (value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto field = value->lookup(field_name);
        if (field.type() != type_code)
            throw labview::lv_err(PVALVError::type_mismatch);

        *result = field.as<T>();
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
readTimestamp(const pvxs::Value* value,
              const char* field_name,
              Timestamp* result)
{
    try {
        if (value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto timestamp = value->lookup(field_name);

        *result = { timestamp.lookup("secondsPastEpoch").as<int64_t>(),
                    timestamp.lookup("nanoseconds").as<int32_t>(),
                    timestamp.lookup("userTag").as<int32_t>() };
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

#define READ_FN(NAME, TYPE, TYPE_CODE)                                         \
    extern "C" PVA_LABVIEW_EXPORT labview::ErrCode read##NAME(                 \
      pvxs::Value* value, const char* field_name, TYPE* result)                \
    {                                                                          \
        return readField(value, field_name, TYPE_CODE, result);                \
    }
READ_FN(Bool, int16_t, pvxs::TypeCode::Bool)
READ_FN(Int8, int8_t, pvxs::TypeCode::Int8)
READ_FN(Int16, int16_t, pvxs::TypeCode::Int16)
READ_FN(Int32, int32_t, pvxs::TypeCode::Int32)
READ_FN(Int64, int64_t, pvxs::TypeCode::Int64)
READ_FN(UInt8, uint8_t, pvxs::TypeCode::UInt8)
READ_FN(UInt16, uint16_t, pvxs::TypeCode::UInt16)
READ_FN(UInt32, uint32_t, pvxs::TypeCode::UInt32)
READ_FN(UInt64, uint64_t, pvxs::TypeCode::UInt64)
READ_FN(Float32, float, pvxs::TypeCode::Float32)
READ_FN(Float64, double, pvxs::TypeCode::Float64)
READ_FN(String, labview::LStrHandle, pvxs::TypeCode::String)
READ_FN(BoolArray, LV1DArrayHandle<int16_t>, pvxs::TypeCode::BoolA)
READ_FN(Int8Array, LV1DArrayHandle<int8_t>, pvxs::TypeCode::Int8A)
READ_FN(Int16Array, LV1DArrayHandle<int16_t>, pvxs::TypeCode::Int16A)
READ_FN(Int32Array, LV1DArrayHandle<int32_t>, pvxs::TypeCode::Int32A)
READ_FN(Int64Array, LV1DArrayHandle<int64_t>, pvxs::TypeCode::Int64A)
READ_FN(UInt8Array, LV1DArrayHandle<uint8_t>, pvxs::TypeCode::UInt8A)
READ_FN(UInt16Array, LV1DArrayHandle<uint16_t>, pvxs::TypeCode::UInt16A)
READ_FN(UInt32Array, LV1DArrayHandle<uint32_t>, pvxs::TypeCode::UInt32A)
READ_FN(UInt64Array, LV1DArrayHandle<uint64_t>, pvxs::TypeCode::UInt64A)
READ_FN(Float32Array, LV1DArrayHandle<float>, pvxs::TypeCode::Float32A)
READ_FN(Float64Array, LV1DArrayHandle<double>, pvxs::TypeCode::Float64A)
READ_FN(StringArray,
        LV1DArrayHandle<labview::LStrHandle>,
        pvxs::TypeCode::StringA)

template<typename T>
labview::ErrCode
writeField(pvxs::Value* const value,
           const char* field_name,
           const pvxs::TypeCode type_code,
           T new_value)
{
    try {
        if (value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        auto field = value->lookup(field_name);
        if (field.type() != type_code)
            throw labview::lv_err(PVALVError::type_mismatch);

        value->update(field_name, new_value);
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

#define WRITE_FN(NAME, TYPE, TYPE_CODE)                                        \
    extern "C" PVA_LABVIEW_EXPORT labview::ErrCode write##NAME(                \
      pvxs::Value* const value, const char* field_name, TYPE new_value)        \
    {                                                                          \
        return writeField(value, field_name, TYPE_CODE, new_value);            \
    }

WRITE_FN(Bool, int16_t, pvxs::TypeCode::Bool)
WRITE_FN(Int8, int8_t, pvxs::TypeCode::Int8)
WRITE_FN(Int16, int16_t, pvxs::TypeCode::Int16)
WRITE_FN(Int32, int32_t, pvxs::TypeCode::Int32)
WRITE_FN(Int64, int64_t, pvxs::TypeCode::Int64)
WRITE_FN(UInt8, uint8_t, pvxs::TypeCode::UInt8)
WRITE_FN(UInt16, uint16_t, pvxs::TypeCode::UInt16)
WRITE_FN(UInt32, uint32_t, pvxs::TypeCode::UInt32)
WRITE_FN(UInt64, uint64_t, pvxs::TypeCode::UInt64)
WRITE_FN(Float32, float, pvxs::TypeCode::Float32)
WRITE_FN(Float64, double, pvxs::TypeCode::Float64)
WRITE_FN(String, labview::LStrHandle, pvxs::TypeCode::String)
WRITE_FN(BoolArray, LV1DArrayHandle<int16_t>, pvxs::TypeCode::BoolA)
WRITE_FN(Int8Array, LV1DArrayHandle<int8_t>, pvxs::TypeCode::Int8A)
WRITE_FN(Int16Array, LV1DArrayHandle<int16_t>, pvxs::TypeCode::Int16A)
WRITE_FN(Int32Array, LV1DArrayHandle<int32_t>, pvxs::TypeCode::Int32A)
WRITE_FN(Int64Array, LV1DArrayHandle<int64_t>, pvxs::TypeCode::Int64A)
WRITE_FN(UInt8Array, LV1DArrayHandle<uint8_t>, pvxs::TypeCode::UInt8A)
WRITE_FN(UInt16Array, LV1DArrayHandle<uint16_t>, pvxs::TypeCode::UInt16A)
WRITE_FN(UInt32Array, LV1DArrayHandle<uint32_t>, pvxs::TypeCode::UInt32A)
WRITE_FN(UInt64Array, LV1DArrayHandle<uint64_t>, pvxs::TypeCode::UInt64A)
WRITE_FN(Float32Array, LV1DArrayHandle<float>, pvxs::TypeCode::Float32A)
WRITE_FN(Float64Array, LV1DArrayHandle<double>, pvxs::TypeCode::Float64A)
WRITE_FN(StringArray,
         LV1DArrayHandle<labview::LStrHandle>,
         pvxs::TypeCode::StringA)

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
deleteValue(pvxs::Value* const value)
{
    try {
        if (value == nullptr)
            throw labview::lv_err(PVALVError::null_ptr);

        delete value;
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}
