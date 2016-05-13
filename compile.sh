COMPILE="g++-5 -O3 -DNEDBUG -std=c++14 -march=native -Werror -Wall -Wextra -pedantic"
for fn in *.cc
do
    $COMPILE -o ${fn%%.*} driver.c $fn &
done
wait
