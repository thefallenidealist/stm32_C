#!/bin/sh

OS=`uname`

if [ "$OS" = "FreeBSD" ]; then
	echo "OS je FreeBSD"
	STTY="sudo stty -f"
	DEV=/dev/cuaU0
	DEV2=/dev/cuaU0.init
	$STTY $DEV2 -echo 38400
	cat /dev/cuaU0

elif [ "$OS" = "Linux" ]; then
	echo "OS je Linux"
	STTY="stty -F"
	DEV=/dev/ttyUSB0
	$STTY $DEV -echo
	$STTY $DEV 9600
else
	echo "neprepoznati OS"
fi

if [ -r $DEV ]; then
	echo "pronadjen serijski"
else
	echo "serijski nije ustekan";
fi

