#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include "mybit.h"

int main() {
    std::cout << "--- Starting mybit verification tests (C++) ---\n\n";
    std::cout << std::hex << std::uppercase << std::setfill('0');

    uint8_t a8 = 0xF0u;
    uint16_t a16 = 0xF0F0u;
    uint32_t a32 = 0x0000FF00u;
    uint64_t a64 = 0x123456789ABCDEF0ULL;

    std::cout << "popcount8: " << std::dec << mybit::popcount(a8) << "\n";
    std::cout << "clz8: " << std::dec << mybit::countl_zero(a8) << "\n";
    std::cout << "ctz8: " << std::dec << mybit::countr_zero(a8) << "\n\n";

    std::cout << "popcount16: " << std::dec << mybit::popcount(a16) << "\n";
    std::cout << "clz16: " << std::dec << mybit::countl_zero(a16) << "\n";
    std::cout << "ctz16: " << std::dec << mybit::countr_zero(a16) << "\n\n";

    std::cout << "popcount32: " << std::dec << mybit::popcount(a32) << "\n";
    std::cout << "clz32: " << std::dec << mybit::countl_zero(a32) << "\n";
    std::cout << "ctz32: " << std::dec << mybit::countr_zero(a32) << "\n\n";

    std::cout << "popcount64: " << std::dec << mybit::popcount(a64) << "\n";
    std::cout << "clz64: " << std::dec << mybit::countl_zero(a64) << "\n";
    std::cout << "ctz64: " << std::dec << mybit::countr_zero(a64) << "\n\n";

    std::cout << "rotl8: 0x" << std::hex << (unsigned)mybit::rotl(a8, 4) << "\n";
    std::cout << "reverse8: 0x" << std::hex << (unsigned)mybit::reverse((uint8_t)a8) << "\n\n";

    std::cout << "bit_floor32(15): " << std::dec << mybit::bit_floor((uint32_t)15) << "\n";
    std::cout << "bit_ceil32(15): " << std::dec << mybit::bit_ceil((uint32_t)15) << "\n\n";

    uint8_t buf[8];
    mybit::store_le<uint16_t>(buf, 0xABCDu);
    std::cout << "load_le16: 0x" << std::hex << mybit::load_le<uint16_t>(buf) << "\n";
    mybit::store_be<uint16_t>(buf, 0xABCDu);
    std::cout << "load_be16: 0x" << std::hex << mybit::load_be<uint16_t>(buf) << "\n\n";

    std::cout << "pext32: 0x" << std::hex << mybit::pext((uint32_t)0x12345678u, (uint32_t)0x00FF0000u) << "\n";
    std::cout << "pdep32: 0x" << std::hex << mybit::pdep((uint32_t)0x000000FFu, (uint32_t)0x0F0F0000u) << "\n\n";

    std::cout << "--- mybit verification tests (C++) completed successfully ---\n";
    return 0;
}