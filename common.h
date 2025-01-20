#pragma once

#include <cstddef>
#include <cfloat>
#include <cmath>
#include <cstdint>
#include <intrin.h>

#include <memory>
#include <type_traits>

// Implementations of std::bit_cast() from C++ 20.
//
// This is a less sketchy version of reinterpret_cast.
//
// See https://en.cppreference.com/w/cpp/numeric/bit_cast for more
// information as well as the source of our implementations.
template <class To, class From>
std::enable_if_t<
    sizeof(To) == sizeof(From) && std::is_trivially_copyable_v<From>&&
    std::is_trivially_copyable_v<To>,
    To>
    // constexpr support needs compiler magic
    bit_cast(const From& src) noexcept {
    static_assert(
        std::is_trivially_constructible_v<To>,
        "This implementation additionally requires "
        "destination type to be trivially constructible");

    To dst;
    std::memcpy(&dst, &src, sizeof(To));
    return dst;
}

// https://github.com/pytorch/pytorch/blob/main/c10/util/floating_point_utils.h
inline float fp32_from_bits(uint32_t w) {
#if defined(__OPENCL_VERSION__)
    return as_float(w);
#elif defined(__CUDA_ARCH__) || defined(__HIP_DEVICE_COMPILE__)
    return __uint_as_float((unsigned int)w);
#elif defined(__INTEL_COMPILER)
    return _castu32_f32(w);
#else
    return bit_cast<float>(w);
#endif
}

inline uint32_t fp32_to_bits(float f) {
#if defined(__OPENCL_VERSION__)
    return as_uint(f);
#elif defined(__CUDA_ARCH__) || defined(__HIP_DEVICE_COMPILE__)
    return (uint32_t)__float_as_uint(f);
#elif defined(__INTEL_COMPILER)
    return _castf32_u32(f);
#else
    return bit_cast<uint32_t>(f);
#endif
}
