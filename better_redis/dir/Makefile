flags=-Wall -O2 -std=c2x
ldflags=

all: clean main tree

tree: tree.o
	cc ${flags} $^ -o $@ ${ldflags}

tree.o: tree.c
	cc ${flags} -c $^

main: main.o
	cc ${flags} $^ -o $@ ${ldflags}

main.o: main.c
	cc ${flags} -c $^

clean:
	rm -rf *.o main
	rm -rf *.o tree
