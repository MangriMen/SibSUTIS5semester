echo "Size;Time" > opt0.csv 
for size in 100 200 300 400 500 600 700 800 900 1000
do
    ./main.out -s $size opt0 >> opt0.csv
done