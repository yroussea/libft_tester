#!/bin/sh

arg=""
for var in "$@"
do
	if [ "$var" = 'type' ];
	then
		arg="$arg""-D TYPE "
	fi
	if [ "$var" = 'strs' ];
	then
		arg="$arg""-D STRS "
	fi
	if [ "$var" = 'mems' ];
	then
		arg="$arg""-D MEMS "
	fi
done
if [ "$arg" = '' ];
then
	arg="-D ALL"
fi

if [ -d "libft" ];
then
	echo "using ""$PWD""/libft"
	lib="../libft"
elif [ -d "../libft" ];
then
	echo "using ""$PWD""/../libft"
	lib="../../libft"
elif [ -d "../../libft" ];
then
	echo "using ""$PWD""/../../libft"
	lib="../../../libft"
else
	echo "libft directory not found, place it at ../.. .. or . (and name it libft)"
	exit 1
fi

echo "!!leaks aren't check; A tester should not dictate the defense"

make LIBFT_DIR="$lib" ALL_FLAG="$arg" -s -C srcs cc && ./srcs/libft_testeur
