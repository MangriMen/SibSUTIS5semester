echo "Size;Time;Threads" > OpenMP.csv 
for size in 500 1000 2000
do
    for thread in 1 2 4 8 10 12
    do
        ./mainOpenMP.out -s $size -t $thread >> OpenMP.csv
    done
done