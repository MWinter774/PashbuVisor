#!/bin/sh

BOOTSECTOR_FILE=out/PashbuVisor.bin

make clean
make all
qemu-system-x86_64 $BOOTSECTOR_FILE
