/*
 * Copyright (c) 2026 GeraPro2_0
 *
 * Licence: MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MYBIT_H
#define MYBIT_H

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__cplusplus) || defined(_MSC_VER)
    #include <stdint.h>
#else
    #if !defined(_STDINT_H) && !defined(_STDINT_H_) && !defined(_GCC_STDINT_H) && !defined(__stdint_h__)
        #define _STDINT_H
        #define _STDINT_H_
        #define _GCC_STDINT_H
        #define __stdint_h__

        typedef unsigned char      uint8_t;
        typedef unsigned short     uint16_t;
        typedef unsigned int       uint32_t;
        #if defined(__GNUC__) || defined(__clang__)
            typedef unsigned long long uint64_t;
        #else
            typedef unsigned __int64   uint64_t;
        #endif
    #endif
#endif

#if defined(_MSC_VER)
    #include <intrin.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MYBIT_ASSUME_LITTLE_ENDIAN)
    /* Allow explicit override for cross-compilation */
    #if MYBIT_ASSUME_LITTLE_ENDIAN
        #define MYBIT_IS_LITTLE_ENDIAN 1
    #else
        #define MYBIT_IS_LITTLE_ENDIAN 0
    #endif
#elif defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__)
    #define MYBIT_IS_LITTLE_ENDIAN (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#elif defined(_WIN32) || defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
    #define MYBIT_IS_LITTLE_ENDIAN 1
#else
    #define MYBIT_IS_LITTLE_ENDIAN 1
#endif

#if defined(_MSC_VER)
    #define MYBIT_INLINE static __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define MYBIT_INLINE static inline __attribute__((always_inline))
#else
    #define MYBIT_INLINE static inline
#endif

#include <stddef.h>

/* Feature detection: prefer C11 when available */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define MYBIT_HAS_C11 1
#else
#define MYBIT_HAS_C11 0
#endif

/* Portable static assert for pre-C11 compilers */
#define MYBIT_CONCAT(a,b) MYBIT_CONCAT1(a,b)
#define MYBIT_CONCAT1(a,b) a##b
#if MYBIT_HAS_C11
#define MYBIT_STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
#else
#define MYBIT_STATIC_ASSERT(cond, msg) typedef char MYBIT_CONCAT(static_assert_, __LINE__)[(cond) ? 1 : -1]
#endif

/* core byte-swap functions with mybit_ prefix to avoid collisions */
MYBIT_INLINE uint16_t mybit_bswap16(uint16_t x) {
#if defined(__GNUC__) || defined(__clang__)
    return __builtin_bswap16(x);
#elif defined(_MSC_VER)
    return _byteswap_ushort(x);
#else
    return (uint16_t)((x << 8) | (x >> 8));
#endif
}

MYBIT_INLINE uint32_t mybit_bswap32(uint32_t x) {
#if defined(__GNUC__) || defined(__clang__)
    return __builtin_bswap32(x);
#elif defined(_MSC_VER)
    return _byteswap_ulong(x);
#else
    return ((x & 0x000000FF) << 24) |
           ((x & 0x0000FF00) << 8)  |
           ((x & 0x00FF0000) >> 8)  |
           ((x & 0xFF000000) >> 24);
#endif
}

MYBIT_INLINE uint64_t mybit_bswap64(uint64_t x) {
#if defined(__GNUC__) || defined(__clang__)
    return __builtin_bswap64(x);
#elif defined(_MSC_VER)
    return _byteswap_uint64(x);
#else
    return ((x & 0x00000000000000FFULL) << 56) |
           ((x & 0x000000000000FF00ULL) << 48) |
           ((x & 0x0000000000FF0000ULL) << 40) |
           ((x & 0x00000000FF000000ULL) << 32) |
           ((x & 0x000000FF00000000ULL) >>  8) |
           ((x & 0x0000FF0000000000ULL) >> 24) |
           ((x & 0x00FF000000000000ULL) >> 40) |
           ((x & 0xFF00000000000000ULL) >> 56);
#endif
}

#if !defined(__cplusplus) && MYBIT_HAS_C11
    #define mybit_bswap(x) _Generic((x), \
        uint16_t: mybit_bswap16, \
        uint32_t: mybit_bswap32, \
        uint64_t: mybit_bswap64 \
    )(x)
