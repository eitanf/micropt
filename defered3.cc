/*
 * An improved version of reorder.cc that defers the substraction of the
 * 'zero' basis from the digits to the end, as opposed to substracting
 * from each digit separately.
 */

#include "converter.h"
#include <cassert>

inline quote_t convert(const char *str)
{
  static const quote_t zero = '0';
  static const quote_t fix_3d = 111 * zero;
  static const quote_t fix_4d = 1111 * zero;
  static const quote_t fix_5d = 11111 * zero;

  quote_t ret = str[2] + str[1] * 10 + str[0] * 100;

  if (str[4] == '\0') { // Most likely outcome first:
    ret = ret * 10 + str[3];
    return ret - fix_4d;
  }

  if (str[3] != '\0') {  // Second most likely case:
    ret = ret * 10 + str[3];
    ret = ret * 10 + str[4];
    return ret - fix_5d;
  }
  
  return ret - fix_3d;
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
void inlined_convert_call<0>(char**& lines, quote_t*& nums)
{
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{

  constexpr auto UNROLL_FACTOR = 5;
  assert(!(nlines % UNROLL_FACTOR));
  for (unsigned i = 0; i < nlines; i+= UNROLL_FACTOR) {
    inlined_convert_call<UNROLL_FACTOR>(lines, nums);
  }
}
