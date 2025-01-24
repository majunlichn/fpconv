# Floating-Point Converter

A tool supports floating-point conversions between fp16, bf16, fp8 (fp8e4m3) and bf8 (fp8e5m2).

## Usage

```PowerShell
PS C:\repos\fpconv\build\Debug> .\fpconv.exe -h
Floating-Point Converter

Usage: fpconv Operation Value0,Value1,Value2,...

Supported Operations:
    -fp32:              encode fp32 numbers.
    -fp32hex-fp32:      decode fp32 from hex to decimal.
    -fp64:              encode fp64 numbers.
    -fp64hex-fp64:      decode fp64 from hex to decimal.
    -fp16:              encode fp32 numbers as fp16.
    -fp16hex-fp32:      decode fp16 numbers as fp32.
    -bf16:              encode fp32 numbers as bf16 (round to nearest even).
    -bf16rtz:           encode fp32 numbers as bf16 (round to zero).
    -bf16hex-fp32:      decode bf16 numbers as fp32.
    -fp8:               encode fp32 numbers as fp8 (fp8e4m3).
    -fp8hex-fp32:       decode fp8 (fp8e4m3) numbers as fp32.
    -bf8:               encode fp32 numbers as bf8 (fp8e5m2).
    -bf8hex-fp32:       decode bf8 (fp8e5m2) numbers as fp32.


PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -fp32 0.1,0.2,0.3,0.4
0x3DCCCCCD,0x3E4CCCCD,0x3E99999A,0x3ECCCCCD
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -fp32hex-fp32 0x3DCCCCCD,0x3E4CCCCD,0x3E99999A,0x3ECCCCCD
0.100000,0.200000,0.300000,0.400000
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -fp64 0.1,0.2,0.3,0.4
0x3FB999999999999A,0x3FC999999999999A,0x3FD3333333333333,0x3FD999999999999A
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -fp64hex-fp64 0x3FB999999999999A,0x3FC999999999999A,0x3FD3333333333333,0x3FD999999999999A
0.100000,0.200000,0.300000,0.400000
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -fp16 0.1,0.2,0.3,0.4
0x2E66,0x3266,0x34CD,0x3666
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -fp16hex-fp32 0x2E66,0x3266,0x34CD,0x3666
0.099976,0.199951,0.300049,0.399902
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -bf16 0.1,0.2,0.3,0.4
0x3DCD,0x3E4D,0x3E9A,0x3ECD
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -bf16rtz 0.1,0.2,0.3,0.4
0x3DCC,0x3E4C,0x3E99,0x3ECC
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -bf16hex-fp32 0x3DCD,0x3E4D,0x3E9A,0x3ECD
0.100098,0.200195,0.300781,0.400391
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -bf16hex-fp32 0x3DCC,0x3E4C,0x3E99,0x3ECC
0.099609,0.199219,0.298828,0.398438
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -fp8 0.1,0.2,0.3,0.4
0x1D,0x25,0x2A,0x2D
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -fp8hex-fp32 0x1D,0x25,0x2A,0x2D
0.101562,0.203125,0.312500,0.406250
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -bf8 0.1,0.2,0.3,0.4
0x2E,0x32,0x35,0x36
PS C:\repos\fpconv\x64\Debug> .\fpconv.exe -bf8hex-fp32 0x2E,0x32,0x35,0x36
0.093750,0.187500,0.312500,0.375000
```

## Build

On Windows, with Visual Studio 2022 you can directly open the solution and build.

For other platforms, you can use CMake to generate project files and build:

```bash
cmake -S . -B build
cmake --build build --config Release
```

You can also directly compile from the sources, just remember to set C++ standard to 20:

```bash
g++ -std=c++20 -o fpconv common.cpp fp16.cpp bf16.cpp fp8.cpp main.cpp
```
