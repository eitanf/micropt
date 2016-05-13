/*
 * SSE4.2 implementation of converter,
 * based on http://www.mersenneforum.org/showthread.php?t=11590
 */
#include "converter.h"
#include <emmintrin.h>
#include <tmmintrin.h>


inline __m128i right_justify(__m128i input, int& ct)
{
  __m128i zeros, subzeros, tens, seq;
  zeros = _mm_set_epi32(0x30303030,0x30303030,0x30303030,0x30303030);
  subzeros = _mm_set_epi32(0x2f2f2f2f,0x2f2f2f2f,0x2f2f2f2f,0x2f2f2f2f);
  tens = _mm_set_epi32(0x3a3a3a3a,0x3a3a3a3a,0x3a3a3a3a,0x3a3a3a3a);
  seq = _mm_set_epi32(0x0f0e0d0c,0x0b0a0908,0x07060504,0x03020100);
  __m128i rev = _mm_set_epi32(0x00010203,0x04050607,0x08090a0b,0x0c0d0e0f);
  __m128i mask = _mm_cmpeq_epi8(rev,rev);
  __m128i m70 = _mm_set_epi32(0x70707070,0x70707070,0x70707070,0x70707070);

  __m128i below_0 = _mm_cmpgt_epi8(input, subzeros);
  __m128i above_9 = _mm_cmplt_epi8(input, tens);
  __m128i valid = _mm_and_si128(below_0, above_9);

  int plink = _mm_movemask_epi8(valid);
  int shift = __builtin_ffs(plink^0xffff)-1; ct=shift;
  __m128i sklunk = _mm_set_epi8(shift,shift,shift,shift,shift,shift,shift,shift,shift,shift,shift,shift,shift,shift,shift,shift);

  // I don't know how you'd do the 128-bit-wide shift without pshufb
  // but it's quite pretty with pshufb:
  __m128i ss2 = _mm_add_epi8(sklunk, seq);
  __m128i ss3 = _mm_add_epi8(m70, ss2);
  __m128i shift2 = _mm_shuffle_epi8(input, ss2);
  __m128i shift3 = _mm_shuffle_epi8(zeros, ss3);
  __m128i masks = _mm_shuffle_epi8(mask, ss3);
  __m128i yibble = _mm_or_si128(shift3,_mm_andnot_si128(masks, shift2));
  return yibble;
}

inline long long u64_from_rj(__m128i input)
{
  __m128i zeros = _mm_set_epi32(0x30303030,0x30303030,0x30303030,0x30303030);
  __m128i mask1 = _mm_set_epi32(0xff00ff00,0xff00ff00,0xff00ff00,0xff00ff00);
  __m128i mask2 = _mm_set_epi32(0xffff0000,0xffff0000,0xffff0000,0xffff0000);
  __m128i hundreds = _mm_set_epi32(0x00000064,0x00000064,0x00000064,0x00000064);
  //  aus(input);
  __m128i corr = _mm_sub_epi32(input, zeros);
  // multiply alternate digits by 10
  // can use 16-bit-wide shifts since everything is less than 10
  __m128i scaled = _mm_add_epi8(_mm_slli_epi16(corr,11),_mm_slli_epi16(corr,9));
  __m128i step1 = _mm_and_si128(mask1,_mm_add_epi8(corr,scaled));
  // multiply alternate digit-pairs by 100 and add
  __m128i step2 = _mm_add_epi16(_mm_slli_epi32(_mm_mullo_epi16(_mm_srli_epi16(step1,8), hundreds),16),
        _mm_srli_epi16(step1,8));
  step2 = _mm_srli_epi32(_mm_and_si128(mask2, step2),16);
  //  aus(step2);
  // do final step in integer registers
  unsigned int Q[4];
  _mm_storeu_si128((__m128i*)Q,step2);
  long long a12,a8,a4,a0;
  a0=1; a4=10000; a8=a4*a4; a12=a8*a4;
  //  printf("%d %d %d %d\n",Q[0],Q[1],Q[2],Q[3]);
  return a0*Q[3] + a4*Q[2] + a8*Q[1] + a12*Q[0];
}



void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  int ct;

  for (unsigned i = 0; i < nlines - 4; i++) {
    __m128i input = _mm_loadu_si128((__m128i*)lines[i]);
    __m128i justified = right_justify(input, ct);
    nums[i] = u64_from_rj(justified);
  }

  nums[nlines - 4] = atoi(lines[nlines - 4]);
  nums[nlines - 3] = atoi(lines[nlines - 3]);
  nums[nlines - 2] = atoi(lines[nlines - 2]);
  nums[nlines - 1] = atoi(lines[nlines - 1]);
}
