#!/bin/bash

path=$(dirname $0)
output=$1

#convert to png
for pic in $(ls $path/*.svg)
do
  echo "converting $pic"
  inkscape --without-gui --export-png=$output/$(basename $pic .svg ).png --export-dpi=72 --export-background-opacity=0 --export-width=16 --export-height=16 $pic >/dev/null
done

