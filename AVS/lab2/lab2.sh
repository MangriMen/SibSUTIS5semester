echo -e "Model name;$(lscpu | grep "Model name:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}')" > None.csv
echo -e "Model name;$(lscpu | grep "Model name:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}')" > O1.csv
echo -e "Model name;$(lscpu | grep "Model name:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}')" > O2.csv
echo -e "Model name;$(lscpu | grep "Model name:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}')" > O3.csv

read n
g++ mainNone.cpp -Werror -Wextra -Wall
./a.out $n >> None.csv
g++ mainO1.cpp -O1 -Werror -Wextra -Wall
./a.out $n >> O1.csv
g++ mainO2.cpp -O2 -Werror -Wextra -Wall
./a.out $n >> O2.csv
g++ mainO3.cpp -O3 -Werror -Wextra -Wall
./a.out $n >> O3.csv