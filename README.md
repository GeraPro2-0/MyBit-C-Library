# MyBit

## mybit.h — tiny header-only byte-swap utilities

Usage:

- Include the header in your C or C++ project:

  #include "mybit.h"

- Example: compile and run the test:

  - GCC:
    gcc -std=c11 -O2 test.c -o test_mybit ; ./test_mybit
    g++ -std=c++11 -O2 testcpp.cpp -o testcpp_mybit ; ./testcpp_mybit
  ----------------------------------------------------------------------------
  - Clang:
    clang -std=c11 -O2 test.c -o test_mybit ; ./test_mybit
    clang++ -std=c++11 -O2 testcpp.cpp -o testcpp_mybit ; ./testcpp_mybit
  ----------------------------------------------------------------------------
  - MSVC:
    cl /std:c11 /O2 test.c /Fe:test_mybit.exe && test_mybit.exe
    cl /std:c++14 /O2 testcpp.cpp /Fe:testcpp_mybit.exe && testcpp_mybit.exe

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

## Added in this update

This release adds full 8-bit and 16-bit counterparts for the existing 32/64-bit helpers, generic C wrappers, and C++ overloads/templates.

- **8-bit helpers:** `mybit_clz8`, `mybit_ctz8`, `mybit_popcount8`, `mybit_rotl8`, `mybit_rotr8`, `mybit_reverse8`, `mybit_has_single_bit8`, `mybit_bit_floor8`, `mybit_bit_ceil8`, plus `mybit_load_le8`/`mybit_load_be8` and `mybit_store_le8`/`mybit_store_be8`.
- **16-bit helpers:** `mybit_clz16`, `mybit_ctz16`, `mybit_popcount16`, `mybit_rotl16`, `mybit_rotr16`, `mybit_reverse16`, `mybit_has_single_bit16`, `mybit_bit_floor16`, `mybit_bit_ceil16`, plus endian load/store `mybit_load_le16`/`mybit_load_be16` and `mybit_store_le16`/`mybit_store_be16`.
- **C generic wrappers:** When compiling as C11 the header exposes `_Generic` wrappers such as `mybit_clz(x)`, `mybit_ctz(x)`, `mybit_popcount(x)`, `mybit_rotl(x, r)`, `mybit_rotr(x, r)`, `mybit_reverse(x)`, `mybit_bit_floor(x)`, `mybit_bit_ceil(x)`, and `mybit_has_single_bit(x)` that dispatch to the correct width (8/16/32/64). Pre-C11 builds use sizeof-based macro fallbacks to provide the same convenience.
- **C++ wrappers and templates:** C++ builds provide overloads and `constexpr` templates in the `mybit` namespace (e.g., `mybit::popcount`, `mybit::countl_zero`, `mybit::countr_zero`, `mybit::rotl`, `mybit::reverse`, `mybit::bit_floor`, `mybit::bit_ceil`, `mybit::load_le`, `mybit::store_le`, `mybit::pext`, `mybit::pdep`). These are enabled for unsigned integer types and provide type-safe, constexpr-capable alternatives to the C macros.

Example (C):

```
#include "mybit.h"
uint32_t x = 0x0F00;
int leading = mybit_clz(x); // dispatches to mybit_clz32
```

Example (C++):

```
#include "mybit.h"
using namespace mybit;
constexpr auto p = popcount(uint32_t{0xFF00});
constexpr auto f = bit_floor(uint32_t{15});
```
