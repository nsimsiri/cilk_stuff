CC=clang++
CFLAGS=-fcilkplus

all: qs

qs: qs.cpp
	$(CC) $(CFLAGS) -w qs.cpp -o qs

test: test.c
	clang $(CFLAGS) test.c -o test

utils: utils.cpp
	$(CC) $(CFLAGS) -std=c++11 utils.cpp -o utils

clean:
	rm -rf qs
	rm -rf test
	rm -rf utils
