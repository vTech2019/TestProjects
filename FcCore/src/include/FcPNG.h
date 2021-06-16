#ifndef _FCPNG_H
#define _FCPNG_H

#ifndef _FCERROR_H
#include <FcError.h>
#endif

#ifndef _FCZLIB_H

#include <include/FcZlib.h>

#endif
#ifndef _FCIMAGE_H

#include <FcImage/FcImage.h>

#endif

#ifndef _FCMATH_H
#include <FcMath.h>
#endif

#ifdef FCPNGSTATIC
#define FCDEF static inline
#else
#define FCDEF extern inline
#endif

#ifdef UNICODE
#define fopen _wfopen
#define fopen_s _wfopen_s
#define tchar wchar_t
#ifndef TEXT
#define __T(x) L ## x
#define TEXT(x) __T(x)
#endif
#else
#define fopen fopen
#define fopen_s fopen_s
#define tchar char
#ifndef TEXT
#define TEXT(x) (x)
#endif
#endif

#ifndef _INC_STDIO

#include <stdio.h>

#define _INC_STDIO
#endif

FCDEF FcError_t FcPNG_read(FcImage_t **image, const tchar *file);

typedef struct _FcFile_t {
    union FcFileMemory_t {
        uint8_t *ptr8;
        uint16_t *ptr16;
        uint32_t *ptr32;
        uint64_t *ptr64;
    } memory;
    size_t size;
} FcFile_t;

FCDEF FcError_t FcFile_read(
        _Out_ FcFile_t *file,
        _In_z_ const tchar *name) {
    FILE *m_stream;
    long size_file;
    FcError_t mError = FC_NO_ERROR;
    file->memory.ptr8 = NULL;
    file->size = 0;

#ifdef _MSC_VER
    if (fopen_s(&m_stream, name, "rb") != 0) {
        mError = errno;
        goto gError;
    }
#else
    if ((m_stream = fopen(name, "rb")) == NULL) {
        mError = errno;
        goto gError;
    }
#endif

    if (fseek(m_stream, 0, SEEK_END) != 0) {
        mError = errno;
        goto gError;
    }
    if ((size_file = ftell(m_stream)) == -1L) {
        mError = errno;
        goto gError;
    }
    rewind(m_stream);
    if ((file->memory.ptr8 = (uint8_t *) malloc((size_t) size_file)) == NULL) {
        mError = errno;
        goto gError;
    }
    file->size = (size_t) size_file;
    if (!fread(file->memory.ptr8, (size_t) size_file, 1, m_stream)) {
        mError = errno;
        goto gError;
    }
    if (fclose(m_stream) != 0) {
        mError = errno;
        goto gError;
    }
    gError:
    return mError;
}

FCDEF FcError_t FcFile_free(_Out_ FcFile_t *file) {
    free(file->memory.ptr8);
    file->memory.ptr8 = NULL;
    file->size = 0;
    return FC_NO_ERROR;
}

