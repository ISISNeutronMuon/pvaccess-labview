#include <pvxs/nt.h>
#include <pvxs/server.h>
#include <pvxs/sharedpv.h>

#include "exceptions.hpp"
#include "pva_labview_export.h"
#include "utils.hpp"

using namespace pvxs;

TypeCode
convertTypeCode(LVTypeCode code)
{
    switch (code) {
        case 1:
            return TypeCode::Bool;
        case 2:
            return TypeCode::BoolA;
        case 3:
            return TypeCode::Int8;
        case 4:
            return TypeCode::Int8A;
        case 5:
            return TypeCode::Int16;
        case 6:
            return TypeCode::Int16A;
        case 7:
            return TypeCode::Int32;
        case 8:
            return TypeCode::Int32A;
        case 9:
            return TypeCode::Int64;
        case 10:
            return TypeCode::Int64A;
        case 11:
            return TypeCode::UInt8;
        case 12:
            return TypeCode::UInt8A;
        case 13:
            return TypeCode::UInt16;
        case 14:
            return TypeCode::UInt16A;
        case 15:
            return TypeCode::UInt32;
        case 16:
            return TypeCode::UInt32A;
        case 17:
            return TypeCode::UInt64;
        case 18:
            return TypeCode::UInt64A;
        case 19:
            return TypeCode::Float32;
        case 20:
            return TypeCode::Float32A;
        case 21:
            return TypeCode::Float64;
        case 22:
            return TypeCode::Float64A;
        case 23:
            return TypeCode::String;
        case 24:
            return TypeCode::StringA;
        default:
            return TypeCode::Null;
    }
}

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
createNTScalar(LVTypeCode type_code, Value** value)
{
    try {
        *value =
          new Value{ nt::NTScalar{ convertTypeCode(type_code) }.create() };
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

template<typename T>
labview::ErrCode
readField(const Value* value,
          const char* field_name,
          const TypeCode type_code,
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

#define READ_FN(NAME, TYPE, TYPE_CODE)                                         \
    extern "C" PVA_LABVIEW_EXPORT labview::ErrCode read##NAME(                 \
      Value* value, const char* field_name, TYPE* result)                      \
    {                                                                          \
        return readField(value, field_name, TYPE_CODE, result);                \
    }
READ_FN(Bool, int16_t, TypeCode::Bool)
READ_FN(Int8, int8_t, TypeCode::Int8)
READ_FN(Int16, int16_t, TypeCode::Int16)
READ_FN(Int32, int32_t, TypeCode::Int32)
READ_FN(Int64, int64_t, TypeCode::Int64)
READ_FN(UInt8, uint8_t, TypeCode::UInt8)
READ_FN(UInt16, uint16_t, TypeCode::UInt16)
READ_FN(UInt32, uint32_t, TypeCode::UInt32)
READ_FN(UInt64, uint64_t, TypeCode::UInt64)
READ_FN(Float32, float, TypeCode::Float32)
READ_FN(Float64, double, TypeCode::Float64)
READ_FN(String, labview::LStrHandle, TypeCode::String)
READ_FN(BoolArray, LV1DArrayHandle<int16_t>, TypeCode::BoolA)
READ_FN(Int8Array, LV1DArrayHandle<int8_t>, TypeCode::Int8A)
READ_FN(Int16Array, LV1DArrayHandle<int16_t>, TypeCode::Int16A)
READ_FN(Int32Array, LV1DArrayHandle<int32_t>, TypeCode::Int32A)
READ_FN(Int64Array, LV1DArrayHandle<int64_t>, TypeCode::Int64A)
READ_FN(UInt8Array, LV1DArrayHandle<uint8_t>, TypeCode::UInt8A)
READ_FN(UInt16Array, LV1DArrayHandle<uint16_t>, TypeCode::UInt16A)
READ_FN(UInt32Array, LV1DArrayHandle<uint32_t>, TypeCode::UInt32A)
READ_FN(UInt64Array, LV1DArrayHandle<uint64_t>, TypeCode::UInt64A)
READ_FN(Float32Array, LV1DArrayHandle<float>, TypeCode::Float32A)
READ_FN(Float64Array, LV1DArrayHandle<double>, TypeCode::Float64A)
READ_FN(StringArray, LV1DArrayHandle<labview::LStrHandle>, TypeCode::StringA)

template<typename T>
labview::ErrCode
writeField(Value* const value,
           const char* field_name,
           const TypeCode type_code,
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
      Value* const value, const char* field_name, TYPE new_value)              \
    {                                                                          \
        return writeField(value, field_name, TYPE_CODE, new_value);            \
    }

WRITE_FN(Bool, int16_t, TypeCode::Bool)
WRITE_FN(Int8, int8_t, TypeCode::Int8)
WRITE_FN(Int16, int16_t, TypeCode::Int16)
WRITE_FN(Int32, int32_t, TypeCode::Int32)
WRITE_FN(Int64, int64_t, TypeCode::Int64)
WRITE_FN(UInt8, uint8_t, TypeCode::UInt8)
WRITE_FN(UInt16, uint16_t, TypeCode::UInt16)
WRITE_FN(UInt32, uint32_t, TypeCode::UInt32)
WRITE_FN(UInt64, uint64_t, TypeCode::UInt64)
WRITE_FN(Float32, float, TypeCode::Float32)
WRITE_FN(Float64, double, TypeCode::Float64)
WRITE_FN(String, labview::LStrHandle, TypeCode::String)
WRITE_FN(BoolArray, LV1DArrayHandle<int16_t>, TypeCode::BoolA)
WRITE_FN(Int8Array, LV1DArrayHandle<int8_t>, TypeCode::Int8A)
WRITE_FN(Int16Array, LV1DArrayHandle<int16_t>, TypeCode::Int16A)
WRITE_FN(Int32Array, LV1DArrayHandle<int32_t>, TypeCode::Int32A)
WRITE_FN(Int64Array, LV1DArrayHandle<int64_t>, TypeCode::Int64A)
WRITE_FN(UInt8Array, LV1DArrayHandle<uint8_t>, TypeCode::UInt8A)
WRITE_FN(UInt16Array, LV1DArrayHandle<uint16_t>, TypeCode::UInt16A)
WRITE_FN(UInt32Array, LV1DArrayHandle<uint32_t>, TypeCode::UInt32A)
WRITE_FN(UInt64Array, LV1DArrayHandle<uint64_t>, TypeCode::UInt64A)
WRITE_FN(Float32Array, LV1DArrayHandle<float>, TypeCode::Float32A)
WRITE_FN(Float64Array, LV1DArrayHandle<double>, TypeCode::Float64A)
WRITE_FN(StringArray, LV1DArrayHandle<labview::LStrHandle>, TypeCode::StringA)

extern "C" PVA_LABVIEW_EXPORT labview::ErrCode
deleteValue(Value* const value)
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
