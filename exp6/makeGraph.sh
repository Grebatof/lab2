#!/usr/bin/gnuplot
set termoption enhanced
set terminal png size 800,480 font "Arial, 16"
set output "Table.png"

set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1

set border lw 2
set grid
set key top left
set logscale y
set mytics 1
set format x "%6.0f"
set format y "%.3f"
set xlabel "Количество элементов в таблице, тыс."
set ylabel "Количество коллизий" rotate by 90
set xtics 6 font "Arial, 12"
set ytics font "Arial, 12"
set tmargin 2
set rmargin 4
set mxtics

plot "hashtab1Kol.dat" using 1:2 title "KR hash" with linespoints ls 1, \
"hashtab2Kol.dat" using 1:2 title "FNV" with linespoints ls 2
