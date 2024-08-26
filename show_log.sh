#!/bin/sh

arg=""
for var in "$@"
do
	arg="$arg ""-e $var"
done

if [ "$#" = "0" ];
then
	cat srcs/log | grep -av ok | grep -av error
else
	cat srcs/log | grep -a error | grep -a $arg
fi


