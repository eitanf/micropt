/*
 * Look-up-table implementation of atoi for whole numbers.
 * Relies on the fact that ~90% of inputs are 4 digits long.
 * Maps all 4-digit numbers into a static array with
 * precomputed results for that string. The mapping is done by
 * mashing together the only 16 significant bits out of the 4 bytes
 * into a 2-byte array index.
 * Unlike lut2.cc, on which this code is based, the mapping to a 16-bit
 * array index is done with the intrinsic pext instruction.
 *
 * This version intentionally leaks memory, and should probably be 
 * rewritten to use constexpr instead of static once pext_u32 supports it.
 */
#include "converter.h"

#include <cassert>
#include <immintrin.h>
#include <stdlib.h>
#include <stdio.h>

inline uint16_t compress_4char_str(const char* str)
{
  return _pext_u32(*reinterpret_cast<const unsigned int*>(str), 0x0F0F0F0F);
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

inline quote_t convert(const char* str)
{
  static auto lut = compute_lut();
  const quote_t val = lut[compress_4char_str(str)];

  if (str[4] == 0) {
    return val;
  }
  if (str[3] == 0) {
    return val / 10;
  }
  else return val * 10 + str[4] - '0';
}

// This is a wrapper call around convert() that calls it N times. It
// gets automatically inlined by the compiler, but saves the need to
// copy and paste the call N times.
template <int N>
void inlined_convert_call(char**& lines, quote_t*& nums)
{
  *nums++ = convert(*lines++);
  inlined_convert_call<N-1>(lines, nums);
}

template <>
void inlined_convert_call<0>(char**&, quote_t*&)
{
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{

  constexpr auto UNROLL_FACTOR = 6;
  assert(!(nlines % UNROLL_FACTOR));
  for (unsigned i = 0; i < nlines; i+= UNROLL_FACTOR) {
    inlined_convert_call<UNROLL_FACTOR>(lines, nums);
  }
}
