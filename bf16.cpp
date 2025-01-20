#include "common.h"


uint16_t bf16_from_fp32_round_to_zero(float x)
{
    if (!std::isnan(x))
    {
        union
        {
            float f32;
            uint32_t u32;
        };
        f32 = x;
        return uint16_t(u32 >> 16);
    }
    else
    {
        return UINT16_C(0x7FC0);
    }
}

// https://github.com/pytorch/pytorch/blob/main/c10/util/BFloat16.h
uint16_t bf16_from_fp32_round_to_nearest_even(float x)
{
    if (!std::isnan(x))
    {
        union
        {
            float f32;
            uint32_t u32;
        };
        f32 = x;
        uint32_t roundingBias = ((u32 >> 16) & 1) + UINT32_C(0x7FFF);
        return static_cast<uint16_t>((u32 + roundingBias) >> 16);
    }
    else
    {
        return UINT16_C(0x7FC0);
    }
}

float bf16_to_fp32(uint16_t x)
{
    union
    {
        uint32_t u32;
        float f32;
    };
    u32 = x;
    u32 <<= 16;
    return f32;
}
