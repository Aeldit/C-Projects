CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Wvla -Werror -pedantic
#SANITIZE=-fsanitize=address -g

# Only for tests
#all: rle
	# Only for tests
	#./src/rle
all: rle.o

# Only for tests
#rle: src/main.o src/rle.o
	#$(CC) $(CFLAGS) $(SANITIZE) -o src/rle src/main.o src/rle.o

# Only for tests
#main.o: src/main.c
	#$(CC) $(CFLAGS) $(SANITIZE) -O -c src/main.c

rle.o:
	cd src/ && $(CC) $(CFLAGS) -O -c rle.c

clean:
	cd src/ && rm -f *~ *.o *a *.so *.swp *.class *.log *.core
	cd src/ && find . -maxdepth 1 -type f -executable -exec rm {} +
