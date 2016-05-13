/*
 * Trivial implementation of converter function using Boost library.
 * You may override this file or create your own.
 */
#include "converter.h"

#include <boost/lexical_cast.hpp>

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  for (unsigned i = 0; i < nlines; i++) {
    nums[i] = boost::lexical_cast<quote_t>(lines[i]);
  }
}
