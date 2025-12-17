#pragma once

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>

namespace labview {

using ErrCode = int32_t;
using UHandle = uint8_t**;

enum NumType
{
    iB = 1,
    iW,
    iL,
    iQ,
    uB,
    uW,
    uL,
    uQ,
    fS,
    fD,
    fX,
    cS,
    cD,
    cX
};

extern "C" UHandle __cdecl
DSNewHClr(size_t n);
extern "C" ErrCode __cdecl
DSCheckHandle(const void* h);
extern "C" ErrCode __cdecl
NumericArrayResize(int32_t typeCode,
                   int32_t numDims,
                   UHandle* dataHP,
                   size_t totalNewSize);

template<typename T>
NumType
getNumType();

void
funcWrapper(ErrCode code);

class lv_err : public std::runtime_error
{
  public:
    ErrCode code;
    lv_err(ErrCode code)
      : code(code)
      , std::runtime_error("LabVIEW error")
    {
    }
};

template<typename T, int D>
struct LVArrayBase
{
    int32_t count;
    T elements[D];
};

template<typename T, int D>
class LVArrayBaseHandle
{
  public:
    LVArrayBase<T, D>** handle;

    LVArrayBaseHandle()
      : LVArrayBaseHandle(DSNewHClr(0)) {};
    LVArrayBaseHandle(UHandle h) { this->handle = (LVArrayBase<T, D>**)(h); };

    int32_t count() const { return (*this->handle)->count; }

    auto elements() const { return (*this->handle)->elements; }

    void resize(size_t size)
    {
        // Validate handle
        funcWrapper(DSCheckHandle(this->handle));
        // Resize handle
        funcWrapper(NumericArrayResize(
          getNumType<T>(), 1, (UHandle*)(&this->handle), size * sizeof(T*)));
        (*this->handle)->count = static_cast<int32_t>(size);
    }

    template<class FROM>
    void from(FROM src);
};

template<typename T>
class LV1DArrayHandle : public LVArrayBaseHandle<T, 1>
{
  public:
    using LVArrayBaseHandle<T, 1>::LVArrayBaseHandle;
};

class LStrHandle : public LVArrayBaseHandle<char, 1>
{
  public:
    using LVArrayBaseHandle::LVArrayBaseHandle;
    LStrHandle(std::string str)
      : LVArrayBaseHandle()
    {
        this->from(str);
    };

    LStrHandle& operator=(const std::string& str)
    {
        this->from(str);
        return *this;
    }

    operator std::string() const
    {
        size_t count = this->count();
        // Allocate new char array
        auto cstr = new char[count];
        // Copy the LStrHandle to it
        memcpy(cstr, (*this->handle)->elements, count);
        return std::string{ cstr, count };
    }

    void from(std::string str)
    {
        auto count = str.length();
        this->resize(count);
        memcpy((*this->handle)->elements, str.c_str(), count);
    }
};

} // namespace labview
