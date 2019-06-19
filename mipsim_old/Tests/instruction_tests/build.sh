#!/bin/bash

mips-mti-elf-as -o $1.o -a=$1.lst $1.s
mips-mti-elf-ld -o $1.elf $1.o
mips-mti-elf-objcopy --output-target ihex $1.elf $1.hex
