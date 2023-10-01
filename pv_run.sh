#!/bin/sh

BOOTSECTOR_FILE=out/bootsector.bin

make clean
make all
qemu-system-x86_64 $BOOTSECTOR_FILE