#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc != 2 || atoi(argv[1]) == 0) { // Error: num args
		printf("Usage: inf <interval>\n");
	} else {
		int interval = atoi(argv[1]);
		while (1) { // inf loop in useconds
			usleep(interval);
		}
	}
	return 0;
}