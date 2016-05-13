/*
 * Trivial implementation of converter function using atoi().
 */
#include "converter.h"

#include <stdlib.h>

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  for (unsigned i = 0; i < nlines; i++) {
    nums[i] = atoi(lines[i]);
  }
}
