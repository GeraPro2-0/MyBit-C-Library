#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mybit.h"

int main(void) {
    printf("--- Starting mybit verification tests (C) ---\n\n");

    uint8_t a8 = 0xF0u; /* 11110000 */
    uint16_t a16 = 0xF0F0u;
    uint32_t a32 = 0x0000FF00u;
    uint64_t a64 = 0x123456789ABCDEF0ULL;

    /* Bit counting */
    printf("popcount8: %u\n", mybit_popcount8(a8));
    printf("clz8: %u\n", mybit_clz8(a8));
    printf("ctz8: %u\n\n", mybit_ctz8(a8));

    printf("popcount16: %u\n", mybit_popcount16(a16));
    printf("clz16: %u\n", mybit_clz16(a16));
    printf("ctz16: %u\n\n", mybit_ctz16(a16));

    printf("popcount32: %u\n", mybit_popcount32(a32));
    printf("clz32: %u\n", mybit_clz32(a32));
    printf("ctz32: %u\n\n", mybit_ctz32(a32));

    printf("popcount64: %u\n", mybit_popcount64(a64));
    printf("clz64: %u\n", mybit_clz64(a64));
    printf("ctz64: %u\n\n", mybit_ctz64(a64));

    /* Rotations and reverse */
    printf("rotl8: 0x%02X\n", mybit_rotl8(a8, 4));
    printf("rotr8: 0x%02X\n", mybit_rotr8(a8, 4));
    printf("reverse8: 0x%02X\n\n", mybit_reverse8(a8));

    printf("rotl16: 0x%04X\n", mybit_rotl16(a16, 8));
    printf("reverse16: 0x%04X\n\n", mybit_reverse16(a16));

    printf("rotl32: 0x%08X\n", mybit_rotl32(a32, 8));
    printf("reverse32: 0x%08X\n\n", mybit_reverse32(a32));

    printf("rotl64: 0x%016llX\n", (unsigned long long)mybit_rotl64(a64, 16));
    printf("reverse64: 0x%016llX\n\n", (unsigned long long)mybit_reverse64(a64));

    /* Bit floor/ceil/has_single_bit */
    printf("bit_floor8(0x3A): 0x%02X\n", mybit_bit_floor8(0x3A));
    printf("bit_ceil8(0x3A): 0x%02X\n", mybit_bit_ceil8(0x3A));
    printf("has_single_bit8(0x20): %u\n\n", mybit_has_single_bit8(0x20));

    printf("bit_floor16(0x03F0): 0x%04X\n", mybit_bit_floor16(0x03F0));
    printf("bit_ceil16(0x03F0): 0x%04X\n\n", mybit_bit_ceil16(0x03F0));

    printf("bit_floor32(15): %u\n", mybit_bit_floor32(15));
    printf("bit_ceil32(15): %u\n\n", mybit_bit_ceil32(15));

    /* Endian loads/stores */
    uint8_t buf8[8];
    uint16_t v16 = 0xABCDu;
    mybit_store_le16(buf8, v16);
    printf("load_le16 from buf: 0x%04X\n", mybit_load_le16(buf8));
    mybit_store_be16(buf8, v16);
    printf("load_be16 from buf: 0x%04X\n\n", mybit_load_be16(buf8));

    mybit_store_le8(buf8, 0x7Fu);
    printf("load_le8: 0x%02X\n", mybit_load_le8(buf8));
    mybit_store_be8(buf8, 0x7Fu);
    printf("load_be8: 0x%02X\n\n", mybit_load_be8(buf8));

    /* bswap */
    printf("bswap16: 0x%04X\n", mybit_bswap16(0x1234));
    printf("bswap32: 0x%08X\n", mybit_bswap32(0x12345678));
    printf("bswap64: 0x%016llX\n\n", (unsigned long long)mybit_bswap64(0x0102030405060708ULL));

    /* BMI2 PEXT/PDEP */
    printf("pext32: 0x%08X\n", mybit_pext32(0x12345678u, 0x00FF0000u));
    printf("pdep32: 0x%08X\n\n", mybit_pdep32(0x000000FFu, 0x0F0F0000u));

    printf("--- mybit verification tests (C) completed successfully ---\n");
    return 0;
}
