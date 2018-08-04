program: main.o result_list.o name_list.o
	gcc -o program main.o result_list.o name_list.o -lm -Wall -std=c99 -pedantic
main.o: main.c
	gcc -c main.c -Wall -std=c99 -pedantic
result_list.o: result_list.c result_list.h name_list.h
	gcc -c result_list.c -Wall -std=c99 -pedantic
name_list.o: name_list.c name_list.h
	gcc -c name_list.c -Wall -std=c99 -pedantic
