/*
 * A variation on the unrolling version by Ben Black
 */

#include "converter.h"
#include <utility>
#include <stdlib.h>

#define do_2 {num2 *= 10; num2 += *numstr2 - 48;numstr2++;}
#define do_1 {num1 *= 10; num1 += *numstr1 - 48;numstr1++;}
#define do_many_1(n) {for (size_t i = 0; i < n; i++) {if(*numstr1){do_1}}}
#define do_many_2(n) {for (size_t i = 0; i < n; i++) {if(*numstr2){do_2}}}

using intpair = std::pair<uint32_t,uint32_t>;
template<const int maxiters>
struct calc{
    intpair operator()(char * numstr1,char * numstr2,uint32_t num1,uint32_t num2){
        if(*numstr1 & *numstr2){
            //this is eqivalent to *numstr1 && *numstr2 because all charachter
            //digits have the 32 bit in common
            do_1
            do_2
            return calc<maxiters-1>()(numstr1,numstr2,num1,num2);
        }
        else if (*numstr1){
            do_1
            do_many_1(maxiters-1)
            return std::make_pair(num1,num2);
        }
        else{
            do_many_2(maxiters)
            return std::make_pair(num1,num2);
        }
    }
};
template<>
struct calc<0>{
    intpair operator()(char *, char *, uint32_t num1, uint32_t num2){
        return  std::make_pair(num1,num2);
    }
};
void convert_all(unsigned nlines, char *lines[], quote_t nums[]){
    constexpr size_t maxnum = 10;
    for(size_t ll = 0;ll < nlines; ll += 2){
        char * numstr1 = lines[ll];
        char * numstr2 = lines[ll+1];
        uint32_t num1 = 0;
        uint32_t num2 = 0;
        do_1
        do_2
        
        intpair res = calc<maxnum-1>()(numstr1,numstr2,num1,num2);
        
        nums[ll] = res.first;
        nums[ll+1] = res.second;
    }
    if(nlines%2){
        nums[nlines-1] = atoi(lines[nlines-1]);
    }
}
