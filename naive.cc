/*
 * Naive implementation of converter function: a simple loop
 * that converts one character at a time.
 */
#include "converter.h"

quote_t convert(char *str)
{
  quote_t ret = 0;
  while (*str) {
    ret = ret * 10 + *str - '0';
    str++;
  }
  return ret;
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  for (unsigned i = 0; i < nlines; i++) {
    nums[i] = convert(lines[i]);
  }
}
