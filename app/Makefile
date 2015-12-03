.PHONY: all clean

main: main.c
	gcc -g -c -I ~/home/sohee/2015SW/include main.c -o main.o
	gcc -o main -L ~/home/sohee/2015SW/libs main.o -lfuncs
clean:
	rm -f main.o
