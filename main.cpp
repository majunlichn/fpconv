#include "common.h"

uint32_t fp16_ieee_to_fp32_bits(uint16_t h);
float fp16_ieee_to_fp32_value(uint16_t h);
uint16_t fp16_ieee_from_fp32_value(float f);
uint16_t bf16_from_fp32_round_to_zero(float x);
uint16_t bf16_from_fp32_round_to_nearest_even(float x);
float bf16_to_fp32(uint16_t x);
float fp8e4m3fn_to_fp32_value(uint8_t input);
uint8_t fp8e4m3fn_from_fp32_value(float f);
float fp8e5m2_to_fp32_value(uint8_t input);
uint8_t fp8e5m2_from_fp32_value(float f);

void print_help()
{
    printf("Floating-Point Converter\n\n");
    printf("Usage: fpconv [Operation] [Value]\n\n");
    printf("Supported Operations:\n");
    printf("    -fp16:              encode a fp32 as fp16.\n");
    printf("    -fp16hex-fp32:      decode a fp16 as fp32.\n");
    printf("    -bf16:              encode a fp32 as bf16 (round to nearest even).\n");
    printf("    -bf16rtz:           encode a fp32 as bf16 (round to zero).\n");
    printf("    -bf16hex-fp32:      decode a bf16 as fp32.\n");
    printf("    -fp8:               encode a fp32 as fp8e4m3 (hex).\n");
    printf("    -fp8hex-fp32:       decode a fp8e4m3 as fp32.\n");
    printf("    -bf8:               encode a fp32 as bf8 (fp8e5m2).\n");
    printf("    -bf8hex-fp32:       decode a bf8 (fp8e5m2) as fp32.\n");
}

int main(int argc, char** argv)
{
    if (argc > 0)
    {
        for (int i = 0; i < argc; ++i)
        {
            if ((strcmp(argv[i], "-h") == 0) ||
                (strcmp(argv[i], "--help") == 0) ||
                (strcmp(argv[i], "?") == 0))
            {
                print_help();
                return 0;
            }
        }
    }

    if (argc == 3)
    {
        const char* opString = argv[1];
        const char* valueString = argv[2];
        if (strcmp(opString, "-fp16") == 0)
        {
            float f0 = strtof(valueString, nullptr);
            uint16_t r = fp16_ieee_from_fp32_value(f0);
            float f1 = fp16_ieee_to_fp32_value(r);
            printf("0x%4X (e=%+.6f)", r, f0 - f1);
        }
        else if (strcmp(opString, "-fp16hex-fp32") == 0)
        {
            uint32_t bits = strtoul(valueString, nullptr, 16);
            float r = fp16_ieee_to_fp32_value(uint16_t(bits));
            printf("%.6f (0x%08X)", r, fp32_to_bits(r));
        }
        if (strcmp(opString, "-bf16") == 0)
        {
            float f0 = strtof(valueString, nullptr);
            uint16_t r = bf16_from_fp32_round_to_nearest_even(f0);
            float f1 = bf16_to_fp32(r);
            printf("0x%4X (e=%+.6f)", r, f0 - f1);
        }
        if (strcmp(opString, "-bf16rtz") == 0)
        {
            float f0 = strtof(valueString, nullptr);
            uint16_t r = bf16_from_fp32_round_to_zero(f0);
            float f1 = bf16_to_fp32(r);
            printf("0x%4X (e=%+.6f)", r, f0 - f1);
        }
        else if (strcmp(opString, "-bf16hex-fp32") == 0)
        {
            uint32_t bits = strtoul(valueString, nullptr, 16);
            float r = bf16_to_fp32(uint16_t(bits));
            printf("%.6f (0x%08X)", r, fp32_to_bits(r));
        }
        if ((strcmp(opString, "-fp8") == 0) ||
            (strcmp(opString, "-fp8e4m3") == 0))
        {
            float f0 = strtof(valueString, nullptr);
            uint8_t r = fp8e4m3fn_from_fp32_value(f0);
            float f1 = fp8e4m3fn_to_fp32_value(r);
            printf("0x%2X (e=%+.6f)", r, f0 - f1);
        }
        else if ((strcmp(opString, "-fp8hex-fp32") == 0) ||
            (strcmp(opString, "-fp8e4m3hex-fp32") == 0))
        {
            uint32_t bits = strtoul(valueString, nullptr, 16);
            float r = fp8e4m3fn_to_fp32_value(uint8_t(bits));
            printf("%.6f (0x%08X)", r, fp32_to_bits(r));
        }
        if ((strcmp(opString, "-bf8") == 0) ||
            (strcmp(opString, "-fp8e5m2") == 0))
        {
            float f0 = strtof(valueString, nullptr);
            uint8_t r = fp8e5m2_from_fp32_value(f0);
            float f1 = fp8e5m2_to_fp32_value(r);
            printf("0x%2X (e=%+.6f)", r, f0 - f1);
        }
        else if ((strcmp(opString, "-bf8hex-fp32") == 0) ||
            (strcmp(opString, "-fp8e5m2hex-fp32") == 0))
        {
            uint32_t bits = strtoul(valueString, nullptr, 16);
            float r = fp8e5m2_to_fp32_value(uint8_t(bits));
            printf("%.6f (0x%08X)", r, fp32_to_bits(r));
        }
    }
    else
    {
        print_help();
    }
    return 0;
}
