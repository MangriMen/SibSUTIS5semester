echo -e "Model name;$(lscpu | grep "Model name:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}')" > O1.csv
echo -e "Model name;$(lscpu | grep "Model name:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}')" > O2.csv
echo -e "Model name;$(lscpu | grep "Model name:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}')" > O3.csv

g++ mainO1.cpp -O1 -Werror -Wextra -Wall -o mainO1.out
g++ mainO2.cpp -O2 -Werror -Wextra -Wall -o mainO2.out
g++ mainO3.cpp -O3 -Werror -Wextra -Wall -o mainO3.out
read n
./mainO1.out $n >> O1.csv
./mainO2.out $n >> O2.csv
./mainO3.out $n >> O3.csv