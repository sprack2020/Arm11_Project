uint32_t swapEndianness(uint32_t n) {
    return (n & 0xFF << 0) << 24 |
           (n & 0xFF << 8) << 8  |
           (n & 0xFF << 16) >> 8 |
           (n & 0xFF << 24) >> 24;
}