#else
    /* Fallback for pre-C11: use sizeof-based ternary to dispatch at compile-time */
    #define mybit_bswap(x) (sizeof(x) <= 2 ? mybit_bswap16((uint16_t)(x)) : (sizeof(x) <= 4 ? mybit_bswap32((uint32_t)(x)) : mybit_bswap64((uint64_t)(x))))
#endif

/* Provide helpers for unsigned long / unsigned long long so _Generic can
   dispatch on common C typedefs whose width may vary by platform. */
MYBIT_INLINE uint64_t mybit_bswap_ul(unsigned long x) {
    if (sizeof(unsigned long) <= 4)
        return (uint32_t)mybit_bswap32((uint32_t)x);
    return mybit_bswap64((uint64_t)x);
}

MYBIT_INLINE uint64_t mybit_bswap_ull(unsigned long long x) {
    if (sizeof(unsigned long long) <= 4)
        return (uint32_t)mybit_bswap32((uint32_t)x);
    return mybit_bswap64((uint64_t)x);
}

#if MYBIT_HAS_C11
    #undef mybit_bswap
    #define mybit_bswap(x) _Generic((x), \
        uint16_t: mybit_bswap16, \
        uint32_t: mybit_bswap32, \
        uint64_t: mybit_bswap64, \
        unsigned int: mybit_bswap32, \
        unsigned long: mybit_bswap_ul, \
        unsigned long long: mybit_bswap_ull, \
        size_t: mybit_bswap_ul \
    )(x)
#else
    /* If no _Generic, provide a safer sizeof-based macro that handles common typedefs */
    #undef mybit_bswap
    #define mybit_bswap(x) (sizeof(x) <= 2 ? mybit_bswap16((uint16_t)(x)) : (sizeof(x) <= 4 ? mybit_bswap32((uint32_t)(x)) : mybit_bswap64((uint64_t)(x))))
#endif

/* Basic compile-time sanity checks */
#include <limits.h>
/* Sanity checks (use portable MYBIT_STATIC_ASSERT where available) */
MYBIT_STATIC_ASSERT(CHAR_BIT == 8, "mybit.h requires 8-bit bytes");
MYBIT_STATIC_ASSERT(sizeof(uint16_t) == 2, "uint16_t must be 2 bytes");
MYBIT_STATIC_ASSERT(sizeof(uint32_t) == 4, "uint32_t must be 4 bytes");
MYBIT_STATIC_ASSERT(sizeof(uint64_t) == 8, "uint64_t must be 8 bytes");

/* C wrappers for unsigned long and unsigned long long that dispatch based on
   compile-time size to the proper 32/64-bit implementation. */
MYBIT_INLINE unsigned mybit_countl_one_ul(unsigned long x) {
    if (sizeof(unsigned long) <= 4) return mybit_countl_one32((uint32_t)x);
    return mybit_countl_one64((uint64_t)x);
}

MYBIT_INLINE unsigned mybit_countr_one_ul(unsigned long x) {
    if (sizeof(unsigned long) <= 4) return mybit_countr_one32((uint32_t)x);
    return mybit_countr_one64((uint64_t)x);
}

MYBIT_INLINE unsigned mybit_countl_one_ull(unsigned long long x) {
    if (sizeof(unsigned long long) <= 4) return mybit_countl_one32((uint32_t)x);
    return mybit_countl_one64((uint64_t)x);
}

MYBIT_INLINE unsigned mybit_countr_one_ull(unsigned long long x) {
    if (sizeof(unsigned long long) <= 4) return mybit_countr_one32((uint32_t)x);
    return mybit_countr_one64((uint64_t)x);
}

#if MYBIT_HAS_C11
    #define mybit_countl_one(x) _Generic((x), \
        uint32_t: mybit_countl_one32, \
        uint64_t: mybit_countl_one64, \
        unsigned int: mybit_countl_one32, \
        unsigned long: mybit_countl_one_ul, \
        size_t: mybit_countl_one_ul, \
        unsigned long long: mybit_countl_one_ull \
    )(x)

    #define mybit_countr_one(x) _Generic((x), \
        uint32_t: mybit_countr_one32, \
        uint64_t: mybit_countr_one64, \
        unsigned int: mybit_countr_one32, \
        unsigned long: mybit_countr_one_ul, \
        size_t: mybit_countr_one_ul, \
        unsigned long long: mybit_countr_one_ull \
    )(x)
