// Alyssa Riceman

#include "converter.h"

inline uint32_t shortCstringToUint(char* cstring) {
    uint32_t result = ((uint32_t)cstring[0]) - 48;
    for (uint_fast8_t i = 1; cstring[i] != 0; i++) {
        result = (result * 10) + (((uint32_t)cstring[i]) - 48);
    }
    return result;
}

void convert_all(unsigned nlines, char* lines[], quote_t nums[]) {
    uint_fast32_t i = 0;
    while (i < nlines) {
        nums[i] = shortCstringToUint(lines[i]);
        i++;
        nums[i] = shortCstringToUint(lines[i]);
        i++;
        nums[i] = shortCstringToUint(lines[i]);
        i++;
        nums[i] = shortCstringToUint(lines[i]);
        i++;
        nums[i] = shortCstringToUint(lines[i]);
        i++;
        nums[i] = shortCstringToUint(lines[i]);
        i++;
        nums[i] = shortCstringToUint(lines[i]);
        i++;
        nums[i] = shortCstringToUint(lines[i]);
        i++;
        nums[i] = shortCstringToUint(lines[i]);
        i++;
        nums[i] = shortCstringToUint(lines[i]);
        i++;
        nums[i] = shortCstringToUint(lines[i]);
        i++;
        nums[i] = shortCstringToUint(lines[i]);
        i++;
    }
}
