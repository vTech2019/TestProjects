#pragma once

#ifndef __FCZLIB_H__
#define __FCZLIB_H__

#include <stdint.h>
#include <include/FcMath.h>
#include <Algorithm/FcSort.h>

const struct {
    uint16_t bits, distance;
} FcZlibOffset[] = {
        0, 1, 0, 2, 0, 3, 0, 4,
        1, 5, 1, 7, 2, 9, 2, 13,
        3, 17, 3, 25, 4, 33, 4, 49,
        5, 65, 5, 97, 6, 129, 6, 193,
        7, 257,
        7, 385,
        8, 513,
        8, 769,
        9, 1025,
        9, 1537,
        10, 2049,
        10, 3073,
        11, 4097,
        11, 6145,
        12, 8193,
        12, 12289,
        13, 16385,
        13, 24577

};
const struct {
    uint16_t bits, length;
} FcZlibLength257[] = {
        0, 3,
        0, 4,
        0, 5,
        0, 6,
        0, 7,
        0, 8,
        0, 9,
        0, 10,
        1, 11,
        1, 13,
        1, 15,
        1, 17,
        2, 19,
        2, 23,
        2, 27,
        2, 31,
        3, 35,
        3, 43,
        3, 51,
        3, 59,
        4, 67,
        4, 83,
        4, 99,
        4, 115,
        5, 131,
        5, 163,
        5, 195,
        5, 227,
        0, 258
};

uint8_t *FcZlibHuffmanDeflate_00(uint8_t *code) {
    union {
        struct {
            uint16_t mLEN;
            uint16_t mNLEN;
            uint8_t data[32768];
        } *_00;
        uint8_t *ptr;
    } mDef;
    mDef.ptr = code;
    uint16_t mLen = SWAP_BYTE_16BIT(mDef._00->mLEN);
    uint16_t mNLen = SWAP_BYTE_16BIT(mDef._00->mNLEN);
    return NULL;
}

