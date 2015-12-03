.PHONY: all clean

libfuncs.a : utf.o gotoxy.o
	ar rv libfuncs.a utf.o gotoxy.o
func1.o : utf.c utf.o
	gcc -c -g -I ~/jinsook/homework/include utf.c -o utf.o
func2.o : gotoxy.c gotoxy.o
	gcc -c -g -I ~/jinsook/homework/include gotoxy.c -o gotoxy.o
clean:
	rm -f gotoxy.o gotoxy.o

