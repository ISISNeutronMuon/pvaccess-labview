#include "lv_interop.hpp"

namespace labview {
template<>
NumType
getNumType<char>()
{
    return NumType::iB;
}
template<>
NumType
getNumType<int8_t>()
{
    return NumType::iB;
}
template<>
NumType
getNumType<int16_t>()
{
    return NumType::iW;
}
template<>
NumType
getNumType<int32_t>()
{
    return NumType::iL;
}
template<>
NumType
getNumType<int64_t>()
{
    return NumType::iQ;
}
template<>
NumType
getNumType<uint8_t>()
{
    return NumType::uB;
}
template<>
NumType
getNumType<uint16_t>()
{
    return NumType::uW;
}
template<>
NumType
getNumType<uint32_t>()
{
    return NumType::uL;
}
template<>
NumType
getNumType<uint64_t>()
{
    return NumType::uQ;
}
template<>
NumType
getNumType<float>()
{
    return NumType::fS;
}
template<>
NumType
getNumType<double>()
{
    return NumType::fD;
}
template<>
NumType
getNumType<LStrHandle>()
{
    switch (sizeof(size_t)) {
        case 4:
            return NumType::uL;
        default:
            return NumType::uQ;
    }
}

void
funcWrapper(ErrCode code)
{
    if (code != 0)
        throw lv_err(code);
}

} // namespace labview
