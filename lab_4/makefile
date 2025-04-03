main.o:
	gcc -c main.c -g
func.o:
	gcc -c func.c -g

prog: main.o func.o
	gcc -o prog func.o main.o
libtable.a: func.o
	ar r libtable.a func.o

prog2: main.o libtable.a
	gcc -o prog2 main.o -l  table -L.

clean:
	rm *.o
