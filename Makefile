all: main
main:
	gcc -Wall -o main src/*.c -lm
clean:
	rm main
run:
	./main
debug:
	rm main
	gcc -Wall -o main src/*.c -lm -g
	gdb main