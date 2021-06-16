
#ifndef _FCSORT_H
#define _FCSORT_H
#ifndef size_t

#include <stdint.h>

#endif
#ifndef uint16_t

#include <stddef.h>

#endif
#ifndef max
#define max(a, b) ((a) < (b) ? b : a);
#define min(a, b) ((a) > (b) ? b : a);
#endif
#define swap(t, a, b) do { t ab = a; a = b; b = ab; }while(0);

#define  FcSort_InsertionData2(type, src, data0, data1, length){\
    size_t InsertionI, InsertionJ;                                                \
    type mKey, mData0, mData1;                                  \
    for (InsertionJ = 0, InsertionI = 1; InsertionI < length; InsertionJ = InsertionI, InsertionI++){                 \
        mKey = src[InsertionI]; mData0 = data0[InsertionI]; mData1 = data1[InsertionI]; \
        for (; InsertionJ < length && mKey < src[InsertionJ]; InsertionJ--){            \
            src[InsertionJ + 1] = src[InsertionJ];                          \
            data0[InsertionJ + 1] = data0[InsertionJ];                            \
            data1[InsertionJ + 1] = data1[InsertionJ];                            \
            }                                                   \
        src[InsertionJ + 1] = mKey;                                   \
        data0[InsertionJ + 1] = mData0;                                   \
        data1[InsertionJ + 1] = mData1;                                   \
    }                                                           \
}
#define  FcSort_Insertion(type, src, length){\
    size_t i, j;\
    type mKey;\
    for (j = 0, i = 1; i < length; j = i, i++){\
        mKey = srcDst[i];\
        for (; j < length && mKey < srcDst[j]; j--)\
            srcDst[j + 1] = srcDst[j];\
        srcDst[j + 1] = mKey;\
    }\
}

static inline void FcSort_InsertionU16D16(uint16_t *sortArr, uint16_t *sortData, size_t length);

static inline void FcSort_RadixU16(uint16_t *src, uint16_t *dst, size_t length);

static inline void FcSort_InsertionU16(uint16_t *srcDst, size_t length);

static inline void FcSort_InsertionU16D16(uint16_t *sortArr, uint16_t *sortData, size_t length) {
    size_t i, j;
    uint16_t mKey, mData;
    for (j = 0, i = 1; i < length; j = i, i++) {
        mKey = sortArr[i];
        mData = sortData[i];
        for (; j < length && mKey < sortArr[j]; j--) {
            sortArr[j + 1] = sortArr[j];
            sortData[j + 1] = sortData[j];
        }
        sortArr[j + 1] = mKey;
        sortData[j + 1] = mData;
    }
}

static inline void FcSort_InsertionU16(uint16_t *srcDst, size_t length) {
    size_t i, j;
    uint16_t mKey;
    for (j = 0, i = 1; i < length; j = i, i++) {
        mKey = srcDst[i];
        for (; j < length && mKey < srcDst[j]; j--)
            srcDst[j + 1] = srcDst[j];
        srcDst[j + 1] = mKey;
    }
}

/*static inline void FcSort_MergeU16(uint16_t* src, size_t length){
        output__m128i vTmp;
        vTmp = _mm_min_epu32(vA, vB);
        vMax = _mm_max_epu32(vA, vB);
        vTmp = _mm_xor_si128(_mm_slli_si128(vTmp, 8), _mm_srli_si128(vTmp, 8));

        vTmp = _mm_alignr_epi8(vTmp, vTmp, 4);
        vMin = _mm_min_epu32(vTmp, vMax);
        vMax = _mm_max_epu32(vTmp, vMax);
        vTmp = _mm_alignr_epi8(vMin, vMin, 4);
        vMin = _mm_min_epu32(vTmp, vMax);
        vMax = _mm_max_epu32(vTmp, vMax);
        vTmp = _mm_alignr_epi8(vMin, vMin, 4);
        vMin = _mm_min_epu32(vTmp, vMax);
        vMax = _mm_max_epu32(vTmp, vMax);
        vMin = _mm_alignr_epi8(vMin, vMin, 4);}
}*/

