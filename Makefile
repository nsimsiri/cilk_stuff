CC=clang++
CFLAGS=-fcilkplus

all: qs

qs: qs.cpp
	$(CC) $(CFLAGS) -w qs.cpp -o qs

test: test.c
	$(CC) $(CFLAGS) test.c -o test

clean:
	rm -rf qs
	rm -rf test