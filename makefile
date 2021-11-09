all: structrw.o main.o
	gcc -o structrw main.o structrw.o
main.o: main.c structrw.h
	gcc -c main.c
structrw.o: structrw.c structrw.h
	gcc -c structrw.c
run:
	./structrw