FCDEF FcError_t FcPNG_read(FcImage_t **image, const tchar *file) {
    size_t i, j;
    FcFile_t mFile = {0};
    union {
        struct {
            uint8_t length[4];
            uint8_t type[4];
            uint8_t data[0];
        } *chunks;
        uint8_t *ptr8;
    } mChunks;
    FcError_t mError = FC_NO_ERROR;
    *image = NULL;
    if (mError = FcFile_read(&mFile, file))
        goto gError;

    if (!FcGL_Vec2ui_equal(FcGL_Vec2uca(mFile.memory.ptr8), FcGL_Vec2uc(137, 80, 78, 71, 13, 10, 26, 10))) {
        mError = FC_PNG_NOTPNG;
        goto gError;
    }
    mChunks.ptr8 = mFile.memory.ptr8 + 8;

    {
        uint32_t mCRCTable[256];
        uint32_t i, j;
        for (i = 0; i < 256; i++) {
            uint32_t c = i;
            for (j = 0; j < 8; j++)
                c = c & 1 ? 0xedb88320L ^ (c >> 1) : c >> 1;
            mCRCTable[i] = c;
        }
        if (SWAP_READ_32BIT(mChunks.chunks->type) != 'IHDR') {
            mError = FC_PNG_NOTPNG;
            goto gError;
        }

        while (SWAP_READ_32BIT(mChunks.chunks->type) != 'IEND') {
            uint32_t c = 0xffffffffL;
            uint32_t mLength = SWAP_READ_32BIT(mChunks.chunks->length);
            uint32_t mCRC = SWAP_READ_32BIT(mChunks.chunks->data + mLength);
            uint8_t *mData = (uint8_t *) &mChunks.chunks->type;
            for (i = 0; i + 7 < mLength + 4; i += 8) {
                uint32_t mLocal[8];
                for (j = 0; j < 8; j++)
                    mLocal[j] = mData[i + j];
                for (j = 0; j < 8; j++)
                    c = mCRCTable[(c ^ mLocal[j]) & 0xff] ^ (c >> 8);
            }
            for (; i < mLength + 4; i++)
                c = mCRCTable[(c ^ mData[i]) & 0xff] ^ (c >> 8);

            c ^= 0xffffffffL;
            if (c != mCRC) {
                mError = FC_PNG_CRCERROR;
                goto gError;
            }
            mChunks.ptr8 = mChunks.chunks->data + mLength + 4;
        }
        mChunks.ptr8 = mFile.memory.ptr8 + 8;
    }
    union {
        struct {
            uint32_t width, height;
            uint8_t depth, typeColor, compression, filter, interplace;
        } *data;
        uint8_t *ptr8;
    } mIHDR;
    union {
        struct {
            uint8_t RGB[1][3];
        } *data;
        uint8_t *ptr8;
    } mPLTE;
    union {
        struct {
            uint8_t compression[1];
        } *data;
        uint8_t *ptr8;
    } mIDAT;
    union {
        union {
            uint16_t gley0[1];
            uint16_t rbg2[1];
            uint8_t alpha3[2];
        } *data;
        uint8_t *ptr8;
    } mTRNS;
    union {
        struct {
            uint32_t whiteX, whiteY, redX, redY, greenX, greenY, blueX, blueY;
        } *data;
        uint8_t *ptr8;
    } mCHRM;
    union {
        struct {
            uint8_t nameNullCompressionProfile[2]; // 1-79, 1, 1, n
        } *data;
        uint8_t *ptr8;
    } mICCP;
    union {
        union {
            uint8_t gley0[1], redGreenBlue23[3], greyAlpha4[2], redGreenBlueAlpha6[4];
        } *data;
        uint8_t *ptr8;
    } mSBIT;
    union {
        union {
            uint16_t gley04[1], redGreenBlue26[3];
            uint8_t paletteIndex3;
        } *data;
        uint8_t *ptr8;
    } mBKGD;
    union {
        struct {
            uint32_t pixelPerUnitX;
            uint32_t pixelPerUnitY;
            uint8_t unit;
        } *data;
        uint8_t *ptr8;
    } mPHYS;
    uint8_t *mTEXT = NULL;
    uint8_t *mZTXT = NULL;
    uint32_t mGamma = 0;
    uint32_t mIDAT_length = 0;
    uint8_t mIntent = 0;
    while (SWAP_READ_32BIT(mChunks.chunks->type) != 'IEND') {
        switch (SWAP_READ_32BIT(mChunks.chunks->type)) {
            case 'IHDR': {
                mIHDR.ptr8 = mChunks.chunks->data;
                FcImageType_t mType = 0;
                switch (mIHDR.data->typeColor) {
                    case 0:
                        mType = FCIMAGE_R;
                        break;
                    case 2:
                        mType = FCIMAGE_RGB;
                        break;
                    case 3:
                        mType = FCIMAGE_R;
                        break;
                    case 4:
                        mType = FCIMAGE_RG;
                        break;
                    case 6:
                        mType = FCIMAGE_RGBA;
                        break;
                }
                if (mIHDR.data->compression != 0 || mIHDR.data->filter != 0) {
                    mError = FC_PNG_NOTPNG;
                    goto gError;
                }
                if (!(*image = FcImage(FcSwapbyte32(mIHDR.data->width), FcSwapbyte32(mIHDR.data->height), mType))) {
                    mError = errno;
                    goto gError;
                }
                break;
            }
            case 'PLTE':
                mPLTE.ptr8 = mChunks.chunks->data;
                break;
            case 'IDAT':
                mIDAT.ptr8 = mChunks.chunks->data;
                mIDAT_length = SWAP_READ_32BIT(mChunks.chunks->length);
                break;
            case 'IEND':
                break;

            case 'tRNS':
                mTRNS.ptr8 = mChunks.chunks->data;
                break;
            case 'cHRM':
                mCHRM.ptr8 = mChunks.chunks->data;
                break;
            case 'iCCP':
                mICCP.ptr8 = mChunks.chunks->data;
                break;
            case 'sBIT':
                mSBIT.ptr8 = mChunks.chunks->data;
                break;
            case 'bKGD':
                mBKGD.ptr8 = mChunks.chunks->data;
                break;
            case 'pHYs':
                mPHYS.ptr8 = mChunks.chunks->data;
                break;
            case 'sPLT':
                break;
            case 'tIME':
                break;
            case 'iTXt':
                break;
            case 'tEXt':
                mTEXT = mChunks.chunks->data;
                break;
            case 'zTXt':
                mZTXT = mChunks.chunks->data;
                break;
            case 'sRGB':
                mIntent = *mChunks.chunks->data;
                break;
            case 'gAMA':
                mGamma = *(uint32_t *) mChunks.chunks->data;
                break;
        }
        mChunks.ptr8 = mChunks.chunks->data + (SWAP_READ_32BIT(mChunks.chunks->length)) + 4;
    }
    uint8_t *data = FcZlibHuffmanDeflateMalloc(mIDAT.data->compression, mIDAT_length);
    for (i = 0; i < mIDAT_length; i++)
        printf("%d\n", data[i]);
    gError:
    return mError;
}

#endif