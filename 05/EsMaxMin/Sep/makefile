numMaxMin.out: top.o max.o min.o
	cc top.o max.o min.o -o numMaxMin.out
max.o: max.c max.h
	cc -c max.c
min.o: min.c min.h
	cc -c min.c
top.o: top.c max.h min.h
	cc -c top.c
clean:
	rm -r *.o
	rm -r numMaxMin.out