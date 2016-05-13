/*
 * Look-up-table implementation of atoi for whole numbers.
 * Each lookup table maps the lower 12 bits of a two-digit string
 * to the corresponding number, possibly pre-multiplying it by a
 * constant factor.
 * Note: this version leaks some memory for the static LUT. It can
 * be easily encapsulated in a singleton to take care of deallocating.
 */
#include "converter.h"
#include <stdlib.h>

static constexpr size_t TABLE_SIZE = (1<<12);

// Create a lookup table for two BCD digits, separated by four useless bits
template <typename storage_t = quote_t>
storage_t *compute_lut(quote_t multiplier = 1)
{
  storage_t *lut = (storage_t *)malloc(sizeof(storage_t) * TABLE_SIZE);
  for (storage_t i = 0; i < 100; i++) {
    const auto idx = ((i % 10) << 8) + (i / 10);
    lut[idx] = multiplier * i;
  }
  return lut;
}

inline quote_t fast_atoi(const char* str)
{
  static auto lut_msp = compute_lut<uint16_t>(100);
  static auto lut_lsp = compute_lut<uint8_t>(1);

  const auto asnum = *reinterpret_cast<const uint32_t *>(str);
  const auto msp = asnum & 0x0F0F;
  if (str[3] == '\0') {
    return 10 * lut_lsp[msp] + str[2] - '0';
  }

  const auto high = asnum >> 16;
  const auto lsp = high & 0x0F0F;
  const quote_t four_digit_num = lut_msp[msp] + lut_lsp[lsp];
  if (str[4] == '\0') {
    return four_digit_num;
  } else {
    return 10 * four_digit_num + str[4] - '0';
  }
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  for (unsigned i = 0; i < nlines; i++) {
    nums[i] = fast_atoi(lines[i]);
  }
}
