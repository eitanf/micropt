/*
 * Implementation of converter function using bit ops instead of arithmetic ops.
 * This version has no loops, it assumes a 3-, 4-, or 5-digit string.
 * Adapted from code by Alex Pan.
 */
#include "converter.h"

quote_t convert(char *str)
{
  int out = (str[0] & 15);
  out = (out<<1) + (out<<3) + (str[1] & 15);
  out = (out<<1) + (out<<3) + (str[2] & 15);
  if (str[3] =='\0') return out;
  out = (out<<1) + (out<<3) + (str[3] & 15);
  if (str[4] =='\0') return out;
  out = (out<<1) + (out<<3) + (str[4] & 15);
  return out;
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  for (unsigned i = 0; i < nlines; i++) {
    nums[i] = convert(lines[i]);
  }
}
