numMax.out: top.o max.o 
	cc top.o max.o -o numMax.out
max.o: max.c max.h
	cc -c max.c
top.o: top.c max.h
	cc -c top.c