static inline void FcSort_SortingNetworkU16(uint16_t *srcDst, size_t length) {
    size_t i, j, vLength, sLength;
    uint16_t mKey;
    uint16_t mV[8];
    vLength = length / 8;
    sLength = length % 8;
    for (i = 0; i < vLength; i++) {
        for (j = 0; j < 8; j++) {
            mV[j] = srcDst[i * 8 + j];
        }
        mV[0] = min(mV[0], mV[1]);
        mV[1] = max(mV[0], mV[1]);
        mV[2] = min(mV[2], mV[3]);
        mV[3] = max(mV[2], mV[3]);
    }
    for (j = 0, i = 1; i < length; j = i, i++) {
        mKey = srcDst[i];
        for (; j < length && mKey < srcDst[j]; j--)
            srcDst[j + 1] = srcDst[j];
        srcDst[j + 1] = mKey;
    }
}

static inline void FcSort_RadixU16_4096(uint16_t *src, uint16_t *dst, size_t length) {
    size_t mCount0[256] = {0};
    size_t mCount1[256] = {0};
    size_t i, s0, s1, c0, c1;
    for (i = 0; i + 3 < length; i += 4) {
        s0 = src[i + 0];
        s1 = src[i + 1];
        c0 = src[i + 2];
        c1 = src[i + 3];
        mCount0[s0 & 0xff]++;
        mCount0[s1 & 0xff]++;
        mCount0[c0 & 0xff]++;
        mCount0[c1 & 0xff]++;
        mCount1[s0 >> 8]++;
        mCount1[s1 >> 8]++;
        mCount1[c0 >> 8]++;
        mCount1[c1 >> 8]++;
    }
    switch (length - i) {
        case 3:
            mCount0[src[i + 2] & 0xff]++;
            mCount1[src[i + 2] >> 8]++;
        case 2:
            mCount0[src[i + 1] & 0xff]++;
            mCount1[src[i + 1] >> 8]++;
        case 1:
            mCount0[src[i + 0] & 0xff]++;
            mCount1[src[i + 0] >> 8]++;
    }
    for (i = 0, s0 = 0, s1 = 0; i < 256; i++) {
        c0 = mCount0[i];
        c1 = mCount1[i];
        mCount0[i] = s0;
        mCount1[i] = s1;
        s0 += c0;
        s1 += c1;
    }
    for (i = 0; i + 3 < length; i += 4) {
        s0 = src[i + 0];
        s1 = src[i + 1];
        c0 = src[i + 2];
        c1 = src[i + 3];
        dst[mCount0[s0 & 0xff]++] = s0;
        dst[mCount0[s1 & 0xff]++] = s1;
        dst[mCount0[c0 & 0xff]++] = c0;
        dst[mCount0[c1 & 0xff]++] = c1;
    }
    switch (length - i) {
        case 3:
            dst[mCount0[src[i + 2] & 0xff]++] = src[i + 2];
        case 2:
            dst[mCount0[src[i + 1] & 0xff]++] = src[i + 1];
        case 1:
            dst[mCount0[src[i + 0] & 0xff]++] = src[i + 0];
    }
    for (i = 0; i + 3 < length; i += 4) {
        s0 = dst[i + 0];
        s1 = dst[i + 1];
        c0 = dst[i + 2];
        c1 = dst[i + 3];
        src[mCount1[s0 >> 8]++] = s0;
        src[mCount1[s1 >> 8]++] = s1;
        src[mCount1[c0 >> 8]++] = c0;
        src[mCount1[c1 >> 8]++] = c1;
    }
    switch (length - i) {
        case 3:
            src[mCount1[dst[i] >> 8]++] = dst[i];
            i++;
        case 2:
            src[mCount1[dst[i] >> 8]++] = dst[i];
            i++;
        case 1:
            src[mCount1[dst[i] >> 8]++] = dst[i];
    }
}

