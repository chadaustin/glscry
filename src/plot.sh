#!/bin/sh

doplot() {
    cat <<EOF | gnuplot
set size 1,1
set terminal png
set output "$2"
plot "$1" using 0:1 title "Imm" with lines,\
     "$1" using 0:2 title "DL"  with lines,\
     "$1" using 0:3 title "VA"  with lines,\
     "$1" using 0:4 title "CVA" with lines,\
     "$1" using 0:5 title "VBO" with lines
EOF
}

doplot "zeroes.data"          "zeroes.png"
doplot "small_triangles.data" "small_triangles.png"
