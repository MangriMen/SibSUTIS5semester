echo "Size;Time;Threads" > PThread.csv 
for size in 500 1000 2000
do
    for thread in 1 2 4 8 10 12
    do
        ./mainPThread.out -s $size -t $thread >> PThread.csv
    done
done