static inline void FcSort_RadixU16(uint16_t *src, uint16_t *dst, size_t length) {
    const uint16_t mask[4] = {0x000f, 0x00f0, 0x0f00, 0xf000}, shift[4] = {0, 4, 8, 12};
    size_t mCount[16][4] = {0};
    size_t i, j, mOffset, d0[4], d1[4] = {0};
    for (i = 0; i < length; i++) {
        mCount[(src[i] & 0x000f) >> 0][0]++;
        mCount[(src[i] & 0x00f0) >> 4][1]++;
        mCount[(src[i] & 0x0f00) >> 8][2]++;
        mCount[(src[i] & 0xf000) >> 12][3]++;
    }
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 4; j++)
            d0[j] = mCount[i][j];
        for (j = 0; j < 4; j++)
            mCount[i][j] = d1[j];
        for (j = 0; j < 4; j++)
            d1[j] += d0[j];
    }
    for (i = 0; i < length; i++) {
        mOffset = src[i];
        dst[mCount[(mOffset & 0x000f) >> 0][0]++] = mOffset;
    }
    for (i = 0; i < length; i++) {
        mOffset = dst[i];
        src[mCount[(mOffset & 0x00f0) >> 4][1]++] = mOffset;
    }
    for (i = 0; i < length; i++) {
        mOffset = src[i];
        dst[mCount[(mOffset & 0x0f00) >> 8][2]++] = mOffset;
    }
    for (i = 0; i < length; i++) {
        mOffset = dst[i];
        src[mCount[(mOffset & 0xf000) >> 12][3]++] = mOffset;
    }
}

static inline void FcSort_ShellU16(uint16_t *array, const size_t size) {
    size_t s, i, j;
    uint16_t v[2];
    for (s = size / 2; s > 0; s /= 2) {
        for (i = 0; i < size; i++) {
            for (j = i + s; j < size; j += s) {
                v[0] = min(array[j], array[i]);
                v[1] = max(array[j], array[i]);
                array[i] = v[0];
                array[j] = v[1];
            }
        }
    }
}

static inline void FcSort_BubbleU16(uint16_t *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i; j < size; j++) {
            if (array[i] > array[j]) {
                uint16_t temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
    }
}

static inline void FcSort_GnomeU16(uint16_t *array, size_t length) {
    for (size_t i = 0; i < length - 1; i++) {
        if (array[i] > array[i + 1]) {
            uint16_t tmp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = tmp;
            i -= i == 0 ? 0 : 2;
        }
    }
}

static inline void FcSort_BitonicU16(uint16_t *array, size_t length) {
    size_t i0, i1, j0, j1, id;
    for (i0 = 2; i0 <= length; i0 *= 2) {
        for (j0 = i0 / 2; j0 > 0; j0 /= 2) {
            for (i1 = 0; i1 < length; i1++) {
                id = i1 ^ j0;
                if (id > i1) {
                    if ((((i1 & i0) == 0) & (array[i1] > array[id])) |
                        (((i1 & i0) != 0) & (array[i1] < array[id]))) {
                        uint16_t tmp = array[i1];
                        array[i1] = array[id];
                        array[id] = tmp;
                    }
                }
            }
        }
    }
}

static inline void FcSort_Heap16(uint16_t arr[], size_t length) {
    uint16_t mRoot;
    size_t n = length, parent = length / 2, offset, child;
    while (n > 1) {
        if (parent > 0) {
            mRoot = arr[--parent];
        } else {
            n--;
            mRoot = arr[n];
            arr[n] = arr[0];
        }
        offset = parent;
        child = offset * 2 + 1;
        while (child < n) {
            if (child + 1 < n) {
                child += arr[child + 1] > arr[child];
            }
            if (arr[child] > mRoot) {
                arr[offset] = arr[child];
                offset = child;
                child = child * 2 + 1;
            } else {
                break;
            }
        }
        arr[offset] = mRoot;
    }
}

static inline void FcSort_QuicksortU16(uint16_t *element_list, ptrdiff_t low, ptrdiff_t high) {
    ptrdiff_t pivot, value1, value2;
    uint16_t temp;
    if (low < high) {
        pivot = low;
        value1 = low;
        value2 = high;
        while (value1 < value2) {
            while (element_list[value1] <= element_list[pivot] && value1 <= high) {
                value1++;
            }
            while (element_list[value2] > element_list[pivot] && value2 >= low) {
                value2--;
            }
            if (value1 < value2) {
                temp = element_list[value1];
                element_list[value1] = element_list[value2];
                element_list[value2] = temp;
            }
        }
        temp = element_list[value2];
        element_list[value2] = element_list[pivot];
        element_list[pivot] = temp;
        FcSort_QuicksortU16(element_list, low, value2 - 1);
        FcSort_QuicksortU16(element_list, value2 + 1, high);
    }
}

#endif //_FCSORT_H
