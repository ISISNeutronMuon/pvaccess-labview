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
getValue(Value* value, TypeCode type_code, T* result)
{
    try {
        if (auto value_field = (*value)["value"]) {
            if (value_field.type() != type_code) {
                return PVALVError::type_mismatch;
            }
            *result = value_field.as<T>();
        } else {
            return PVALVError::no_value_field;
        }
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

#define GETVALUE_FN(NAME, TYPE, TYPE_CODE)                                     \
    extern "C" PVA_LABVIEW_EXPORT labview::ErrCode getValue##NAME(             \
      Value* value, TYPE* result)                                              \
    {                                                                          \
        return getValue(value, TYPE_CODE, result);                             \
    }
GETVALUE_FN(Bool, int16_t, TypeCode::Bool)
GETVALUE_FN(Int8, int8_t, TypeCode::Int8)
GETVALUE_FN(Int16, int16_t, TypeCode::Int16)
GETVALUE_FN(Int32, int32_t, TypeCode::Int32)
GETVALUE_FN(Int64, int64_t, TypeCode::Int64)
GETVALUE_FN(UInt8, uint8_t, TypeCode::UInt8)
GETVALUE_FN(UInt16, uint16_t, TypeCode::UInt16)
GETVALUE_FN(UInt32, uint32_t, TypeCode::UInt32)
GETVALUE_FN(UInt64, uint64_t, TypeCode::UInt64)
GETVALUE_FN(Float32, float, TypeCode::Float32)
GETVALUE_FN(Float64, double, TypeCode::Float64)
GETVALUE_FN(String, labview::LStrHandle, TypeCode::String)
GETVALUE_FN(BoolArray, LV1DArrayHandle<int16_t>, TypeCode::BoolA)
GETVALUE_FN(Int8Array, LV1DArrayHandle<int8_t>, TypeCode::Int8A)
GETVALUE_FN(Int16Array, LV1DArrayHandle<int16_t>, TypeCode::Int16A)
GETVALUE_FN(Int32Array, LV1DArrayHandle<int32_t>, TypeCode::Int32A)
GETVALUE_FN(Int64Array, LV1DArrayHandle<int64_t>, TypeCode::Int64A)
GETVALUE_FN(UInt8Array, LV1DArrayHandle<uint8_t>, TypeCode::UInt8A)
GETVALUE_FN(UInt16Array, LV1DArrayHandle<uint16_t>, TypeCode::UInt16A)
GETVALUE_FN(UInt32Array, LV1DArrayHandle<uint32_t>, TypeCode::UInt32A)
GETVALUE_FN(UInt64Array, LV1DArrayHandle<uint64_t>, TypeCode::UInt64A)
GETVALUE_FN(Float32Array, LV1DArrayHandle<float>, TypeCode::Float32A)
GETVALUE_FN(Float64Array, LV1DArrayHandle<double>, TypeCode::Float64A)
GETVALUE_FN(StringArray,
            LV1DArrayHandle<labview::LStrHandle>,
            TypeCode::StringA)

template<typename T>
labview::ErrCode
setValue(Value* value, TypeCode type_code, T new_value)
{
    try {
        if (auto value_field = (*value)["value"]) {
            if (value_field.type() != type_code) {
                return PVALVError::type_mismatch;
            }
            (*value)["value"] = new_value;
        } else {
            return PVALVError::no_value_field;
        }
    } catch (...) {
        return err2code();
    }
    return PVALVError::no_err;
}

#define SETVALUE_FN(NAME, TYPE, TYPE_CODE)                                     \
    extern "C" PVA_LABVIEW_EXPORT labview::ErrCode setValue##NAME(             \
      Value* value, TYPE new_value)                                            \
    {                                                                          \
        return setValue(value, TYPE_CODE, new_value);                          \
    }

SETVALUE_FN(Bool, int16_t, TypeCode::Bool)
SETVALUE_FN(Int8, int8_t, TypeCode::Int8)
SETVALUE_FN(Int16, int16_t, TypeCode::Int16)
SETVALUE_FN(Int32, int32_t, TypeCode::Int32)
SETVALUE_FN(Int64, int64_t, TypeCode::Int64)
SETVALUE_FN(UInt8, uint8_t, TypeCode::UInt8)
SETVALUE_FN(UInt16, uint16_t, TypeCode::UInt16)
SETVALUE_FN(UInt32, uint32_t, TypeCode::UInt32)
SETVALUE_FN(UInt64, uint64_t, TypeCode::UInt64)
SETVALUE_FN(Float32, float, TypeCode::Float32)
SETVALUE_FN(Float64, double, TypeCode::Float64)
SETVALUE_FN(String, labview::LStrHandle, TypeCode::String)
SETVALUE_FN(BoolArray, LV1DArrayHandle<int16_t>, TypeCode::BoolA)
SETVALUE_FN(Int8Array, LV1DArrayHandle<int8_t>, TypeCode::Int8A)
SETVALUE_FN(Int16Array, LV1DArrayHandle<int16_t>, TypeCode::Int16A)
SETVALUE_FN(Int32Array, LV1DArrayHandle<int32_t>, TypeCode::Int32A)
SETVALUE_FN(Int64Array, LV1DArrayHandle<int64_t>, TypeCode::Int64A)
SETVALUE_FN(UInt8Array, LV1DArrayHandle<uint8_t>, TypeCode::UInt8A)
SETVALUE_FN(UInt16Array, LV1DArrayHandle<uint16_t>, TypeCode::UInt16A)
SETVALUE_FN(UInt32Array, LV1DArrayHandle<uint32_t>, TypeCode::UInt32A)
SETVALUE_FN(UInt64Array, LV1DArrayHandle<uint64_t>, TypeCode::UInt64A)
SETVALUE_FN(Float32Array, LV1DArrayHandle<float>, TypeCode::Float32A)
SETVALUE_FN(Float64Array, LV1DArrayHandle<double>, TypeCode::Float64A)
SETVALUE_FN(StringArray,
            LV1DArrayHandle<labview::LStrHandle>,
            TypeCode::StringA)
