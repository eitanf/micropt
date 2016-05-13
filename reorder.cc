/*
 * A slightly improved version of satoi.c
 * There are two minor performance enhacements compared to satoi.c:
 * 1) Break down base return value (3 digits) to repeated
 *    multiplications by 10 to exploit LEA instruction (~1.3% improvement).
 * 2) Reorder branches so that most likely case (4 digits) is
 * checked first, with an early return (addition ~3.3% improvement).
 */
#include "converter.h"

inline quote_t convert(const char *str)
{
  quote_t ret = str[0] - '0';
  ret = ret * 10 + str[1] - '0';
  ret = ret * 10 + str[2] - '0';

  if (str[4] == '\0')  // Most likely outcome first:
    return 10 * ret + str[3] - '0';

  if (str[3] != '\0') {  // Second most likely case:
  	ret = ret * 10 + str[3] - '0';
  	return 10 * ret + str[4] - '0';
  }
  
  return ret;
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  for (unsigned i = 0; i < nlines; i++) {
    nums[i] = convert(lines[i]);
  }
}
