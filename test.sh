#!/bin/bash

for i in $(seq 1 8); do
	output=$(./a.out $i)
	if [ $? -ne 0 ]; then
		echo "Error at: $i (a.out)"
		echo $?
		echo $output
		break
	fi
	output=$(python3 gzstat.py --print-block-codes --decode-blocks < tests_gzip/gzip.gz)
	if [ $? -ne 0 ]; then
		echo "Error at: $i (gzstat)"
		echo $output
		break
	fi

	rm -f ./tests_gzip/gzip
	output=$(gzip -d tests_gzip/gzip.gz)
	if [ $? -ne 0 ]; then
		echo "Error at: $i (gzip)"
		echo $output
		break
	fi

	output=$(diff tests_gzip/gzip tests_gzip/test_gzip.txt)
	if [ -n "$output" ]; then
		echo "Error at: $i (diff)"
		echo $output
		break
	fi

done

