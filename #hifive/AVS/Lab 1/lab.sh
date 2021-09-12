#!/bin/bash

echo "Дата: `date`;"
echo "Имя учётной записи: $(whoami);"
echo "Доменное имя ПК: $(hostname);"

echo "Процессор:"
echo -e "\tМодель - $(lscpu | grep "Model name:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}')"
echo -e "\tАрхитектура - $(lscpu | grep "Architecture:" | awk '{for(i=2;i<NF+2;i++) printf("%s ", $i)}')"
echo -e "\tТактовая частота - $(lscpu | grep "CPU MHz:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}')"
echo -e "\tКоличество ядер - $(lscpu | grep "CPU(s):" | awk '{for(i=2;i<NF+2;i++) printf("%s ", $i)}')"
echo -e "\tКоличество потоков на одно ядро - $(lscpu | grep "Thread(s) per core:" | awk '{for(i=4;i<NF+2;i++) printf("%s ", $i)}')"

echo "Оперативная память:"
echo -e "\tВсего - $(free -h | grep "Mem:" | awk '{printf $2}')"
echo -e "\tДоступно - $(free -h | grep "Mem:" | awk '{printf $4}')"

echo "Жёсткий диск:"
echo -e "\tВсего - $(df -h | grep "C:\\\\" | awk '{printf $2}')"
echo -e "\tДоступно - $(df -h / | grep "/" | awk '{printf $4}')"
echo -e "\tСмонтировано в корневую директорию / - $(df -h / | awk 'NR == 2 {printf $2}')"
echo -e "\tSWAP всего - $(free -h | grep "Swap:" | awk '{printf $2}')"
echo -e "\tSWAP доступно - $(free -h | grep "Swap:" | awk '{printf $4}')"

echo "Сетевые интерфейсы:"

OLDIFS=$IFS
IFS=$'\n'
count=0
for interface in $(ifconfig -s -a)
do
    count=$(( $count + 1 ))
done
count=$(( $count - 1 ))

echo -e "\tКоличество сетевых интрефейсов - $count\n"

printf "%-2s" "N"
printf "%-14s" "Имя"
printf "%-26s" "MAC адрес"
printf "%-21s" "IP адрес"
printf "%-5s\n" "Скорость соединения"

count=0
for interface in $(ifconfig -s -a | awk '{print $1}')
do
    if (( $count > 0 )); then
        printf "%-2d" $(( $count ))
        printf "%-11s" $interface
        printf "%-21s" $(ifconfig $interface | grep "ether" | awk '{printf $2}')
        printf "%-16s" $(ifconfig $interface | grep "inet " | awk '{printf $2}')
        printf "%-5s\n" $(ifconfig $interface | grep "mtu" | awk '{printf $4}')
    fi
    count=$(($count + 1))
done
IFS=$OLDIFS