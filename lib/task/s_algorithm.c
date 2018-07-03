//------------------------------------------------------------------------------
// S ALGORITHM:	Contains functions to manage scheduling algorithms.
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "task/s_algorithm.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT S ALGORITHM: prints info about the schduling algorithm
//------------------------------------------------------------------------------

void print_s_algorithm(s_algorithm a, FILE *f) {
	fprintf(f, "The taskset schedulability will be checked under %s.\n\n", s_algorithm_to_string(a));
}

//------------------------------------------------------------------------------
// S ALGORITHM TO STRING: converts the integer of the enum in a string
//------------------------------------------------------------------------------

char * s_algorithm_to_string(s_algorithm a) {
	char * ret = malloc(sizeof(char) * 5);
	switch(a) {
		case FP:
			ret = "FP";
			break;
		case RM:
			ret = "RM";
			break;
		case DM:
			ret = "DM";
			break;
		case EDF:
			ret = "EDF";
			break;
	}
	
	return ret;
}
