.PHONY: all clean

all: pman

pman: main.c
	gcc -Wall main.c -o pman -lreadline

clean:
	-rm -rf pman *.o
