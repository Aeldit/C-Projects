CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Wvla -Werror -pedantic
SANITIZE=-fsanitize=address -g


all: src/hashtable.o

# Only for tests
check: src/hashtable 
	# Only for tests
	./src/hashtable

# Only for tests
src/hashtable: CFLAGS+=$(SANITIZE)
src/hashtable: src/main.o src/hashtable.o
	$(CC) $(SANITIZE) -o $@ $^

clean:
	cd src/ && rm -f *.o hashtable

