for size in 100 200 300
do
    valgrind --tool=cachegrind ./main.out -s $size opt1
done