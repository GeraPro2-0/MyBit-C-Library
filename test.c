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
    assert(mybit_ctz32(0x80000000u) == 31u);

    assert(mybit_popcount32(0u) == 0u);
    assert(mybit_popcount32(0xFFFFFFFFu) == 32u);
    assert(mybit_popcount32(0x00F000FFu) == 12u);

    assert(mybit_clz64(0ULL) == 64u);
    assert(mybit_clz64(1ULL) == 63u);
    assert(mybit_clz64(0x8000000000000000ULL) == 0u);

    assert(mybit_ctz64(0ULL) == 64u);
    assert(mybit_ctz64(1ULL) == 0u);
    assert(mybit_ctz64(0x8000000000000000ULL) == 63u);

    assert(mybit_popcount64(0ULL) == 0u);
    assert(mybit_popcount64(0xFFFFFFFFFFFFFFFFULL) == 64u);

    assert(mybit_has_single_bit32(0x1000u) == 1);
    assert(mybit_has_single_bit32(0x1001u) == 0);
    assert(mybit_has_single_bit64(0x1000000000000ULL) == 1);
    assert(mybit_has_single_bit64(0x1000000000001ULL) == 0);

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

    uint32_t p32 = 0xF0F0F0F0u;
    uint64_t p64 = 0xFFFFFFFFFFFFFFFFULL;
    assert(mybit_popcount(p32) == 16u);
    assert(mybit_popcount(p64) == 64u);

    uint16_t b16 = 0x1234u;
    assert(mybit_bswap(b16) == 0x3412u);
    assert(mybit_bswap(p32) == 0x0F0F0F0Fu);
    assert(mybit_bswap(p64) == 0xFFFFFFFFFFFFFFFFULL);

    uint32_t rot32 = 0x80000001u;
    uint64_t rot64 = 0x8000000000000001ULL;

    assert(mybit_rotl(rot32, 1u) == 0x00000003u);
    assert(mybit_rotl(rot64, 1u) == 0x00000003ULL);

    assert(mybit_rotr(0x00000003u, 1u) == 0x80000001u);
    assert(mybit_rotr(0x00000003ULL, 1u) == 0x8000000000000001ULL);

    int32_t signed_neg = -1;
    assert(mybit_countl_one(signed_neg) == 32);
    assert(mybit_countr_one(signed_neg) == 32);
    
    int16_t short_neg = -1;
    assert(mybit_bswap(short_neg) == (int16_t)0xFFFF);

    uint32_t array_bswap[] = { 0x11223344, 0x55667788 };
    uint32_t *ptr_bswap = array_bswap;
    
    uint32_t res_bswap = mybit_bswap(*ptr_bswap++); 
    assert(res_bswap == 0x44332211);
    assert(ptr_bswap == &array_bswap[1]);

    uint32_t array_count[] = { 0xFFFFFFFF, 0x00000000 };
    uint32_t *ptr_count = array_count;
    
    uint32_t res_count = mybit_countl_one(*ptr_count++);
    assert(res_count == 32);
    assert(ptr_count == &array_count[1]);

    printf("All C tests passed successfully!\n");
    return 0;
}