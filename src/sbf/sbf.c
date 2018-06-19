#include <stdlib.h>
#include <stdio.h>

#include "sbf/sbf.h"

int main(int argc, char *argv[]) {
	unsigned int Qs, Ts, t;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <Q> <T>\n", argv[0]);
		return -1;
	}

	Qs = atoi(argv[1]);
	Ts = atoi(argv[2]);

	for (t = 0; t < 100; t++)
		printf("sbf(%u) = %u\n", t, sbf(Qs, Ts, t));

	return 0;
}
