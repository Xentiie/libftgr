#!/bin/bash

WIDTH=500
HEIGHT=500

times=

count=3
for i in $(seq $count); do
    i=$(($i+2))
    i=$((2**$i))
    echo $i
    gcc xcreateimage_bitmap_pad.c -lX11 -DPADN=$i -DWIDTH=$WIDTH -DHEIGHT=$HEIGHT
    times+=$(\time ./a.out 2>&1 | grep elapsed | awk '{print $3}' | sed -e "s/elapsed//")
    times+=" "
done

echo $times