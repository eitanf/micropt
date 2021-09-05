CC="${CC:-g++-10}"
COMPILE="${CC} -Ofast -DNDEBUG -std=c++17 -march=native  -Wall -Wextra -pedantic"


echo "Compiling with ${COMPILE}..."
for fn in *.cc
do
    $COMPILE -o ${fn%%.*} driver.c $fn &
done
wait
