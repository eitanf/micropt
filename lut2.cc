/*
 * Look-up-table implementation of atoi for whole numbers.
 * Relies on the fact that ~90% of inputs are 4 digits long.
 * Maps all 4-digit numbers into a static array with
 * precomputed results for that string. The mapping is done by
 * mashing together the only 16 significant bits out of the 4 bytes
 * into a 2-byte array index.
 */
#include "converter.h"

#include <array>

inline constexpr uint16_t
compress_4char_str(const char str[4])
{
  return
    (str[3] & 0x0F) |
    (str[2] & 0x0F) << 4 |
    (str[1] & 0x0F) << 8 |
    (str[0] & 0x0F) << 12;
}

constexpr size_t TABLE_SIZE = 1<<16;
using lut_t = std::array<quote_t, TABLE_SIZE>;

constexpr lut_t
compute_lut()
{
  lut_t lut { 0 };
  char buf[5] = "0000";

  for (unsigned i = 1000; i < 10000; i++) {
    buf[3] = (i % 10) + '0';
    buf[2] = (i % 100 / 10) + '0';
    buf[1] = (i % 1000 / 100) + '0';
    buf[0] = (i / 1000) + '0';
    lut[compress_4char_str(buf)] = i;
  }
  return lut;
}

constexpr auto lut = compute_lut();

inline quote_t fast_atoi(const char* str)
{
  if (str[4] != '\0') {
    return atoi(str);
  }
  const quote_t ret = lut[compress_4char_str(str)];
  return ret;
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  for (unsigned i = 0; i < nlines; i++) {
    nums[i] = fast_atoi(lines[i]);
  }
}
