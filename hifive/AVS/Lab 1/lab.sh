#!/bin/bash
echo `date`;
whoami;
hostname;
echo "Процессор:";
echo -e -n "\tМодель: - ";
lscpu | grep "Model name:" | awk '{for ( i = 3; i < NF+2; i++ ) printf("%s ", $i)}';
echo -e -n "\tАрхитектура: - ";
lscpu | grep "Architecture:";
echo -e -n "\tТактовая частота: - \n";
echo -e -n "\tКоличество ядер: - ";
lscpu | grep "CPU(s):";
echo -e -n "\tКоличество потоков на одно ядро: - ";
lscpu | grep "Thread(s) per core:";
echo "Оперативная память:";
free;
echo "Жёсткий диск:";
echo -e -n "\tВсего: -\n";
echo -e -n "\tДоступно: -\n";
echo -e -n "\tСмонтировано в корневую директорию / –\n";
echo -e -n "\tSWAP всего –\n";
echo -e -n "\tSWAP доступно –\n";
echo "Сетевые интерфейсы:";
echo -e -n "\tКоличество сетевых интерфейсов –\n";
