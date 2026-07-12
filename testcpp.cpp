#include <iostream>
#include <cassert>
#include "mybit.h"

int main() {
    // Test C++ overloads for mybit_bswap
    uint32_t x32 = 0x11223344u;
    uint64_t x64 = 0x0102030405060708ULL;

    assert(mybit_bswap(x32) == 0x44332211u);
    assert(mybit_bswap(x64) == 0x0807060504030201ULL);

    // Test C++ namespace helpers
    assert(mybit::has_single_bit<uint32_t>(0x1000u));
    assert(!mybit::has_single_bit<uint32_t>(0x1001u));

    assert(mybit::countl_zero<uint32_t>(1u) == 31u);
    assert(mybit::countr_zero<uint32_t>(1u) == 0u);
    assert(mybit::bit_floor<uint32_t>(0x12345678u) == 0x10000000u);
    assert(mybit::bit_ceil<uint32_t>(0x12345678u) == 0x20000000u);

    assert(mybit::countl_zero<uint64_t>(1ULL) == 63u);
    assert(mybit::countr_zero<uint64_t>(8ULL) == 3u);

    std::cout << "mybit C++ wrappers: ok\n";
    return 0;
}
