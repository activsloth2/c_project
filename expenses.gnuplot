set terminal png size 800,600
set output 'expenses.png'
set title 'Expenses by Category'
set style data histograms
set style fill solid
set boxwidth 0.5
set ylabel 'Amount'
set xlabel 'Category'
plot 'expenses.txt' using 2:xtic(1) title '' with histogram
