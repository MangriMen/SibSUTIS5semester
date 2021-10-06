rm *.dat
files[0]=RAMSERIES
files[1]=HDDSERIES
files[2]=SSDSERIES
files[3]=FLASHSERIES
for file in ${files[*]}
do
    cat "$file.csv" | awk -F ";" '{print $2 " " $9}' | awk '{gsub(/,/,".")}1'  > "$file.dat"
done
gnuplot << eor
    set terminal pngcairo size 1200, 600
    set output '1.1.png'
    set style data linespoints
    set xlabel "BlockSize"
    set ylabel "WriteBandwidth(Mb/s)"
    set format x "%.0f"
    set format y "%g"
    set ytics 2
    set logscale y
    set style line 1 lt 2 pt 7 lc rgb "red" lw 2
    set style line 2 lt 2 pt 7 lc rgb "blue" lw 2
    set style line 3 lt 2 pt 7 lc rgb "green" lw 2
    set style line 4 lt 2 pt 7 lc rgb "magenta" lw 2
    files=system('ls -1B *.dat')
    plot for [i=1:words(files)] word(files, i) u 1:2 ls i title word(files, i)
eor
rm *.dat
for file in ${files[*]}
do
    cat "$file.csv" | awk -F ";" '{print $2 " " $14}' | awk '{gsub(/,/,".")}1'  > "$file.dat"
done
gnuplot << eor
    set terminal pngcairo size 1200, 600
    set output '1.2.png'
    set style data linespoints
    set xlabel "BlockSize"
    set ylabel "ReadBandwidth(Mb/s)"
    set format x "%.0f"
    set format y "%g"
    set logscale y
    set ytics 2
    set style line 1 lt 2 pt 7 lc rgb "red" lw 2
    set style line 2 lt 2 pt 7 lc rgb "blue" lw 2
    set style line 3 lt 2 pt 7 lc rgb "green" lw 2
    set style line 4 lt 2 pt 7 lc rgb "magenta" lw 2
    files=system('ls -1B *.dat')
    plot for [i=1:words(files)] word(files, i) u 1:2 ls i title word(files, i)
eor
rm *.dat
for file in ${files[*]}
do
    cat "$file.csv" | awk -F ";" '{print $2 " " $10}' | awk '{gsub(/,/,".")}1'  > "$file.dat"
done
gnuplot << eor
    set terminal pngcairo size 1200, 600
    set output '2.1.png'
    set style data linespoints
    set xlabel "BlockSize"
    set ylabel "AbsError(write)(s)"
    set format x "%.0f"
    set format y "%g"
    set logscale y
    set ytics 2
    set style line 1 lt 2 pt 7 lc rgb "red" lw 2
    set style line 2 lt 2 pt 7 lc rgb "blue" lw 2
    set style line 3 lt 2 pt 7 lc rgb "green" lw 2
    set style line 4 lt 2 pt 7 lc rgb "magenta" lw 2
    files=system('ls -1B *.dat')
    plot for [i=1:words(files)] word(files, i) u 1:2 ls i title word(files, i)
eor
rm *.dat
for file in ${files[*]}
do
    cat "$file.csv" | awk -F ";" '{print $2 " " $15}' | awk '{gsub(/,/,".")}1'  > "$file.dat"
done
gnuplot << eor
    set terminal pngcairo size 1200, 600
    set output '2.2.png'
    set style data linespoints
    set xlabel "BlockSize"
    set ylabel "AbsError(read)(s)"
    set format x "%.0f"
    set format y "%g"
    set logscale y
    set ytics 2
    set style line 1 lt 2 pt 7 lc rgb "red" lw 2
    set style line 2 lt 2 pt 7 lc rgb "blue" lw 2
    set style line 3 lt 2 pt 7 lc rgb "green" lw 2
    set style line 4 lt 2 pt 7 lc rgb "magenta" lw 2
    files=system('ls -1B *.dat')
    plot for [i=1:words(files)] word(files, i) u 1:2 ls i title word(files, i)
