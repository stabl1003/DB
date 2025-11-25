flags=-Wall -O2 -std=c2x
ldflags=

all: clean main

main: main.o
	cc ${flags} $^ -o $@ ${ldflags}

main.o: main.c
	cc ${flags} -c $^

clean:
	rm -rf *.o main
