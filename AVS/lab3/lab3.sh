echo "Memory test started"
echo "Testing RAM..."
./memory_test.out -m RAM -b 4Mb,8Mb,12Mb,16Mb,20Mb,24Mb,28Mb,32Mb,36Mb,40Mb,44Mb,48Mb,52Mb,56Mb,60Mb,64Mb,68Mb,72Mb,76Mb,80Mb -l 4 -f -d short,int,llong
echo "RAM done"
echo "Testing SSD... (/mnt/c/Users/mangr/AppData/Local/Temp/memorytest.bin)"
./memory_test.out -m SSD -b 4Mb,8Mb,12Mb,16Mb,20Mb,24Mb,28Mb,32Mb,36Mb,40Mb,44Mb,48Mb,52Mb,56Mb,60Mb,64Mb,68Mb,72Mb,76Mb,80Mb -l 4 -f -d short,int,llong -t /mnt/c/Users/mangr/AppData/Local/Temp/memorytest.bin
echo "SSD done"
echo "Testing HDD... (/mnt/d/memorytest.bin)"
./memory_test.out -m HDD -b 4Mb,8Mb,12Mb,16Mb,20Mb,24Mb,28Mb,32Mb,36Mb,40Mb,44Mb,48Mb,52Mb,56Mb,60Mb,64Mb,68Mb,72Mb,76Mb,80Mb -l 4 -f -d short,int,llong -t /mnt/d/memorytest.bin
echo "HDD done"
echo "Testing FLASH...(/mnt/f/memorytest.bin)"
./memory_test.out -m FLASH -b 4Mb,8Mb,12Mb,16Mb,20Mb,24Mb,28Mb,32Mb,36Mb,40Mb,44Mb,48Mb,52Mb,56Mb,60Mb,64Mb,68Mb,72Mb,76Mb,80Mb -l 4 -f -d short,int,llong -t /mnt/f/memorytest.bin
echo "FLASH done"