uint8_t *FcZlibHuffmanDeflate_10(uint16_t HLIT, uint8_t *mcode, uint8_t *endTable) {
    /*Extra               Extra               Extra
        Code Bits Length(s) Code Bits Lengths   Code Bits Length(s)
        ---- ---- ------     ---- ---- ------ - ---- ---- ------ -
        257   0     3       267   1   15, 16     277   4   67 - 82
        258   0     4       268   1   17, 18     278   4   83 - 98
        259   0     5       269   2   19 - 22     279   4   99 - 114
        260   0     6       270   2   23 - 26     280   4  115 - 130
        261   0     7       271   2   27 - 30     281   5  131 - 162
        262   0     8       272   2   31 - 34     282   5  163 - 194
        263   0     9       273   3   35 - 42     283   5  195 - 226
        264   0    10       274   3   43 - 50     284   5  227 - 257
        265   1  11, 12      275   3   51 - 58     285   0    258
        266   1  13, 14      276   3   59 - 66
        Extra           Extra               Extra
        Code Bits Dist  Code Bits   Dist     Code Bits Distance
        ---- ---- ----  ---- ----  ------    ---- ---- --------
        0   0    1     10   4     33 - 48    20    9   1025 - 1536
        1   0    2     11   4     49 - 64    21    9   1537 - 2048
        2   0    3     12   5     65 - 96    22   10   2049 - 3072
        3   0    4     13   5     97 - 128   23   10   3073 - 4096
        4   1   5, 6    14   6    129 - 192   24   11   4097 - 6144
        5   1   7, 8    15   6    193 - 256   25   11   6145 - 8192
        6   2   9 - 12   16   7    257 - 384   26   12  8193 - 12288
        7   2  13 - 16   17   7    385 - 512   27   12 12289 - 16384
        8   3  17 - 24   18   8    513 - 768   28   13 16385 - 24576
        9   3  25 - 32   19   8   769 - 1024   29   13 24577 - 32768*/
    uint8_t code[] = {
            0x8d, 0x51, 0x0a, 0xc0, 0x20, 0x0c, 0x43, 0xff, 0x3d, 0x45, 0xae, 0x56, 0x67, 0xdd, 0x8a, 0x5d, 0x0b, 0xd5,
            0x21, 0xde, 0x7e, 0x0a, 0xf9, 0x08, 0x21, 0x2f, 0xc9, 0x4a, 0x57, 0xcb, 0x12, 0x05, 0x5d, 0xec, 0xde, 0x82,
            0x18,
            0xc6, 0xc3, 0x28, 0x4c, 0x05, 0x5e, 0x61, 0x72, 0x3f, 0x23, 0x0d, 0x6a, 0x7c, 0xe2, 0xce, 0xc8, 0xe1, 0x8d,
            0x0d, 0x73,
            0x77, 0x3b, 0xc8, 0x0a, 0x94, 0x29, 0x36, 0xe3, 0xa8, 0xba, 0x12, 0xa9, 0x62, 0xf9, 0x17, 0x50, 0xa9, 0x9c,
            0xb6, 0xc3,
            0xe4, 0x60, 0xb8, 0xe9, 0xc2, 0x24, 0x19, 0xe7, 0xa1, 0x7a, 0xec, 0x2d, 0xe9, 0x78, 0xfd, 0x65, 0x1b, 0x07,
            0xa5, 0x90,
            0xce, 0xe9, 0x07
    };
    size_t i0, i1, j, offset;
    uint8_t mHLIT_DIST[286 + 32];
    uint8_t mBitCount[8] = {0};
    uint8_t mAlph[] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
    uint8_t mTreeCode[sizeof(mAlph)] = {0};
    uint8_t cLen[sizeof(mAlph)] = {0};
    if (HLIT >= 30)
        goto gError;
    union {
        struct {
            uint8_t HDIST: 5, HCLEN0: 3,
                    HCLEN1: 1, cLength0: 3, cLength1: 3, cLength2_0: 1,
                    cLength2_1: 2, cLength3: 3, cLength4: 3,
                    cLength5: 3, cLength6: 3, cLength7_0: 2,
                    cLength7_1: 1, cLength8: 3, cLength9: 3, cLength10_0: 1,
                    cLength10_1: 2, cLength11: 3, cLength12: 3,
                    cLength13: 3, cLength14: 3, cLength15_0: 2,
                    cLength15_1: 1, cLength16: 3, cLength17: 3, cLength18_0: 1,
                    cLength18_1: 2, cLength19: 3, cLength20: 3;
            union {
                struct {
                    uint8_t b00: 1, b01: 1, b02: 1, b03: 1, b04: 1, b05: 1, b06: 1, b07: 1;
                } b;
                uint8_t data;
            } mLength[1];
        } *_10;
        uint8_t *ptr;
    } mDef;
    mDef.ptr = code;
    uint8_t mEnd = 51 + 8;
    uint8_t mMaxBits = 0;
    HLIT = 2 + 257;
    uint16_t mHDIST = mDef._10->HDIST + 1;
    uint16_t mHCLEN = mDef._10->HCLEN0 + (mDef._10->HCLEN1 << 3) + 4;
    uint64_t mValue = 0;
    switch (mHCLEN) {
        default:
            goto gError;
        case 19:
            cLen[mAlph[18]] = mDef._10->cLength18_0 + (mDef._10->cLength18_1 << 1);;
        case 18:
            cLen[mAlph[17]] = mDef._10->cLength17;
        case 17:
            cLen[mAlph[16]] = mDef._10->cLength16;
        case 16:
            cLen[mAlph[15]] = mDef._10->cLength15_0 + (mDef._10->cLength15_1 << 2);
        case 15:
            cLen[mAlph[14]] = mDef._10->cLength14;
        case 14:
            cLen[mAlph[13]] = mDef._10->cLength13;
        case 13:
            cLen[mAlph[12]] = mDef._10->cLength12;
        case 12:
            cLen[mAlph[11]] = mDef._10->cLength11;
        case 11:
            cLen[mAlph[10]] = mDef._10->cLength10_0 + (mDef._10->cLength10_1 << 1);
        case 10:
            cLen[mAlph[9]] = mDef._10->cLength9;
        case 9:
            cLen[mAlph[8]] = mDef._10->cLength8;
        case 8:
            cLen[mAlph[7]] = mDef._10->cLength7_0 + (mDef._10->cLength7_1 << 2);
        case 7:
            cLen[mAlph[6]] = mDef._10->cLength6;
        case 6:
            cLen[mAlph[5]] = mDef._10->cLength5;
        case 5:
            cLen[mAlph[4]] = mDef._10->cLength4;
        case 4:
            cLen[mAlph[3]] = mDef._10->cLength3;
            cLen[mAlph[2]] = mDef._10->cLength2_0 + (mDef._10->cLength2_1 << 1);
            cLen[mAlph[1]] = mDef._10->cLength1;
            cLen[mAlph[0]] = mDef._10->cLength0;
    }
    switch (mHCLEN) {
        default:
            goto gError;
        case 4:
            mValue |= mDef._10->cLength4;
        case 5:
            mValue |= mDef._10->cLength5 << 3;
        case 6:
            mValue |= mDef._10->cLength6 << 6;
        case 7:
            mValue |= ((mDef._10->cLength7_1 << 2) | mDef._10->cLength7_0) << 9;
        case 8:
            mValue |= mDef._10->cLength8 << 12;
        case 9:
            mValue |= mDef._10->cLength9 << 15;
        case 10:
            mValue |= ((mDef._10->cLength10_1 << 1) | mDef._10->cLength10_0) << 18;
        case 11:
            mValue |= mDef._10->cLength11 << 21;
        case 12:
            mValue |= mDef._10->cLength12 << 24;
        case 13:
            mValue |= mDef._10->cLength13 << 27;
        case 14:
            mValue |= mDef._10->cLength14 << 30;
        case 15:
            mValue |= (uint64_t) ((mDef._10->cLength15_1 << 2) | mDef._10->cLength15_0) << 33;
        case 16:
            mValue |= (uint64_t) mDef._10->cLength16 << 36;
        case 17:
            mValue |= (uint64_t) mDef._10->cLength17 << 39;
        case 18:
            mValue |= (uint64_t) ((mDef._10->cLength18_1 << 1) | mDef._10->cLength18_0) << 42;
        case 19:
            mValue |= (uint64_t) mDef._10->cLength19 << 45;
            mValue |= (uint64_t) mDef._10->cLength20 << 48;
            mValue |= (uint64_t) mDef._10->mLength[0].data << 51;
            mValue >>= (mHCLEN - 4) * 3;
            mEnd -= (mHCLEN - 4) * 3;
    }
    {
        uint8_t mCODE = 0;
        uint8_t mCode[8] = {0};
        uint8_t mTmp[sizeof(cLen)];
        mBitCount[0] = 0;
        for (j = 1; j < sizeof(mCode); j++) {
            for (i0 = 0; i0 < sizeof(cLen); i0++)
                mBitCount[j] += cLen[i0] == j;
            mCODE = (mCODE + mBitCount[j - 1]) << 1;
            mCode[j] = mCODE;
        }
        for (i0 = 0; i0 < sizeof(mBitCount); i0++)
            if (mBitCount[i0] && mMaxBits < i0)
                mMaxBits = i0;
        for (i0 = 0, j = 0; i0 < sizeof(cLen); i0++) {
            uint8_t len = cLen[i0];
            mAlph[i0] = 0;
            if (len != 0) {
                mTreeCode[j] = mCode[len];
                mAlph[j++] = i0;
                mCode[len]++;
            }
        }
        for (i0 = 0, j = 0; i0 < sizeof(cLen); i0++) {
            if (cLen[i0] != 0)
                cLen[j++] = cLen[i0];
        }
        //FcSort_InsertionData2(uint8_t, mTreeCode, mAlph, cLen, sizeof(mAlph));
        for (i0 = 0; i0 < sizeof(mAlph); i0++) {
            if (mAlph[i0] != 0)
                for (j = i0; j < sizeof(mAlph); j++) {
                    if (mAlph[j] != 0)
                        if (mTreeCode[i0] > mTreeCode[j]) {
                            mTreeCode[j] ^= mTreeCode[i0];
                            mTreeCode[i0] ^= mTreeCode[j];
                            mTreeCode[j] ^= mTreeCode[i0];
                            mAlph[j] ^= mAlph[i0];
                            mAlph[i0] ^= mAlph[j];
                            mAlph[j] ^= mAlph[i0];
                            cLen[j] ^= cLen[i0];
                            cLen[i0] ^= cLen[j];
                            cLen[j] ^= cLen[i0];
                        }
                }
        }
        for (i0 = 0; i0 < sizeof(mAlph); i0++) {
            uint8_t tmp = 0;
            for (j = 0; j < cLen[i0]; j++) {
                tmp |= ((mTreeCode[i0] >> (cLen[i0] - 1 - j)) & 1) << j;
            }
            mTreeCode[i0] = tmp;
        }

        for (i0 = 0; i0 < sizeof(cLen); i0++) {
            printf("%3zd %3d %3d %3d  ", i0, cLen[i0], mAlph[i0], mTreeCode[i0]);
            for (j = 0; j < 8; j++)
                putchar(((mTreeCode[i0] >> (7 - j)) & 1) + 48);
            printf("\n");
        }
    }
    offset = 0;
    for (i0 = i1 = 0; i0 < HLIT + mHDIST;) {
        uint8_t mTmp;
        uint16_t mLengthCode = (mValue >> i1);
        uint8_t mCode = 19;
        for (j = 0; j < sizeof(mTreeCode); j++) {
            if ((mLengthCode & (0xff >> (8u - cLen[j]))) == mTreeCode[j]) {
                mCode = mAlph[j];
                i1 += cLen[j];
                printf("%d ", mAlph[j]);
                break;
            }
        }
        switch (mCode) {
            case 0:
            case 1:;
            case 2:;
            case 3:;
            case 4:;
            case 5:;
            case 6:;
            case 7:;
            case 8:;
            case 9:;
            case 10:;
            case 11:;
            case 12:;
            case 13:;
            case 14:;
            case 15:
                mLengthCode = i0 + 1u;
                mTmp = mAlph[j];
                break;
            case 16: {
                mLengthCode = i0 + 3u + ((mValue >> i1) & 3);
                mTmp = mHLIT_DIST[i0 - 1];
                i1 += 2;
                break;
            }
            case 17: {
                mLengthCode = i0 + 3u + ((mValue >> i1) & 7);
                mTmp = 0;
                i1 += 3;
                break;
            }
            case 18: {
                mLengthCode = i0 + 11u + ((mValue >> i1) & 0x7f);
                mTmp = 0;
                i1 += 7;
                break;
            }
            default:
                goto gError;
        }
        for (; i0 < mLengthCode; i0++)
            mHLIT_DIST[i0] = mTmp;
        if (i1 + 7 >= mEnd) {
            mValue >>= i1;
            for (j = 0; j < 7; j++)
                mValue |= (uint64_t) mDef._10->mLength[offset + j + 1].data << (j * 8 + (mEnd - i1));
            offset += 7 - (mEnd - i1) / 8;
            mEnd = 7 * 8 + (mEnd - i1);
            i1 = 0;
        }
    }
    putchar('\n');
    for (j = 0; j < HLIT; j++) {
        printf("%d ", mHLIT_DIST[j]);
    }
    putchar('\n');
    for (; j < HLIT + mHDIST; j++) {
        printf(" %d ", mHLIT_DIST[j]);
    }
    putchar('\n');
    //printf("%d %d\n", mDIST, mCLEN);
    //for (j = 0; j < 21; j++)
    //for (i0 = 0; i0 < 8; i0++)
    //	printf("%d", (code[j] >> i0) & 1);
    //printf("\n");
    //for (i0 = 0; i0 < 9; i0++)
    //	printf(" ");
    //for (i0 = 0; i0 < mCLEN; i0++)
    //	printf("%d%d%d", cLen[i0] & 1, (cLen[i0] & 2) >> 1, (cLen[i0] & 4) >> 2);
    gError:
    return NULL;
}

