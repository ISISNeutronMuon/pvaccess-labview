#include "lv_interop.hpp"

namespace labview {
template<>
TypeCode
getNumType<char>()
{
    return TypeCode::iB;
}
template<>
TypeCode
getNumType<int8_t>()
{
    return TypeCode::iB;
}
template<>
TypeCode
getNumType<int16_t>()
{
    return TypeCode::iW;
}
template<>
TypeCode
getNumType<int32_t>()
{
    return TypeCode::iL;
}
template<>
TypeCode
getNumType<int64_t>()
{
    return TypeCode::iQ;
}
template<>
TypeCode
getNumType<uint8_t>()
{
    return TypeCode::uB;
}
template<>
TypeCode
getNumType<uint16_t>()
{
    return TypeCode::uW;
}
template<>
TypeCode
getNumType<uint32_t>()
{
    return TypeCode::uL;
}
template<>
TypeCode
getNumType<uint64_t>()
{
    return TypeCode::uQ;
}
template<>
TypeCode
getNumType<float>()
{
    return TypeCode::fS;
}
template<>
TypeCode
getNumType<double>()
{
    return TypeCode::fD;
}
template<>
TypeCode
getNumType<LStrHandle>()
{
    switch (sizeof(size_t)) {
        case 4:
            return TypeCode::uL;
        default:
            return TypeCode::uQ;
    }
}

void
funcWrapper(ErrCode code)
{
    if (code != 0)
        throw lv_err(code);
}

} // namespace labview
