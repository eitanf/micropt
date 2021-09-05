#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#include "converter.h"

// Check that all values have been converted correctly:
bool equal(quote_t nums[], char *strs[], uint32_t n)
{
  for (uint32_t i = 0; i < n; ++i) {
    if (nums[i] != (quote_t)atoi(strs[i])) {
      printf("For %u-th string: %s, got value: %u\n", i+1, strs[i], nums[i]);
      return false;
    }
  }
  return true;
}


// Shuffle two random values in the strings array, as long as they're the same size.
void swap_random_pair(char* strs[], uint32_t n)
{
  uint32_t p1, p2;
  while (true) {
    p1 = rand() % n;
    p2 = rand() % n;
    if (strlen(strs[p1]) == strlen(strs[p2])) {
      break;
    }
  }

  char tmp[10];
  strcpy(tmp, strs[p1]);
  strcpy(strs[p1], strs[p2]);
  strcpy(strs[p2], tmp);
}


int main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(stderr, "Requires arguments: quotes filename and no. of repetitions\n");
    exit(-1);
  }

  // Find out length of input:
  int64_t datasize;
  FILE *fin;
  if ((fin = fopen(argv[1], "r")) == NULL) {
    perror("open input file");
    exit(-2);
  }
  if (fseek(fin, 0L, SEEK_END) == -1) {
    perror("fseek input file");
    exit(-3);
  }
  if ((datasize = ftell(fin)) == -1) {
    perror("ftell input file");
    exit(-4);
  }
  rewind(fin);

  // Read in file and parse EOL tokens:
  char *data = (char *)calloc(datasize + 1, 1);
  if (fread(data, 1, datasize, fin) < 1) {
    perror("read input file");
    exit(-5);
  }
  fclose(fin);

  char **lines = (char **)malloc(sizeof(char *) * datasize);  // A bit overkill allocation, but easy.
  unsigned nlines = 0;
  lines[nlines++] = strtok(data, "\n");
  while ((lines[nlines] = strtok(NULL, "\n"))) {
    nlines++;
  }


  // Finally, main timing loop:
  double min_t = 1000000000.;
  uint32_t *nums = (uint32_t *)calloc(sizeof(uint32_t), nlines);
  const int niter = atoi(argv[2]);

  for (int iter = 0; iter < niter; ++iter) {
    if (!(iter % 1000)) {
      printf("On iteration #%d\tBest so far: %g\n", iter, min_t);
    }
    swap_random_pair(lines, nlines);

    clock_t t0 = clock();
    convert_all(nlines, lines, nums);
    double t = (double)(clock() - t0) / CLOCKS_PER_SEC;

    assert(equal(nums, lines, nlines));
    if (t < min_t) {
      min_t = t;
    }
  }

  printf("Best run time overall (sec): %g\n", min_t);
  free(nums);
  free(lines);
  free(data);
  return 0;
}
