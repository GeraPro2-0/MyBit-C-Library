/* Simple unit test for mybit.h using C++ features */
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

    assert(mybit::popcount<uint32_t>(0x00000000u) == 0u);
    assert(mybit::popcount<uint32_t>(0xF0F0F0F0u) == 16u);
    assert(mybit::popcount<uint64_t>(0xFFFFFFFFFFFFFFFFULL) == 64u);

    assert(mybit::byteswap<uint16_t>(0x1234u) == 0x3412u);
    assert(mybit::byteswap<uint32_t>(0x11223344u) == 0x44332211u);
    assert(mybit::byteswap<uint64_t>(0x0102030405060708ULL) == 0x0807060504030201ULL);

    uint32_t rot_val = 0x80000001u;
    assert(mybit::rotl(rot_val, 1u) == 0x00000003u);
    assert(mybit::rotr(0x00000003u, 1u) == 0x80000001u);

#if MYBIT_IS_LITTLE_ENDIAN
    assert(mybit::endian::native == mybit::endian::little);
#else
    assert(mybit::endian::native == mybit::endian::big);
#endif

    float float_val = 1.0f;
    uint32_t casted_int = mybit::bit_cast<uint32_t>(float_val);
    assert(casted_int == 0x3F800000u);
    
    float casted_float = mybit::bit_cast<float>(casted_int);
    assert(casted_float == 1.0f);

    std::cout << "mybit C++ wrappers: ok\n";
    return 0;
}