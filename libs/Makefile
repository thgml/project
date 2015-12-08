.PHONY: all clean

libfuncs.a : utf8.o gotoxy.o
	ar rv libfuncs.a utf8.o gotoxy.o
utf8.o : utf8.c utf8.o
	gcc -c -g -I ~/jinsook/homework/include utf8.c -o utf8.o
gotoxy.o : gotoxy.c gotoxy.o
	gcc -c -g -I ~/jinsook/homework/include gotoxy.c -o gotoxy.o
clean:
	rm -f utf8.o gotoxy.o
