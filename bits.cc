/*
 * Implementation of converter function using bit ops instead of arithmetic ops
 * Adapted from code by Alex Pan.
 */
#include "converter.h"

quote_t convert(char *str)
{
  int out = (str[0] & 15); //<- eliminates extra bitshifts from the loop
  int i = 1;
  for (; str[i] != '\0'; ++i){
  out = (out<<1) + (out<<3) + (str[i] & 15);
  }
  return out;
}
    
void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  for (unsigned i = 0; i < nlines; i++) {
    nums[i] = convert(lines[i]);
  }
}
