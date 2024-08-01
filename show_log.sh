#!/bin/sh

arg=""
for var in "$@"
do
	arg="$arg ""-e $var"
done

if [ "$#" = "0" ];
then
	cat srcs/log | grep -v ok | grep -v error
else
	cat srcs/log | grep error | grep $arg
fi


