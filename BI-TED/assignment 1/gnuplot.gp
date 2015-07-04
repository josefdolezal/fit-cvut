# author: josef dolezal
# git: https://github.com/josefdolezal
reset
set datafile separator ";"
set xlabel "day of year and hour of day of first submission"
set ylabel "success rate"
set grid
set xdata time
set timefmt "%Y-%m-%d %H"
set palette rgbformulae 3,0,3
set style fill solid border
set yrange [0:1]
set xtics format "%j\n%H"
set cblabel "no of submissions"
plot "data.txt" using 1:2:(sqrt($3 * (2**22))):3 with circles palette notitle
