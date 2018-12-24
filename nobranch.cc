/*
 * An improved version of reorder.cc that defers the substraction of the
 * 'zero' basis from the digits to the end, as opposed to substracting
 * from each digit separately.
 */

#include "converter.h"
#include <cassert>
#include <cstring>
#include <iostream>

inline quote_t convert(const char *str)
{
  constexpr quote_t zero = '0';
  constexpr quote_t fix_3d = 111 * zero;

  const uint32_t mask4d = (str[3] == '\0') - 1;
  const uint32_t mask5d = mask4d & ((str[4] == '\0') - 1);

  // Compute sum of all digits (multiplying by zero if past end of string:
  const quote_t res_3d = str[2] + str[1] * 10 + str[0] * 100;
  const quote_t res_4d = res_3d + (mask4d & (9*res_3d + str[3]));
  const quote_t res_5d = res_4d + (mask5d & (9*res_4d + str[4]));

  const auto fix = fix_3d +
     (mask4d & (1000 * zero)) +  // fix_4d = fix_3d + 1000 zeros
     (mask5d & (10000 * zero));  // fix_5d = fix_4d + 10000 zeros

  return res_5d - fix;
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

  constexpr auto UNROLL_FACTOR = 12;
  assert(!(nlines % UNROLL_FACTOR));
  for (unsigned i = 0; i < nlines; i+= UNROLL_FACTOR) {
    inlined_convert_call<UNROLL_FACTOR>(lines, nums);
  }
}
