# MyBit

## mybit.h — tiny header-only byte-swap utilities

Usage:

- Include the header in your C or C++ project:

  #include "mybit.h"

- Example: compile and run the test:

  cc -std=c11 -O2 tests/test_mybit.c -o bin/test_mybit
  ./bin/test_mybit

- Compatible versions:

  C: Compatible from C89/C90 onwards.
  C++ (using ONLY C functions): Compatible from C++98 onwards.
  C++ (using C++'s own features): Compatible from C++14 or C++11 onwards (with caution).

- Freestanding:

  Since this library does not depend on an operating system (there is no stdlib.h or stdio.h, i.e., freestanding), it can be used anywhere, on any operating system, in a driver, in a kernel, and even in the firmware of a microchip without an OS (bare-metal).

## Features
- **Header-only**: Drop `mybit.h` into your project and you are ready to go.
- **Portability**: Supports C (pre-C11 fallback, C11 `_Generic`) and C++ (C++11 up to C++20 `constexpr` templates).
- **Hardware Acceleration**: Automatically detects and uses compiler builtins...
- **Safe Macro Evaluation**: Fully protected against macro double-evaluation side effects (e.g., safely pass expressions like `mybit_bswap(*ptr++)` even in older pre-C11 compilers).
- **Signed Integer Support**: Robust type casting rules seamlessly handle signed integers (`int`, `short`, `long long`) by forcing logical bitwise operations, eliminating compiler-specific undefined behaviors like arithmetic right-shift sign extensions.

Notes:
- Defines `mybit_bswap16`, `mybit_bswap32`, `mybit_bswap64`, plus a generic `mybit_bswap(x)` wrapper for C and C++.
- Defines portable bit utilities:
  - `mybit_has_single_bit32`, `mybit_bit_floor32`, `mybit_bit_ceil32`
  - `mybit_has_single_bit64`, `mybit_bit_floor64`, `mybit_bit_ceil64`
  - `mybit_clz32`, `mybit_ctz32`, `mybit_popcount32`, `mybit_rotl32`, `mybit_rotr32`, `mybit_reverse32`
  - `mybit_clz64`, `mybit_ctz64`, `mybit_popcount64`, `mybit_rotl64`, `mybit_rotr64`, `mybit_reverse64`
- Endian load/store helpers:
  - `mybit_load_le16`, `mybit_store_le16`, `mybit_load_be16`, `mybit_store_be16`
  - `mybit_load_le32`, `mybit_store_le32`, `mybit_load_be32`, `mybit_store_be32`
  - `mybit_load_le64`, `mybit_store_le64`, `mybit_load_be64`, `mybit_store_be64`
- This library intentionally does not expose legacy `byteswap*` symbols to avoid
  collisions; add your own compatibility aliases if you need them.
 - Additional helpers:
   - `mybit_countl_one32`, `mybit_countr_one32`, `mybit_countl_one64`, `mybit_countr_one64`
   - C++ `constexpr` templates in namespace `mybit` for `countl_one`, `countr_one`, `bit_floor`, `bit_ceil`, `has_single_bit`, etc.
- Define `MYBIT_ASSUME_LITTLE_ENDIAN` to 1 or 0 to override endianness detection for cross-compilation.
