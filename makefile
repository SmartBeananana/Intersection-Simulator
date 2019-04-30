CC          =	gcc

CFLAGS      =	-Wall -std=c99 -pedantic -g -lm

test: src/QueueImpl.c src/LinkedListImpl.c src/carImpl.c src/main.c
	$(CC) $(CFLAGS) src/QueueImpl.c src/LinkedListImpl.c src/carImpl.c src/main.c -Iinclude -o bin/testMe

testmain: src/test.c src/testQueue.c src/QueueImpl.c src/LinkedListImpl.c
	$(CC) $(CFLAGS) src/test.c src/testQueue.c src/QueueImpl.c src/LinkedListImpl.c -Iinclude -o bin/testMain

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*
