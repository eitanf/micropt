/*
 * A short-cut version of atoi with few branches.
 * Relies on the fact that ~94% of inputs are 4 digits long.
 */
#include "converter.h"

#include <stdlib.h>

inline quote_t fast_atoi(char* str)
{
  quote_t ret = 100 * (str[0] - '0') +
                 10 * (str[1] - '0') +
                  1 * (str[2] - '0');
  if (str[3] != '\0') {
    ret = 10 * ret + str[3] - '0';
    if (str[4] != '\0') {
      ret = 10 * ret + str[4] - '0';
    }
  }
  return ret;
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  for (unsigned i = 0; i < nlines; i++) {
    nums[i] = fast_atoi(lines[i]);
  }
}
