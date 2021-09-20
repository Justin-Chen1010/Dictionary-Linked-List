
dict: Ass1.o func.o parse.o
	gcc -o dict Ass1.o func.o parse.o
	
Ass1.o: Ass1.c func.h
	gcc -c -Wall Ass1.c
	
func.o: func.c func.h
	gcc -c -Wall func.c

parse.o: parse.c func.h
	gcc -c -Wall parse.c