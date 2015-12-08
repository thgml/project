.PHONY: all clean

main: main.c
	gcc -g -c -I ~/home/jin/realproject/include main.c -o main.o
	gcc -o main -L ~/home/jin/realproject/libs main.o -lfuncs
clean:
	rm -f main.o