#else
    /* Fallback for pre-C11: use sizeof-based macro dispatch */
    #define mybit_countl_one(x) (sizeof(x) <= 4 ? mybit_countl_one32((uint32_t)(x)) : mybit_countl_one64((uint64_t)(x)))
    #define mybit_countr_one(x) (sizeof(x) <= 4 ? mybit_countr_one32((uint32_t)(x)) : mybit_countr_one64((uint64_t)(x)))
#endif

/* static assertions to ensure expected type sizes and 8-bit char */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    _Static_assert(sizeof(uint16_t) == 2, "uint16_t must be 2 bytes");
    _Static_assert(sizeof(uint32_t) == 4, "uint32_t must be 4 bytes");
    _Static_assert(sizeof(uint64_t) == 8, "uint64_t must be 8 bytes");
#endif

/* portable bit operations */

MYBIT_INLINE unsigned mybit_clz32(uint32_t x) {
    if (x == 0u) return 32u;
#if defined(__GNUC__) || defined(__clang__)
    return (unsigned)__builtin_clz(x);
#elif defined(_MSC_VER)
    unsigned long index;
    _BitScanReverse(&index, x);
    return 31u - (unsigned)index;
#else
    unsigned n = 0u;
    if ((x & 0xFFFF0000u) == 0u) { n += 16u; x <<= 16; }
    if ((x & 0xFF000000u) == 0u) { n += 8u; x <<= 8; }
    if ((x & 0xF0000000u) == 0u) { n += 4u; x <<= 4; }
    if ((x & 0xC0000000u) == 0u) { n += 2u; x <<= 2; }
    if ((x & 0x80000000u) == 0u) { n += 1u; }
    return n;
#endif
}

MYBIT_INLINE unsigned mybit_ctz32(uint32_t x) {
    if (x == 0u) return 32u;
#if defined(__GNUC__) || defined(__clang__)
    return (unsigned)__builtin_ctz(x);
#elif defined(_MSC_VER)
    unsigned long index;
    _BitScanForward(&index, x);
    return (unsigned)index;
#else
    unsigned n = 0u;
    if ((x & 0x0000FFFFu) == 0u) { n += 16u; x >>= 16; }
    if ((x & 0x000000FFu) == 0u) { n += 8u; x >>= 8; }
    if ((x & 0x0000000Fu) == 0u) { n += 4u; x >>= 4; }
    if ((x & 0x00000003u) == 0u) { n += 2u; x >>= 2; }
    if ((x & 0x00000001u) == 0u) { n += 1u; }
    return n;
#endif
}

MYBIT_INLINE unsigned mybit_popcount32(uint32_t x) {
#if defined(__GNUC__) || defined(__clang__)
    return (unsigned)__builtin_popcount(x);
#elif defined(_MSC_VER)
    return (unsigned)__popcnt(x);
#else
    x = x - ((x >> 1) & 0x55555555u);
    x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
    x = ((x + (x >> 4)) & 0x0F0F0F0Fu);
    return (unsigned)((x * 0x01010101u) >> 24);
#endif
}

MYBIT_INLINE uint32_t mybit_rotl32(uint32_t x, unsigned r) {
    r &= 31u;
    return (x << r) | (x >> ((32u - r) & 31u));
}

MYBIT_INLINE uint32_t mybit_rotr32(uint32_t x, unsigned r) {
    r &= 31u;
    return (x >> r) | (x << ((32u - r) & 31u));
}

MYBIT_INLINE uint32_t mybit_reverse32(uint32_t x) {
    x = ((x >> 1) & 0x55555555u) | ((x & 0x55555555u) << 1);
    x = ((x >> 2) & 0x33333333u) | ((x & 0x33333333u) << 2);
    x = ((x >> 4) & 0x0F0F0F0Fu) | ((x & 0x0F0F0F0Fu) << 4);
    x = ((x >> 8) & 0x00FF00FFu) | ((x & 0x00FF00FFu) << 8);
    return (x >> 16) | (x << 16);
}

MYBIT_INLINE unsigned mybit_clz64(uint64_t x) {
    if (x == 0ULL) return 64u;
#if defined(__GNUC__) || defined(__clang__)
    return (unsigned)__builtin_clzll(x);
#elif defined(_MSC_VER)
    unsigned long index;
    _BitScanReverse64(&index, x);
    return 63u - (unsigned)index;
#else
    unsigned n = 0u;
    if ((x >> 32) == 0ULL) { n += 32u; x <<= 32; }
    if ((x >> 48) == 0ULL) { n += 16u; x <<= 16; }
    if ((x >> 56) == 0ULL) { n += 8u; x <<= 8; }
    if ((x >> 60) == 0ULL) { n += 4u; x <<= 4; }
    if ((x >> 62) == 0ULL) { n += 2u; x <<= 2; }
    if ((x >> 63) == 0ULL) { n += 1u; }
    return n;
#endif
}

