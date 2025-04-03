main.o: main.c
	gcc -c main.c

list.o: list.c
	gcc -c list.c

vec.o: vec.c
	gcc -c vec.c

PICvec.o: vec.c
	gcc -c -fPIC vec.c
  
PIClist.o: list.c
	gcc -c -fPIC list.c

libstackL.a: list.o
	ar r libstackL.a list.o

libstackV.a: vec.o
	ar r libstackV.a vec.o

libstackL.so: PIClist.o
	gcc -shared -o libstackL.so list.o

libstackV.so: PICvec.o
	gcc -shared -o libstackV.so vec.o

prog_static_list: main.o libstackL.a
	gcc -o prog_static_list main.o -L. -lstackL

prog_static_vec: main.o libstackV.a
	gcc -o prog_static_vec main.o -L. -lstackV

prog_dinam_list: main.o libstackL.so
	gcc -o prog_dinam_list main.o -L. -lstackL -Wl,-rpath,.

prog_dinam_vec: main.o libstackV.so
	gcc -o prog_dinam_vec main.o -L. -lstackV -Wl,-rpath,.
 
all: prog_static_list prog_static_vec prog_dinam_list prog_dinam_vec

clean:
	rm *.o
	rm *.a
	rm *.so
