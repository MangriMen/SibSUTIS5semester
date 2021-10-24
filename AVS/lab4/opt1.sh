echo "Size;Time" > opt1.csv 
for size in 100 200 300 400 500 600 700 800 900 1000
do
    ./main.out -s $size opt1 >> opt1.csv
done