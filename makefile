image:	image.o scanner.o ppm.o 
	gcc image.o scanner.o ppm.o -o image
image.o:	image.c image.h
	gcc -Wall -g -c image.c
scanner.o:	scanner.c scanner.h
	gcc -Wall -g -c scanner.c
ppm.o:	ppm.c scanner.h
	gcc -Wall -g -c ppm.c
clean:
	rm image.o scanner.o ppm.o image