eor
rm *.dat
for file in ${files[*]}
do
    cat "$file.csv" | grep "4194304" -m 10 | awk -F ";" '{print $5 " " $10}' | awk '{gsub(/,/,".")}1'  > "$file.dat"
done
gnuplot << eor
    set terminal pngcairo size 1200, 600
    set output '3.1.png'
    set style data linespoints
    set xlabel "LaunchNum"
    set ylabel "AbsError(write)(s)"
    set format x "%.0f"
    set format y "%g"
    set logscale y
    set ytics 2
    set style line 1 lt 2 pt 7 lc rgb "red" lw 2
    set style line 2 lt 2 pt 7 lc rgb "blue" lw 2
    set style line 3 lt 2 pt 7 lc rgb "green" lw 2
    set style line 4 lt 2 pt 7 lc rgb "magenta" lw 2
    files=system('ls -1B *.dat')
    plot for [i=1:words(files)] word(files, i) u 1:2 ls i title word(files, i)
eor
rm *.dat
for file in ${files[*]}
do
    cat "$file.csv" | grep "4194304" -m 10 | awk -F ";" '{print $5 " " $15}' | awk '{gsub(/,/,".")}1'  > "$file.dat"
done
gnuplot << eor
    set terminal pngcairo size 1200, 600
    set output '3.2.png'
    set style data linespoints
    set xlabel "LaunchNum"
    set ylabel "AbsError(read)(s)"
    set format x "%.0f"
    set format y "%g"
    set logscale y
    set ytics 2
    set style line 1 lt 2 pt 7 lc rgb "red" lw 2
    set style line 2 lt 2 pt 7 lc rgb "blue" lw 2
    set style line 3 lt 2 pt 7 lc rgb "green" lw 2
    set style line 4 lt 2 pt 7 lc rgb "magenta" lw 2
    files=system('ls -1B *.dat')
    plot for [i=1:words(files)] word(files, i) u 1:2 ls i title word(files, i)
eor
rm *.dat
for file in ${files[*]}
do
    cat "$file.csv" | awk -F ";" '{print $4 " " $9}' | awk '{gsub(/,/,".")}1'  > "$file.dat"
done
gnuplot << eor
    set terminal pngcairo size 1200, 600
    set output '4.1.png'
    set style data linespoints
    set xlabel "BufferSize"
    set ylabel "WriteBandwidth(Mb/s)"
    set format x "%.0f"
    set format y "%g"
    set logscale y
    set ytics 2
    set style line 1 lt 2 pt 7 lc rgb "red" lw 2
    set style line 2 lt 2 pt 7 lc rgb "blue" lw 2
    set style line 3 lt 2 pt 7 lc rgb "green" lw 2
    set style line 4 lt 2 pt 7 lc rgb "magenta" lw 2
    files=system('ls -1B *.dat')
    plot for [i=1:words(files)] word(files, i) u 1:2 ls i title word(files, i)
eor
rm *.dat
for file in ${files[*]}
do
    cat "$file.csv" | awk -F ";" '{print $4 " " $14}' | awk '{gsub(/,/,".")}1'  > "$file.dat"
done
gnuplot << eor
    set terminal pngcairo size 1200, 600
    set output '4.2.png'
    set style data linespoints
    set xlabel "BufferSize"
    set ylabel "ReadBandwidth(Mb/s)"
    set format x "%.0f"
    set format y "%g"
    set logscale y
    set ytics 2
    set style line 1 lt 2 pt 7 lc rgb "red" lw 2
    set style line 2 lt 2 pt 7 lc rgb "blue" lw 2
    set style line 3 lt 2 pt 7 lc rgb "green" lw 2
    set style line 4 lt 2 pt 7 lc rgb "magenta" lw 2
    files=system('ls -1B *.dat')
    plot for [i=1:words(files)] word(files, i) u 1:2 ls i title word(files, i)
eor