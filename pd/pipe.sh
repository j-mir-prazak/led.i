#!/bin/bash
BASEDIR=$(dirname "$0")
cd $BASEDIR

if [ ! -z $5 ]
then
	tty="$5"
	if [ ! -z $1 ]
	then
	command="$1"
	(echo "$command:$2:$3:$4" | cat - > "$tty") &
	proc=$!
	sleep 0.001
	kill $proc > /dev/null 2>&1
	#echo "$(($(date +%s%N)/1000000))" > "$tty"
	#echo "$(($(date +%s%N)/1000000))"
	echo "$1 $2 $3 $4 $5"
	fi
fi
