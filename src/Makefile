all:
	gcc -O4 -ansi -Wall -c -o life.o life.c
	gcc -O4 -ansi -Wall -c -o genetic.o genetic.c
	gcc -O4 -ansi -Wall -c -o dnalife.o dnalife.c
	gcc -O4 -ansi -Wall -o dnalife dnalife.o genetic.o life.o
debug:
	gcc -O4 -ansi -g -Wall -c -o life.o life.c
	gcc -O4 -ansi -g -Wall -c -o genetic.o genetic.c
	gcc -O4 -ansi -g -Wall -c -o dnalife.o dnalife.c
	gcc -O4 -ansi -g -Wall -o dnalife dnalife.o genetic.o life.o

clean:
	rm *.o


