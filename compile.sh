COMPILE="g++-8 -Ofast -DNEDBUG -std=c++17 -march=native   -Wall -Wextra -pedantic"
for fn in *.cc
do
    $COMPILE -o ${fn%%.*} driver.c $fn &
done
wait
