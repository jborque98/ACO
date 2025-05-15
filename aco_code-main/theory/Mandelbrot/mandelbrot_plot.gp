# Output to PNG image
set terminal pngcairo size 1920, 1080 enhanced font 'Verdana,12'
set output 'mandelbrot.png'

# Appearance
set title "Mandelbrot Set" font "Verdana,16"
set xlabel "Re(C)"
set ylabel "Im(C)"
set size ratio -1              # Keep aspect ratio correct
unset key                      # No legend needed
set pointsize 0.3              # Smaller, denser points

# Optional: dark mode style
set border lc rgb "white"
set tics textcolor rgb "white"
set xlabel textcolor rgb "white"
set ylabel textcolor rgb "white"
set title textcolor rgb "white"
set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "black" behind

# Plot the points
plot 'mandelbrot.txt' using 1:2 with points pt 7 lc rgb "cyan"
