#!/bin/bash

i=1
n=$1
while (($i <= $n))
do
	echo "----------------------"
	echo "	$i	"
	echo "----------------------"
	echo "fork"
	grep -c "$i has taken a fork" result.txt
	echo "eating"
	grep -c "$i is eating" result.txt
	echo "sleeping"
	grep -c "$i is sleeping" result.txt
	echo "thinking"
	grep -c "$i is thinking" result.txt
	echo "sleeping"
	grep -c "$i is sleeping" result.txt
	echo "died"
	grep -c "$i died" result.txt
	echo -e "\n\n"
	((i+=1))
done