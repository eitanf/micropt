/*
 * Look-up-table implementation of atoi for whole numbers.
 * Relies on the fact that ~90% of inputs are 4 digits long.
 * Maps all 4-digit numbers into a static array with
 * precomputed results for that string. The mapping is done by
 * mashing together the only 16 significant bits out of the 4 bytes
 * into a 2-byte array index.
 */
#include "converter.h"

#include <stdlib.h>
#include <stdio.h>

inline constexpr uint16_t compress_4char_str(const char* str)
{
  return
    (*reinterpret_cast<const uint32_t*>(str) & 0x0F) |
    (*reinterpret_cast<const uint32_t*>(str) & 0x0F00) >> 4 |
    (*reinterpret_cast<const uint32_t*>(str) & 0x0F0000) >> 8 |
    (*reinterpret_cast<const uint32_t*>(str) & 0x0F000000) >> 12;
}

static constexpr size_t TABLE_SIZE = 1<<16;

quote_t *compute_lut()
{
  static quote_t *lut = (quote_t *)malloc(sizeof(quote_t) * TABLE_SIZE);
  char str[5];
  for (unsigned i = 1000; i < 10000; i++) {
    sprintf(str, "%u", i);
    lut[compress_4char_str(str)] = i;
  }
  return lut;
}

inline quote_t fast_atoi(const char* str)
{
  if (str[4] != '\0') {
    return atoi(str);
  }
  static auto lut = compute_lut();
  const quote_t ret = lut[compress_4char_str(str)];
  return ret;
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  for (unsigned i = 0; i < nlines; i++) {
    nums[i] = fast_atoi(lines[i]);
  }
}
