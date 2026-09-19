#!/bin/sh
gcc hello.c -o hello_bin
./hello_bin
read -p "Press Enter to delete binary and exit..." dummy
rm -f hello_bin
