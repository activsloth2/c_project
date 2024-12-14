set terminal png size 800,600
set output 'data.png'
set title 'Income, Expenditure, and EMI'
set style data histograms
set style fill solid
set boxwidth 0.5
set ylabel 'Amount'
set xlabel 'Category'
plot 'data.txt' using 2:xtic(1) title '' with histogram