uint8_t *FcZlibHuffmanDeflateMalloc(uint8_t *code, size_t length) {
    union {
        struct {
            union {
                struct {
                    uint8_t mCM: 4;
                    uint8_t mCINFO: 4;
                } mCMF;
                uint8_t mValueCMF;
            };
            union {
                struct {
                    uint8_t mFCHECK: 5;
                    uint8_t mFDICT: 1;
                    uint8_t mFLEVEL: 2;
                } mFLG;
                uint8_t mValueFLG;
            };
            union {
                struct {
                    uint8_t mDICTID[4];
                    uint8_t mBFINAL: 1;
                    uint8_t mBTYPE: 2;
                    uint8_t data[32768];
                } _f00;
                struct {
                    uint8_t mBFINAL: 1;
                    uint8_t mBTYPE: 2;
                    uint8_t data[32768];
                } _00;
                struct {
                    uint8_t mBFINAL: 1;
                    uint8_t mBTYPE: 2;
                    uint8_t mHLIT: 5;
                    uint8_t data[32768];
                } _10;
            };
        } *data;
        uint8_t *ptr;
    } mHuffmanDeflateBlock;
    mHuffmanDeflateBlock.ptr = code;

    if (mHuffmanDeflateBlock.data->mCMF.mCM != 8)
        goto gError;
    if ((SWAP_BYTE_16BIT(mHuffmanDeflateBlock.data->mValueCMF * 256 + mHuffmanDeflateBlock.data->mValueFLG) -
         mHuffmanDeflateBlock.data->mFLG.mFCHECK) % 31)
        goto gError;
    uint16_t mWindowSize = mHuffmanDeflateBlock.data->mCMF.mCINFO;
    if (mHuffmanDeflateBlock.data->mFLG.mFDICT) {
        switch (mHuffmanDeflateBlock.data->_f00.mBTYPE) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                goto gError;
        }
    } else {
        switch (mHuffmanDeflateBlock.data->_00.mBTYPE) {
            case 0: {
                FcZlibHuffmanDeflate_00(mHuffmanDeflateBlock.data->_00.data);
                break;
            }
            case 1:
                break;
            case 2:
                FcZlibHuffmanDeflate_10(mHuffmanDeflateBlock.data->_10.mHLIT, mHuffmanDeflateBlock.data->_10.data,
                                        code + length);
                break;
            case 3:
                goto gError;
        }
    }

    gError:
    return 0;
}

#endif