MYBIT_INLINE unsigned mybit_ctz64(uint64_t x) {
    if (x == 0ULL) return 64u;
#if defined(__GNUC__) || defined(__clang__)
    return (unsigned)__builtin_ctzll(x);
#elif defined(_MSC_VER)
    unsigned long index;
    _BitScanForward64(&index, x);
    return (unsigned)index;
#else
    unsigned n = 0u;
    if ((x & 0xFFFFFFFFULL) == 0ULL) { n += 32u; x >>= 32; }
    if ((x & 0x0000FFFFULL) == 0ULL) { n += 16u; x >>= 16; }
    if ((x & 0x000000FFULL) == 0ULL) { n += 8u; x >>= 8; }
    if ((x & 0x0000000FULL) == 0ULL) { n += 4u; x >>= 4; }
    if ((x & 0x00000003ULL) == 0ULL) { n += 2u; x >>= 2; }
    if ((x & 0x00000001ULL) == 0ULL) { n += 1u; }
    return n;
#endif
}

MYBIT_INLINE unsigned mybit_popcount64(uint64_t x) {
#if defined(__GNUC__) || defined(__clang__)
    return (unsigned)__builtin_popcountll(x);
#elif defined(_MSC_VER)
    return (unsigned)__popcnt64(x);
#else
    x = x - ((x >> 1) & 0x5555555555555555ULL);
    x = (x & 0x3333333333333333ULL) + ((x >> 2) & 0x3333333333333333ULL);
    x = ((x + (x >> 4)) & 0x0F0F0F0F0F0F0F0FULL);
    return (unsigned)((x * 0x0101010101010101ULL) >> 56);
#endif
}

MYBIT_INLINE uint64_t mybit_rotl64(uint64_t x, unsigned r) {
    r &= 63u;
    return (x << r) | (x >> ((64u - r) & 63u));
}

MYBIT_INLINE uint64_t mybit_rotr64(uint64_t x, unsigned r) {
    r &= 63u;
    return (x >> r) | (x << ((64u - r) & 63u));
}

MYBIT_INLINE uint64_t mybit_reverse64(uint64_t x) {
    x = ((x >> 1) & 0x5555555555555555ULL) | ((x & 0x5555555555555555ULL) << 1);
    x = ((x >> 2) & 0x3333333333333333ULL) | ((x & 0x3333333333333333ULL) << 2);
    x = ((x >> 4) & 0x0F0F0F0F0F0F0F0FULL) | ((x & 0x0F0F0F0F0F0F0F0FULL) << 4);
    x = ((x >> 8) & 0x00FF00FF00FF00FFULL) | ((x & 0x00FF00FF00FF00FFULL) << 8);
    x = ((x >> 16) & 0x0000FFFF0000FFFFULL) | ((x & 0x0000FFFF0000FFFFULL) << 16);
    return (x >> 32) | (x << 32);
}

MYBIT_INLINE unsigned mybit_has_single_bit32(uint32_t x) {
    return x != 0u && (x & (x - 1u)) == 0u;
}

MYBIT_INLINE unsigned mybit_has_single_bit64(uint64_t x) {
    return x != 0ULL && (x & (x - 1ULL)) == 0ULL;
}

MYBIT_INLINE uint32_t mybit_bit_floor32(uint32_t x) {
    return x == 0u ? 0u : (1u << (31u - mybit_clz32(x)));
}

MYBIT_INLINE uint64_t mybit_bit_floor64(uint64_t x) {
    return x == 0ULL ? 0ULL : (1ULL << (63u - mybit_clz64(x)));
}

MYBIT_INLINE uint32_t mybit_bit_ceil32(uint32_t x) {
    if (x == 0u) return 0u;
    x -= 1u;
    x |= x >> 1u;
    x |= x >> 2u;
    x |= x >> 4u;
    x |= x >> 8u;
    x |= x >> 16u;
    return x + 1u;
}

MYBIT_INLINE uint64_t mybit_bit_ceil64(uint64_t x) {
    if (x == 0ULL) return 0ULL;
    x -= 1ULL;
    x |= x >> 1ULL;
    x |= x >> 2ULL;
    x |= x >> 4ULL;
    x |= x >> 8ULL;
    x |= x >> 16ULL;
    x |= x >> 32ULL;
    return x + 1ULL;
}

