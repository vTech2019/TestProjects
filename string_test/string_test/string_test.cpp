#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
extern "C" void string_reverse_X64(uint8_t text[], size_t length);

__declspec(noinline) void string_reverse(uint8_t text[], volatile size_t length) {
    size_t i, j, k, z, tmp, code = 0;
    for (z = 0, i = length - 1; z < 2; z++, code = ' ', i = 0)
        for (j = 0; i < length; i++)
            if (text[i] == code || i == length - 1) {
                for (k = j, j = i - 1; k < j; k++, j--) {
                    tmp = text[k];
                    text[k] = text[j];
                    text[j] = tmp;
                }
                j = i + 1;
            }
}

int main() {
    uint8_t text_0[] = "Two wrongs make a right in C++.Two wrongs make a right in C++.Two wrongs make a right in C++.Two wrongs make a right in C++.";
    uint64_t i = sizeof(text_0);
    uint64_t time_00, time_01, time_10, time_11;
    time_10 = __rdtsc();
    string_reverse(text_0, i);
    time_11 = __rdtsc();
    time_00 = __rdtsc();
    string_reverse_X64(text_0, i);
    time_01 = __rdtsc();
    printf("%s\n%s\n%lld %lld\n", text_0, text_0, time_01 - time_00, time_11 - time_10);

    return 0;
}