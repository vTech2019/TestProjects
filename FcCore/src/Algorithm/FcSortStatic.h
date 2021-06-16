//
// Created by human on 20/05/2021.
//

#ifndef _FCSORTSTATIC_H
#define _FCSORTSTATIC_H

static inline void BM2(short src[16]) {
    _Alignas(16) short dst[16];
    short i;
    for (i = 0; i < 16; i += 2) {
        dst[i + 0] = min(src[i + 0], src[i + 1]);
        dst[i + 1] = max(src[i + 0], src[i + 1]);
    }
    for (i = 0; i < 16; i++)
        src[i] = dst[i];
}

static inline void BM4(short src[16]) {
    _Alignas(16) short dst[16];
    short i;
    for (i = 0; i < 16; i += 4) {
        dst[i + 0] = min(src[i + 0], src[i + 2]);
        dst[i + 2] = max(src[i + 0], src[i + 2]);
        dst[i + 1] = min(src[i + 1], src[i + 3]);
        dst[i + 3] = max(src[i + 1], src[i + 3]);
    }
    BM2(dst);
    for (i = 0; i < 16; i++)
        src[i] = dst[i];
}

static inline void BM8(short src[16]) {
    _Alignas(16) short dst[16];
    short i, j;
    for (i = 0; i < 16; i += 8) {
        for (j = 0; j < 4; j++) {
            dst[i + 0 + j] = min(src[i + j], src[i + 4 + j]);
            dst[i + 4 + j] = max(src[i + j], src[i + 4 + j]);
        }
    }
    BM4(dst);
    BM2(dst);
    for (i = 0; i < 16; i++)
        src[i] = dst[i];
}

void sort(short src[16]) {
    BM2(src);
    BM4(src);
    BM8(src);
}

#endif //_FCSORTSTATIC_H
