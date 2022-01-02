#!/bin/sh

alias build="mkdir ./out 2>/dev/null | make -f ./build/Makefile"
alias run="qemu-system-x86_64 out/output.bin"
alias build_and_run="build && run"
