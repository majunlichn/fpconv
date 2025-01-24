#include "common.h"
#include <format>

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

void print_help();
std::string fpconvert(const std::string& operation, const std::vector<std::string>& tokens);

int main(int argc, char** argv)
{
    if (argc > 1)
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
        const char* operation = argv[1];
        std::vector<std::string> tokens = StrSplit(argv[2], ",", false);
        try
        {
            std::string output = fpconvert(operation, tokens);
            printf("%s", output.c_str());
            fflush(stdout);
        }
        catch (...)
        {
            return -1;
        }
    }
    else
    {
        print_help();
    }
    return 0;
}

void print_help()
{
    printf("Floating-Point Converter\n\n");
    printf("Usage: fpconv [Operation] [Value0,Value1,Value2,...]\n\n");
    printf("Supported Operations:\n");
    printf("    -fp32:              encode fp32 numbers.\n");
    printf("    -fp32hex-fp32:      decode fp32 from hex to decimal.\n");
    printf("    -fp64:              encode fp64 numbers.\n");
    printf("    -fp64hex-fp64:      decode fp64 from hex to decimal.\n");
    printf("    -fp16:              encode fp32 numbers as fp16.\n");
    printf("    -fp16hex-fp32:      decode fp16 numbers as fp32.\n");
    printf("    -bf16:              encode fp32 numbers as bf16 (round to nearest even).\n");
    printf("    -bf16rtz:           encode fp32 numbers as bf16 (round to zero).\n");
    printf("    -bf16hex-fp32:      decode bf16 numbers as fp32.\n");
    printf("    -fp8:               encode fp32 numbers as fp8 (fp8e4m3).\n");
    printf("    -fp8hex-fp32:       decode fp8 (fp8e4m3) numbers as fp32.\n");
    printf("    -bf8:               encode fp32 numbers as bf8 (fp8e5m2).\n");
    printf("    -bf8hex-fp32:       decode bf8 (fp8e5m2) numbers as fp32.\n");
    printf("\n\n");
}

std::string fpconvert(const std::string& operation, const std::vector<std::string>& tokens)
{
    std::string output;
    if (operation == "-fp32")
    {
        for (const std::string& token : tokens)
        {
            float fp32 = std::stof(token.c_str(), nullptr);
            uint32_t hex = bit_cast<uint32_t>(fp32);
            output += std::format("0x{:8X}", hex);
            output += ",";
        }
        output.pop_back();
    }
    else if (operation == "-fp32hex-fp32")
    {
        for (const std::string& token : tokens)
        {
            uint32_t hex = std::stoul(token.c_str(), nullptr, 16);
            float fp32 = bit_cast<float>(hex);
            output += std::format("{:.6f}", fp32);
            output += ",";
        }
        output.pop_back();
    }
    else if (operation == "-fp64")
    {
        for (const std::string& token : tokens)
        {
            double fp64 = std::stod(token.c_str(), nullptr);
            uint64_t hex = bit_cast<uint64_t>(fp64);
            output += std::format("0x{:16X}", hex);
            output += ",";
        }
        output.pop_back();
    }
    else if (operation == "-fp64hex-fp64")
    {
        for (const std::string& token : tokens)
        {
            uint64_t hex = std::stoull(token.c_str(), nullptr, 16);
            double fp64 = bit_cast<double>(hex);
            output += std::format("{:.6f}", fp64);
            output += ",";
        }
        output.pop_back();
    }
    else if (operation == "-fp16")
    {
        for (const std::string& token : tokens)
        {
            float fp32 = std::stof(token.c_str(), nullptr);
            uint16_t fp16 = fp16_ieee_from_fp32_value(fp32);
            output += std::format("0x{:4X}", fp16);
            output += ",";
        }
        output.pop_back();
    }
    else if (operation == "-fp16hex-fp32")
    {
        for (const std::string& token : tokens)
        {
            uint16_t hex = static_cast<uint16_t>(std::stoul(token.c_str(), nullptr, 16));
            float fp32 = fp16_ieee_to_fp32_value(hex);
            output += std::format("{:.6f}", fp32);
            output += ",";
        }
        output.pop_back();
    }
    else if (operation == "-bf16")
    {
        for (const std::string& token : tokens)
        {
            float fp32 = std::stof(token.c_str(), nullptr);
            uint16_t bf16 = bf16_from_fp32_round_to_nearest_even(fp32);
            output += std::format("0x{:4X}", bf16);
            output += ",";
        }
        output.pop_back();
    }
    else if (operation == "-bf16rtz")
    {
        for (const std::string& token : tokens)
        {
            float fp32 = std::stof(token.c_str(), nullptr);
            uint16_t bf16 = bf16_from_fp32_round_to_zero(fp32);
            output += std::format("0x{:4X}", bf16);
            output += ",";
        }
        output.pop_back();
    }
    else if (operation == "-bf16hex-fp32")
    {
        for (const std::string& token : tokens)
        {
            uint16_t hex = static_cast<uint16_t>(std::stoul(token.c_str(), nullptr, 16));
            float fp32 = bf16_to_fp32(hex);
            output += std::format("{:.6f}", fp32);
            output += ",";
        }
        output.pop_back();
    }
    else if ((operation == "-fp8") ||
        (operation == "-fp8e4m3"))
    {
        for (const std::string& token : tokens)
        {
            float fp32 = std::stof(token.c_str(), nullptr);
            uint8_t fp8 = fp8e4m3fn_from_fp32_value(fp32);
            output += std::format("0x{:2X}", fp8);
            output += ",";
        }
        output.pop_back();
    }
    else if ((operation == "-fp8hex-fp32") ||
        (operation == "-fp8e4m3hex-fp32"))
    {
        for (const std::string& token : tokens)
        {
            uint8_t hex = static_cast<uint8_t>(std::stoul(token.c_str(), nullptr, 16));
            float fp32 = fp8e4m3fn_to_fp32_value(hex);
            output += std::format("{:.6f}", fp32);
            output += ",";
        }
        output.pop_back();
    }
    else if ((operation == "-bf8") ||
        (operation == "-fp8e5m2"))
    {
        for (const std::string& token : tokens)
        {
            float fp32 = std::stof(token.c_str(), nullptr);
            uint8_t bf8 = fp8e5m2_from_fp32_value(fp32);
            output += std::format("0x{:2X}", bf8);
            output += ",";
        }
        output.pop_back();
    }
    else if ((operation == "-bf8hex-fp32") ||
        (operation == "-fp8e5m2hex-fp32"))
    {
        for (const std::string& token : tokens)
        {
            uint8_t hex = static_cast<uint8_t>(std::stoul(token.c_str(), nullptr, 16));
            float fp32 = fp8e5m2_to_fp32_value(hex);
            output += std::format("{:.6f}", fp32);
            output += ",";
        }
        output.pop_back();
    }
    else
    {
        printf("Invalid operation! Run \"fpconv -h\" for help.\n");
    }
    return output;
}
