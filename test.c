/* Simple unit test for mybit.h */
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "mybit.h"

int main(void) {
    uint32_t x = 0x11223344u;
    uint32_t y = mybit_bswap32(x);
    assert(y == 0x44332211u);
    assert(mybit_bswap32(y) == x);

    uint16_t a = 0x1234u;
    assert(mybit_bswap16(a) == 0x3412u);

    uint64_t z = 0x0102030405060708ULL;
    assert(mybit_bswap64(z) == 0x0807060504030201ULL);

    assert(mybit_clz32(0u) == 32u);
    assert(mybit_clz32(1u) == 31u);
    assert(mybit_clz32(0x80000000u) == 0u);

    assert(mybit_ctz32(0u) == 32u);
    assert(mybit_ctz32(1u) == 0u);
    assert(mybit_ctz32(0x1000u) == 12u);

    assert(mybit_popcount32(0u) == 0u);
    assert(mybit_popcount32(0xF0F0F0F0u) == 16u);

    assert(mybit_rotl32(0x12345678u, 8u) == 0x34567812u);
    assert(mybit_rotr32(0x12345678u, 8u) == 0x78123456u);
    assert(mybit_reverse32(0xF0F0F0F0u) == 0x0F0F0F0Fu);

    assert(mybit_clz64(0ULL) == 64u);
    assert(mybit_clz64(1ULL) == 63u);
    assert(mybit_ctz64(0ULL) == 64u);
    assert(mybit_ctz64(8ULL) == 3u);

    assert(mybit_popcount64(0xFF00FF00FF00FF00ULL) == 32u);
    assert(mybit_rotl64(0x0123456789ABCDEFULL, 4u) == 0x123456789ABCDEF0ULL);
    assert(mybit_rotr64(0x0123456789ABCDEFULL, 4u) == 0xF0123456789ABCDEULL);
    assert(mybit_reverse64(1ULL) == 0x8000000000000000ULL);

    assert(mybit_has_single_bit32(0x1000u));
    assert(!mybit_has_single_bit32(0x1001u));
    assert(mybit_bit_floor32(0x12345678u) == 0x10000000u);
    assert(mybit_bit_ceil32(0x12345678u) == 0x20000000u);
    assert(mybit_bit_floor64(0x1000000000000ULL) == 0x1000000000000ULL);
    assert(mybit_bit_ceil64(0x1000000000001ULL) == 0x2000000000000ULL);
    assert(mybit_countl_one32(0xFFFF0000u) == 16u);
    assert(mybit_countr_one32(0x0000FFFFu) == 16u);
    assert(mybit_countl_one64(0xFFFFFFFF00000000ULL) == 32u);
    assert(mybit_countr_one64(0x00000000FFFFFFFFULL) == 32u);

    /* C _Generic dispatch tests: unsigned long / unsigned long long */
    unsigned long ul = (unsigned long)0x0000FFFFu;
    unsigned long long ull = (unsigned long long)0x00000000FFFFFFFFULL;
    assert(mybit_countl_one(ul) == mybit_countl_one32((uint32_t)ul));
    assert(mybit_countl_one(ull) == mybit_countl_one64((uint64_t)ull));

    assert(mybit_bswap((uint32_t)0x11223344u) == 0x44332211u);

    uint8_t buf[8];
    mybit_store_le32(buf, 0x12345678u);
    assert(buf[0] == 0x78u);
    assert(buf[1] == 0x56u);
    assert(buf[2] == 0x34u);
    assert(buf[3] == 0x12u);
    assert(mybit_load_le32(buf) == 0x12345678u);

    mybit_store_be32(buf, 0x12345678u);
    assert(buf[0] == 0x12u);
    assert(buf[1] == 0x34u);
    assert(buf[2] == 0x56u);
    assert(buf[3] == 0x78u);
    assert(mybit_load_be32(buf) == 0x12345678u);

#if MYBIT_IS_LITTLE_ENDIAN
    /* On little-endian, littleswap is identity */
    assert(littleswap32(x) == x);
#else
    assert(littleswap32(x) == mybit_bswap32(x));
#endif

    printf("mybit: ok\n");
    return 0;
}