MYBIT_INLINE unsigned mybit_countl_one32(uint32_t x) {
    return mybit_clz32(~x);
}

MYBIT_INLINE unsigned mybit_countr_one32(uint32_t x) {
    return mybit_ctz32(~x);
}

MYBIT_INLINE unsigned mybit_countl_one64(uint64_t x) {
    return mybit_clz64(~x);
}

MYBIT_INLINE unsigned mybit_countr_one64(uint64_t x) {
    return mybit_ctz64(~x);
}

MYBIT_INLINE uint16_t mybit_load_le16(const void *ptr) {
    const uint8_t *b = (const uint8_t *)ptr;
    return (uint16_t)b[0] | ((uint16_t)b[1] << 8);
}

MYBIT_INLINE uint16_t mybit_load_be16(const void *ptr) {
    const uint8_t *b = (const uint8_t *)ptr;
    return ((uint16_t)b[0] << 8) | (uint16_t)b[1];
}

MYBIT_INLINE uint32_t mybit_load_le32(const void *ptr) {
    const uint8_t *b = (const uint8_t *)ptr;
    return (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
}

MYBIT_INLINE uint32_t mybit_load_be32(const void *ptr) {
    const uint8_t *b = (const uint8_t *)ptr;
    return ((uint32_t)b[0] << 24) | ((uint32_t)b[1] << 16) | ((uint32_t)b[2] << 8) | (uint32_t)b[3];
}

MYBIT_INLINE uint64_t mybit_load_le64(const void *ptr) {
    const uint8_t *b = (const uint8_t *)ptr;
    return (uint64_t)b[0] | ((uint64_t)b[1] << 8) | ((uint64_t)b[2] << 16) | ((uint64_t)b[3] << 24) |
           ((uint64_t)b[4] << 32) | ((uint64_t)b[5] << 40) | ((uint64_t)b[6] << 48) | ((uint64_t)b[7] << 56);
}

MYBIT_INLINE uint64_t mybit_load_be64(const void *ptr) {
    const uint8_t *b = (const uint8_t *)ptr;
    return ((uint64_t)b[0] << 56) | ((uint64_t)b[1] << 48) | ((uint64_t)b[2] << 40) | ((uint64_t)b[3] << 32) |
           ((uint64_t)b[4] << 24) | ((uint64_t)b[5] << 16) | ((uint64_t)b[6] << 8)  | (uint64_t)b[7];
}

MYBIT_INLINE void mybit_store_le16(void *ptr, uint16_t v) {
    uint8_t *b = (uint8_t *)ptr;
    b[0] = (uint8_t)v;
    b[1] = (uint8_t)(v >> 8);
}

MYBIT_INLINE void mybit_store_be16(void *ptr, uint16_t v) {
    uint8_t *b = (uint8_t *)ptr;
    b[0] = (uint8_t)(v >> 8);
    b[1] = (uint8_t)v;
}

MYBIT_INLINE void mybit_store_le32(void *ptr, uint32_t v) {
    uint8_t *b = (uint8_t *)ptr;
    b[0] = (uint8_t)v;
    b[1] = (uint8_t)(v >> 8);
    b[2] = (uint8_t)(v >> 16);
    b[3] = (uint8_t)(v >> 24);
}

MYBIT_INLINE void mybit_store_be32(void *ptr, uint32_t v) {
    uint8_t *b = (uint8_t *)ptr;
    b[0] = (uint8_t)(v >> 24);
    b[1] = (uint8_t)(v >> 16);
    b[2] = (uint8_t)(v >> 8);
    b[3] = (uint8_t)v;
}

MYBIT_INLINE void mybit_store_le64(void *ptr, uint64_t v) {
    uint8_t *b = (uint8_t *)ptr;
    b[0] = (uint8_t)v;
    b[1] = (uint8_t)(v >> 8);
    b[2] = (uint8_t)(v >> 16);
    b[3] = (uint8_t)(v >> 24);
    b[4] = (uint8_t)(v >> 32);
    b[5] = (uint8_t)(v >> 40);
    b[6] = (uint8_t)(v >> 48);
    b[7] = (uint8_t)(v >> 56);
}

MYBIT_INLINE void mybit_store_be64(void *ptr, uint64_t v) {
    uint8_t *b = (uint8_t *)ptr;
    b[0] = (uint8_t)(v >> 56);
    b[1] = (uint8_t)(v >> 48);
    b[2] = (uint8_t)(v >> 40);
    b[3] = (uint8_t)(v >> 32);
    b[4] = (uint8_t)(v >> 24);
    b[5] = (uint8_t)(v >> 16);
    b[6] = (uint8_t)(v >> 8);
    b[7] = (uint8_t)v;
}

#if MYBIT_IS_LITTLE_ENDIAN
    #define littleswap16(x) (x)
    #define littleswap32(x) (x)
    #define littleswap64(x) (x)
    #define littleswap(x)   (x)

    #define bigswap16(x) mybit_bswap16(x)
    #define bigswap32(x) mybit_bswap32(x)
    #define bigswap64(x) mybit_bswap64(x)
    #define bigswap(x)   mybit_bswap(x)
#else
    #define littleswap16(x) mybit_bswap16(x)
    #define littleswap32(x) mybit_bswap32(x)
    #define littleswap64(x) mybit_bswap64(x)
    #define littleswap(x)   mybit_bswap(x)

    #define bigswap16(x) (x)
    #define bigswap32(x) (x)
    #define bigswap64(x) (x)
    #define bigswap(x)   (x)
#endif

#ifdef __cplusplus
}
#endif

