# Makefile for pman and inf

# Define phony targets
.PHONY: all clean install

# Default target
all: pman inf

# Compile rule for pman
pman: main.c
	gcc -Wall main.c bg.c pstat.c linked_list.c -o pman -lreadline

# Compile rule for inf
inf: inf.c
	gcc -Wall inf.c -o inf

# Install rule (uncomment, run make -> make install -> make clean to use globally)
# install: pman
# 	install -m 755 pman /usr/local/bin

# Clean rule
clean:
	-rm -rf pman inf *.o
