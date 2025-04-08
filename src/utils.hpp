#pragma once

#include "lv_interop.hpp"
#include <pvxs/client.h>
#include <string>

using LVTypeCode = uint8_t;

template<typename T>
class LV1DArrayHandle : public labview::LV1DArrayHandle<T>
{
  public:
    template<class E>
    LV1DArrayHandle(const pvxs::shared_array<const E>& src)
      : labview::LV1DArrayHandle<T>()
    {
        this->from(src);
    }

    template<class E>
    void from(pvxs::shared_array<const E> src)
    {
        size_t count = src.size();
        this->resize(count);
        for (size_t i = 0; i < count; i++) {
            this->elements()[i] = T(src[i]);
        }
    }
};

template<>
struct pvxs::impl::StorageMap<labview::LStrHandle>
{
    typedef std::string store_t;
    static constexpr StoreType code{ StoreType::String };
};

template<typename E>
struct pvxs::impl::StorageMap<LV1DArrayHandle<E>>
{
    typedef shared_array<const void> store_t;
    static constexpr StoreType code{ StoreType::Array };
};

template<typename E>
struct pvxs::impl::StoreTransform<LV1DArrayHandle<E>>
{
    static inline pvxs::shared_array<const void> in(const LV1DArrayHandle<E>& v)
    {
        size_t count = v.count();
        auto arr =
          pvxs::shared_array<typename pvxs::impl::StoreAs<E>::store_t>(count);
        for (size_t i = 0; i < count; i++) {
            arr[i] = pvxs::impl::StoreTransform<E>::in(v.elements()[i]);
        }
        return arr.freeze().template castTo<const void>();
    }
    static inline LV1DArrayHandle<E> out(
      const pvxs::shared_array<const void>& v)
    {
        return LV1DArrayHandle<E>(v.template convertTo<const E>());
    }
};

template<>
struct pvxs::impl::StoreTransform<LV1DArrayHandle<labview::LStrHandle>>
{
    static inline pvxs::shared_array<const void> in(
      const LV1DArrayHandle<labview::LStrHandle>& v)
    {
        size_t count = v.count();
        auto arr = pvxs::shared_array<
          typename pvxs::impl::StoreAs<labview::LStrHandle>::store_t>(count);
        for (size_t i = 0; i < count; i++) {
            arr[i] = pvxs::impl::StoreTransform<labview::LStrHandle>::in(
              v.elements()[i]);
        }
        return arr.freeze().template castTo<const void>();
    }
    static inline LV1DArrayHandle<labview::LStrHandle> out(
      const pvxs::shared_array<const void>& v)
    {
        return LV1DArrayHandle<labview::LStrHandle>(
          v.castTo<const std::string>());
    }
};
