
#ifndef _FCSSE2_H
#define _FCSSE2_H

#include <emmintrin.h>
#include <immintrin.h>

static inline void FcSSE2_Sort8x8i(__m128i *v0, __m128i *v1) {

    size_t j = 0;
    __m128i mTmp;
    __m128i mMin, mMax;

    mMin = *v0;
    mMax = *v1;
    printf("%d %d %d %d %d %d %d %d   ", ((uint16_t * ) & mMin)[0], ((uint16_t * ) & mMin)[1],
           ((uint16_t * ) & mMin)[2],
           ((uint16_t * ) & mMin)[3], ((uint16_t * ) & mMin)[4], ((uint16_t * ) & mMin)[5], ((uint16_t * ) & mMin)[6],
           ((uint16_t * ) & mMin)[7]);
    printf("%d %d %d %d %d %d %d %d\n", ((uint16_t * ) & mMax)[0], ((uint16_t * ) & mMax)[1], ((uint16_t * ) & mMax)[2],
           ((uint16_t * ) & mMax)[3], ((uint16_t * ) & mMax)[4], ((uint16_t * ) & mMax)[5], ((uint16_t * ) & mMax)[6],
           ((uint16_t * ) & mMax)[7]);
    for (j = 0; j < 8; j++) {
        mTmp = _mm_min_epi16(mMin, mMax);
        mMax = _mm_max_epi16(mMin, mMax);
        //mMin = _mm_or_si128(_mm_slli_si128(mMin, 2), _mm_srli_si128(mMin, 14));
        mMin = _mm_alignr_epi8(mTmp, mMax, 2);
        mMax = _mm_alignr_epi8(mMax, mTmp, 14);
        printf("%d %d %d %d %d %d %d %d   ", ((uint16_t * ) & mMin)[0], ((uint16_t * ) & mMin)[1],
               ((uint16_t * ) & mMin)[2],
               ((uint16_t * ) & mMin)[3], ((uint16_t * ) & mMin)[4], ((uint16_t * ) & mMin)[5],
               ((uint16_t * ) & mMin)[6],
               ((uint16_t * ) & mMin)[7]);
        printf("%d %d %d %d %d %d %d %d\n", ((uint16_t * ) & mMax)[0], ((uint16_t * ) & mMax)[1],
               ((uint16_t * ) & mMax)[2],
               ((uint16_t * ) & mMax)[3], ((uint16_t * ) & mMax)[4], ((uint16_t * ) & mMax)[5],
               ((uint16_t * ) & mMax)[6],
               ((uint16_t * ) & mMax)[7]);
    }
    printf("%d %d %d %d %d %d %d %d\n", ((uint16_t * ) & mTmp)[0], ((uint16_t * ) & mTmp)[1], ((uint16_t * ) & mTmp)[2],
           ((uint16_t * ) & mTmp)[3], ((uint16_t * ) & mTmp)[4], ((uint16_t * ) & mTmp)[5], ((uint16_t * ) & mTmp)[6],
           ((uint16_t * ) & mTmp)[7]);

    *v0 = mMin;
    *v1 = mMax;
}

static inline void FcSSE2_Sort8i(__m128i *v0) {

    size_t j = 0;
    __m128i m0, m1, m2;
    m0 = *v0;
    m1 = _mm_or_si128(_mm_slli_si128(m0, 2), _mm_srli_si128(m0, 14));
    for (j = 0; j < 4; j++) {
        m2 = _mm_min_epi16(m0, m1);
        m1 = _mm_max_epi16(m0, m1);
        m0 = _mm_or_si128(_mm_slli_si128(m2, 2), _mm_srli_si128(m2, 14));
        m1 = _mm_or_si128(_mm_srli_si128(m1, 2), _mm_slli_si128(m1, 14));
        m2 = _mm_min_epi16(m0, m1);
        m1 = _mm_max_epi16(m0, m1);
    }
    printf("%d %d %d %d %d %d %d %d\n", ((uint16_t * ) & m0)[0], ((uint16_t * ) & m0)[1], ((uint16_t * ) & m0)[2],
           ((uint16_t * ) & m0)[3], ((uint16_t * ) & m0)[4], ((uint16_t * ) & m0)[5], ((uint16_t * ) & m0)[6],
           ((uint16_t * ) & m0)[7]);
    printf("%d %d %d %d %d %d %d %d\n", ((uint16_t * ) & m1)[0], ((uint16_t * ) & m1)[1], ((uint16_t * ) & m1)[2],
           ((uint16_t * ) & m1)[3], ((uint16_t * ) & m1)[4], ((uint16_t * ) & m1)[5], ((uint16_t * ) & m1)[6],
           ((uint16_t * ) & m1)[7]);

    *v0 = m0;
}

#endif //_FCSSE2_H
