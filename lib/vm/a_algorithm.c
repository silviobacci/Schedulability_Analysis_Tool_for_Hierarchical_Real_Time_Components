//------------------------------------------------------------------------------
// A ALGORITHM:	Contains functions to manage allocation algorithms.
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "vm/a_algorithm.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT A ALGORITHM: prints info about the allocation algorithm
//------------------------------------------------------------------------------

void print_a_algorithm(a_algorithm a, FILE *f) {
	fprintf(f, "The taskset schedulability will be checked using %s as allocation algorithm.\n\n", a_algorithm_to_string(a));
}

//------------------------------------------------------------------------------
// A ALGORITHM TO STRING: converts enum integer to string
//------------------------------------------------------------------------------

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
