set terminal pngcairo size 600,600 enhanced font "Arial,12"
set output "comparacion_trayectorias.png"
set size square
set size ratio -1
set grid
set title "Comparación RK4 vs Leap‑Frog"
set xlabel "x [AU]"
set ylabel "y [AU]"

plot \
  "posiciones.txt"      using ($2/1.496e11):($3/1.496e11) \
      with lines lw 2 title "RK4", \
  "posiciones_LF.txt"   using ($2/1.496e11):($3/1.496e11) \
      with lines lw 2 dt 2 title "Leap‑Frog"
