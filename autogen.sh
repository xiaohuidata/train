#!/bin/sh

(
	cd ./protos || exit
	echo "run:$(pwd)"
	make
)
echo "run end $(pwd)"

aclocal && \
        autoheader && \
        autoconf && \
        automake --add-missing --force-missing
