CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Wvla -Werror -pedantic
SANITIZE=-fsanitize=address -g

# Only for tests
all: tinyprintf
	# Only for tests
	./src/tinyprintf
#all: tinyprintf.o

# Only for tests
tinyprintf: src/main.o src/tinyprintf.o
	$(CC) $(CFLAGS) $(SANITIZE) -o src/tinyprintf src/main.o src/tinyprintf.o

# Only for tests
main.o: src/main.c
	$(CC) $(CFLAGS) $(SANITIZE) -O -c src/main.c

tinyprintf.o:
	# Only for tests
	cd src/ && $(CC) $(CFLAGS) $(SANITIZE) -O -c tinyprintf.c
	#cd src/ && $(CC) $(CFLAGS) -O -c tinyprintf.c

clean:
	# Only for tests
	rm src/*.o && rm src/tinyprintf
	#rm src/tinyprintf.o