#if defined(__cplusplus)
inline uint16_t mybit_bswap(uint16_t x) { return mybit_bswap16(x); }
inline uint32_t mybit_bswap(uint32_t x) { return mybit_bswap32(x); }
inline uint64_t mybit_bswap(uint64_t x) { return mybit_bswap64(x); }

// Helpful constexpr templates for C++: usable at compile-time when possible.
#include <type_traits>

namespace mybit {
    template<typename T>
    using _enable_unsigned = typename std::enable_if<std::is_unsigned<T>::value>::type;

    template<typename T, typename = _enable_unsigned<T>>
    constexpr bool has_single_bit(T x) noexcept { return x != 0 && (x & (x - 1)) == 0; }

    template<typename T, typename = _enable_unsigned<T>>
    constexpr unsigned countl_zero(T x) noexcept {
#if defined(__cpp_lib_is_constant_evaluated) || (defined(__cplusplus) && __cplusplus >= 202002L)
        if (std::is_constant_evaluated()) {
            const unsigned bits = sizeof(T) * 8u;
            unsigned n = 0u;
            for (unsigned i = 0u; i < bits; ++i) {
                if ((x & (T(1) << (bits - 1u - i))) == 0) n++; else break;
            }
            return n;
        }
#endif
        if (x == 0) return sizeof(T) * 8u;
        if (sizeof(T) <= 4u) {
            return mybit_clz32(static_cast<uint32_t>(x)) - (32u - (sizeof(T) * 8u));
        } else {
            return mybit_clz64(static_cast<uint64_t>(x));
        }
    }

    template<typename T, typename = _enable_unsigned<T>>
    constexpr unsigned countl_one(T x) noexcept { return countl_zero(~x); }

    template<typename T, typename = _enable_unsigned<T>>
    constexpr unsigned countr_zero(T x) noexcept {
#if defined(__cpp_lib_is_constant_evaluated) || (defined(__cplusplus) && __cplusplus >= 202002L)
        if (std::is_constant_evaluated()) {
            const unsigned bits = sizeof(T) * 8u;
            unsigned n = 0u;
            for (unsigned i = 0u; i < bits; ++i) {
                if ((x & (T(1) << i)) == 0) n++; else break;
            }
            return n;
        }
#endif
        if (sizeof(T) <= 4u) {
            return mybit_ctz32(static_cast<uint32_t>(x));
        } else {
            return mybit_ctz64(static_cast<uint64_t>(x));
        }
    }

    template<typename T, typename = _enable_unsigned<T>>
    constexpr unsigned countr_one(T x) noexcept { return countr_zero(~x); }

    template<typename T, typename = _enable_unsigned<T>>
    constexpr T bit_floor(T x) noexcept {
        if (x == 0) return 0;
        const unsigned bits = sizeof(T) * 8u;
        unsigned shift = bits - 1u - countl_zero(x);
        return T(1) << shift;
    }

    template<typename T, typename = _enable_unsigned<T>>
    constexpr T bit_ceil(T x) noexcept {
        if (x == 0) return 0;
        T f = bit_floor(x);
        return (f == x) ? f : (f << 1);
    }
}

#endif

#endif