rm *.dat
files[0]=opt0
files[1]=opt1
for file in ${files[*]}
do
    cat "$file.csv" | awk -F ";" '{print $1 " " $2}' > "$file.dat"
done
gnuplot << eor
    set terminal pngcairo size 1200, 600
    set output 'graph.png'
    set style data linespoints
    set xlabel "Size"
    set ylabel "Time"
    set format x "%g"
    set style line 1 lt 2 pt 7 lc rgb "red" lw 2
    set style line 2 lt 2 pt 7 lc rgb "blue" lw 2
    files=system('ls -1B *.dat')
    plot for [i=1:words(files)] word(files, i) u (column(1)/1024/1024):2 ls i title word(files, i)
eor
rm *.dat