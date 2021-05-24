#!/bin/sh

while true; do
	clear
	tail $1
	read -s -t 0.01 input
	echo $input
	echo "$input" >> $1
done
