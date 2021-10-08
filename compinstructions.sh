gcc -c `cob-config --cflags` main.c
cobc -c -static say.cob
cobc -x -o hello main.o say.o
./hello
