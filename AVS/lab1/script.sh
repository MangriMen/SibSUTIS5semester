#!/bin/bash
echo `date`;
whoami;
hostname;
echo "Процессор:"
echo -e -n "\tМодель - "
lscpu | grep "Model name:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}'
lscpu | grep "Architecture:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}'
lscpu | grep "CPU MHz:" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}'
lscpu | grep "CPU(s):" | awk '{for(i=3;i<NF+2;i++) printf("%s ", $i)}'
lscpu | grep "Thread(s) per core:"
echo "Оперативная память:"
echo -e -n "\tВсего - "
free | grep "Mem:" | cut -c1
echo -e -n "\tДоступно - "
free | grep "Mem:" | cut -c1
echo "Жёсткий диск:"
echo -e -n "\tВсего - "
echo -e -n "\tДоступно - "
echo -e -n "\tСмонтировано в корневую директорию / -"
echo -e -n "\tSWAP всего - "
echo -e -n "\tSWAP доступно - "
echo "Сетевые интерфейсы:"
echo -e -n "\tКоличество сетевых интрефейсов - "