all:geom.c

geom.c:
	gcc -Wall -Werror -o 1 geom.c
run:
	./1
clean:
	rm 1