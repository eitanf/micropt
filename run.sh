#!/usr/bin/env bash
# This script will run all the executables in the current directory against
# the quotes.txt input and record the best runtime results in a CSV file,
# together with the user-inputted CPU id and compiler data.

echo "Enter CPU ID: "
read cpu
echo "Enter compiler and version: "
read compiler
iters=5000

files=`find . -maxdepth 1 -type f -executable`

for fn in $files
do
  echo -n `basename $fn`,
  runtime=`$fn quotes.txt $iters | grep overall | awk ' { print $6 }'`
  echo "$cpu,$compiler,$iters,$runtime"
done
