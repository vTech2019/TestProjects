//
// Created by human on 24/05/2021.
//

#include "Algorithm/FcSort.h"
#include <stdlib.h>
#include <stdio.h>
static inline uint64_t rdtsc(void)
{
    uint64_t msr;
    asm volatile ( "rdtsc\n\t" "shl $32, %%rdx\n\t" "or %%rdx, %0"
    : "=a" (msr)
    :
    : "rdx");
    return msr;
}
void genValue(uint16_t* data, size_t length){
    for (size_t i = 0; i < length; i++){
        data[i] = rand() % length;
    }

}
void testValue(uint16_t* data, size_t length){
    uint16_t mValue = *data;
    for (size_t i = 1; i < length; i++){
        if (mValue > data[i])
            printf("Error %zd\n", i);
        mValue = data[i];
    }
}
int32_t compare_ints(const void* a, const void* b)
{
    uint16_t arg1 = *(const uint16_t*)a;
    uint16_t arg2 = *(const uint16_t*)b;

    return (arg1 > arg2) - (arg1 < arg2);

    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}
void sortTest(const size_t stack){
    uint64_t t[10][2] = {0};
    uint16_t* mTmp = malloc(stack * sizeof(uint16_t));
    uint16_t* mKeys = malloc(stack * sizeof(uint16_t));
    uint16_t* mData = malloc(stack * sizeof(uint16_t));
    genValue(mTmp, stack);
    memcpy(mKeys, mTmp, stack * sizeof(uint16_t));
    t[0][0] = rdtsc();
    FcSort_InsertionU16(mKeys, stack);
    t[0][1] = rdtsc();
    testValue(mKeys, stack);

    memcpy(mKeys, mTmp, stack * sizeof(uint16_t));
    t[1][0] = rdtsc();
    FcSort_RadixU16(mKeys, mData, stack);
    t[1][1] = rdtsc();

    memcpy(mKeys, mTmp, stack * sizeof(uint16_t));
    t[2][0] = rdtsc();
    FcSort_RadixU16_4096(mKeys, mData, stack);
    t[2][1] = rdtsc();

    memcpy(mKeys, mTmp, stack * sizeof(uint16_t));
    t[3][0] = rdtsc();
    FcSort_Heap16(mKeys, stack);
    t[3][1] = rdtsc();


    /* memcpy(mKeys, mTmp, stack * sizeof(uint16_t));
    t[5][0] = rdtsc();
    FcSort_ShellU16(mKeys, stack);
    t[5][1] = rdtsc();

    memcpy(mKeys, mTmp, stack * sizeof(uint16_t));
    t[6][0] = rdtsc();
    FcSort_BubbleU16(mKeys, stack);
    t[6][1] = rdtsc();

     memcpy(mKeys, mTmp, stack * sizeof(uint16_t));
     t[7][0] = rdtsc();
     FcSort_GnomeU16(mKeys, stack);
     t[7][1] = rdtsc();
     testValue(mKeys, stack);
     /*memcpy(mKeys, mTmp, stack * sizeof(uint16_t));
     t[8][0] = rdtsc();
     FcSort_BitonicU16(mKeys, stack);
     t[8][1] = rdtsc();
     testValue(mKeys, stack);*/

    memcpy(mKeys, mTmp, stack * sizeof(uint16_t));
    t[9][0] = rdtsc();
    FcSort_QuicksortU16(mKeys, 0, stack - 1);
    t[9][1] = rdtsc();
    testValue(mKeys, stack);
    printf("%9lu  ", stack);
    for (size_t i = 0; i < 10; i++)
        printf("%6.6f ", ((double)2.0 * stack / (1024 * 1024 * 1024)) / ((t[i][1] - t[i][0]) / (1.9 * 10e9)));
    for (size_t i = 0; i < 10; i++)
        printf("%4.4f ", (double)(t[i][1] - t[i][0]) / stack);
    printf("\n");
    free(mKeys);
    free(mData);
    free(mTmp);
};