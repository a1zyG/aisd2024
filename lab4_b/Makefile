all: libtree
	cc -g -c main.c -o main.o
	cc -g -c dialog.c -o dialog.o
	cc -g -c input.c -o input.o
	cc -g main.o dialog.o input.o -L. -ltree -o bin

time: libtree
	cc -g timing.c -L. -ltree -o bin

test: libtree
	cc -g -c test_tree.c -o test_tree.o
	cc -g test_tree.o -L. -ltree -o bin
	./bin

libtree:
	cc -g -c tree.c -o tree.o
	cc -g -c list.c -o list.o
	ar rcs libtree.a tree.o list.o

clean:
	rm -rf bin
	rm -rf *.o
	rm -rf *.a