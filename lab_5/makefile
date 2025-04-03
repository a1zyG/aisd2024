prog: main.o func.o prog2
	gcc -o prog func.o main.o
	make clean
main.o:
	gcc -c main.c -g
func.o:
	gcc -c func.c -g

libtable.a: func.o
	ar r libtable.a func.o

prog2: main.o libtable.a
	gcc -o prog2 main.o -l  table -L.

clean:
	rm *.o
