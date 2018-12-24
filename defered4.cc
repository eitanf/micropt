/*
 * An improved version of defered3.cc that breaks down the arithmetic
 * of each string-len case, allowing the compiler more opportunity for
 * instruction reordering.
 */

#include "converter.h"
#include <cassert>
#include <cstring>
#include <iostream>

inline quote_t convert(const char *str)
{
  constexpr quote_t zero = '0';
  constexpr quote_t fix_3d = 111 * zero;
  constexpr quote_t fix_4d = 1111 * zero;
  constexpr quote_t fix_5d = 11111 * zero;

  if (str[4] == '\0') { // Most likely outcome first:
    return str[0] * 1000 + str[1] * 100 + str[2] * 10 + str[3] - fix_4d;
  }
  if (str[3] != '\0') {  // Second most likely case:
    return str[0] * 10000 + str[1] * 1000 + str[2] * 100 + str[3] * 10 + str[4] - fix_5d;
  }
  return str[0] * 100 + str[1] * 10 + str[2] - fix_3d;
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
