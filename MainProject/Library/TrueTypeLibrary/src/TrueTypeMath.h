#include <sal.h>
#include <stdint.h>

#define ALIGN(size) (((size - 1) | 15) + 1)

#define ALIGN64(size) (((size - 1) | 63) + 1)

#define SWAP_BYTE_16(value)                                                    \
  ((((value) >> (uint16_t)8) & (uint16_t)0xff) |                               \
   (((value) & (uint16_t)0xff) << (uint16_t)8))
#define SWAP_BYTE_32(value)                                                    \
  (((((value)&0xff000000) >> 24) | (((value)&0x00ff0000) >> 8) |               \
    ((value)&0x0000ff00) << 8) |                                               \
   (((value)&0x000000ff) << 24))
#define SWAP_BYTE_64(value)                                                    \
  (((value & 0x00000000000000ffull) << 56) |                                   \
   ((value & 0x000000000000ff00ull) << 40) |                                   \
   ((value & 0x0000000000ff0000ull) << 24) |                                   \
   ((value & 0x00000000ff000000ull) << 8) |                                    \
   ((value & 0x000000ff00000000ull) >> 8) |                                    \
   ((value & 0x0000ff0000000000ull) >> 24) |                                   \
   ((value & 0x00ff000000000000ull) >> 40) |                                   \
   ((value & 0xff00000000000000ull) >> 56))

#define swap32_byte_16(value)                                                  \
  ((((value)&0x0000ff00) >> 8) | (((value)&0x000000ff) << 8) |                 \
   ((((value)&0xff000000) >> 8) | (((value)&0x00ff0000) << 8)))

#define swap64_byte_16(value)                                                  \
  ((((value)&0x000000000000ff00ull) >> 8) |                                    \
   (((value)&0x00000000000000ffull) << 8) |                                    \
   ((((value)&0x00000000ff000000ull) >> 8) |                                   \
    (((value)&0x0000000000ff0000ull) << 8)) |                                  \
   ((((value)&0x0000ff0000000000ull) >> 8) |                                   \
    (((value)&0x000000ff00000000ull) << 8)) |                                  \
   ((((value)&0xff00000000000000ull) >> 8) |                                   \
    (((value)&0x00ff000000000000ull) << 8)))

#define all64_flag8(ptr, byte_offset, flag)                                    \
  (*(uint64_t *)(ptr + byte_offset) &                                          \
   ((uint64_t)flag | ((uint64_t)flag << 8) | ((uint64_t)flag << 16) |          \
    ((uint64_t)flag << 24) | ((uint64_t)flag << 32) | ((uint64_t)flag << 40) | \
    ((uint64_t)flag << 48) | ((uint64_t)flag << 56)))

#ifndef __TRUETYPEMATH_H__
#define __TRUETYPEMATH_H__

static inline uint8_t* align64(uint8_t* ptr) {
    return (uint8_t*)((intptr_t)(ptr + 63) & ~63);
}
static inline uint8_t* align16(uint8_t* ptr) {
    return (uint8_t*)((intptr_t)(ptr + 15) & ~15);
}
static inline uint64_t swap_byte_64(_In_ uint64_t value) {
    return (((value & 0x00000000000000ffull) << 56) |
        ((value & 0x000000000000ff00ull) << 40) |
        ((value & 0x0000000000ff0000ull) << 24) |
        ((value & 0x00000000ff000000ull) << 8) |
        ((value & 0x000000ff00000000ull) >> 8) |
        ((value & 0x0000ff0000000000ull) >> 24) |
        ((value & 0x00ff000000000000ull) >> 40) |
        ((value & 0xff00000000000000ull) >> 56));
}
static inline uint32_t swap_byte_32(_In_ uint32_t value) {
    return (((((value) & 0xff000000) >> 24) | (((value) & 0x00ff0000) >> 8) |
        ((value) & 0x0000ff00) << 8) |
        (((value) & 0x000000ff) << 24));
}
static inline uint16_t swap_byte_16(_In_ uint16_t value) {
    return ((((value) >> 8i16) & 0xffi16) |
        (((value) & 0xffi16) << 8i16));
}
static inline uint32_t check_checksum_swapByte(_In_reads_bytes_(length)uint32_t* table, _In_ uint32_t length) {
    uint32_t i = 0, i_end = (((length + 3) & ~3u)) / 4;
    uint32_t m_sum = 0;
    for (; i < i_end; i++)
        m_sum += swap_byte_32(table[i]);
    return m_sum;
}

#endif
