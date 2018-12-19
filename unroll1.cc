/*
 * A loop-unrolling version of naive.cc, written by Ben Black
 */

#include "converter.h"
#include <stdlib.h>

void convert_all(unsigned nlines, char *lines[], quote_t nums[]){
    const size_t maxnum = 10;
    for(size_t ll = 0;ll < nlines; ll++){
        char * numstr = lines[ll];
        uint32_t num = 0;
        for(size_t i = 0; i < maxnum; i++){
            num *= 10;
            num += uint8_t(*numstr) - 48;
            numstr++;
            if(!uint8_t(*numstr)){
                break;
            }
        }
        nums[ll] = num;
    }
}
