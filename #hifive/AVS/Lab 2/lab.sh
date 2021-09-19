#!/bin/bash
#
#Процессор

lscpu | grep -i 'Model name' | awk '{print $3,$4,$5,$6}' > test.csv
g++ main.cpp -Werror -Wextra -Wall
read n
./a.out $n >> test.csv