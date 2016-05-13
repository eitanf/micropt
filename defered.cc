/*
 * Defer substraction of zeros till after conversion.
 * Written by Will Jones, with minor cleanups.
 */
#include "converter.h"

static quote_t add_first_three(char *lines[], uint32_t i)
{
    return (100 * (int)lines[i][0]) + (10 * (int)lines[i][1]) + (int)lines[i][2];
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
    /*
      We convert the characters to integers, and to get the actual integer value,
      we need to subtract the integer representation of the "0" character. For
      speed, we precompute the total value to subtract for 3, 4, and 5 digit
      numbers.
    */
    
    const char* zero_char = "0";
    const int zero = (int)zero_char[0];
    // adjustment constants for different sizes
    const quote_t fix_3d = 111 * zero;
    const quote_t fix_4d = 1111 * zero;
    const quote_t fix_5d = 11111 * zero;
    

    unsigned i;

    for (i = 0; i < nlines; i++) {
        quote_t sum = 0;

        // Handle first three digits
        sum = add_first_three(lines, i);
        
        // Handle last two digits        
        if (__builtin_expect((lines[i][3] != 0), 1))
            {
                sum = (10 * sum) + (int)lines[i][3];
                
                if (__builtin_expect((lines[i][4] != 0), 0)) {
                    sum = (10 * sum) + (int)lines[i][4];
                    sum = sum - fix_5d;
                }
                else {
                    sum = sum - fix_4d;
                }
            }
        else {
            sum = sum - fix_3d;
        }

        nums[i] = sum;
    }
}
