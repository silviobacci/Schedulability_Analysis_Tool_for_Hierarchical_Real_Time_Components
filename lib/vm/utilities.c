#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utilities/utilities.h>

#include <task/task_io.h>

void print_a_algorithm(a_algorithm a, FILE *f) {
	fprintf(f, "The taskset schedulability will be checked using %s as allocation algorithm.\n\n", a_algorithm_to_string(a));
}

char * a_algorithm_to_string(a_algorithm a) {
	char * ret = malloc(sizeof(char) * 25);
	switch(a) {
		case BF:
			ret = "BEST FIT";
			break;
		case FF:
			ret = "FIRST FIT";
			break;
		case NF:
			ret = "NEXT FIT";
			break;
		case WF:
			ret = "WORST FIT";
			break;
		case FFD:
			ret = "FIRST FIT DECREASING";
			break;
	}
	
	return ret;
}
