//------------------------------------------------------------------------------
// SBF: Contains the testing code to compute the sbf.
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "task/types.h"
#include "task/task_io.h"
#include "schedulability/sbf.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define 	START_TIME		0		// start time to compute sbf
#define 	END_TIME		100		// end time to compute sbf

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MAIN: entry poiny
//------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	unsigned int t;
	FILE * out = stdout;
	periodic_server * ps;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <Qs> <Ts>\n", argv[0]);
		return -1;
	}
	
	ps = load_periodic_server(atoi(argv[1]), atoi(argv[2]));

	fprintf(out, "\n--------------------------------------------------------------------");
	fprintf(out, "\n------------------------------- SBF --------------------------------");
	fprintf(out, "\n--------------------------------------------------------------------\n\n");

	print_periodic_server(ps, out);
	
	fprintf(out, "The sbf computed from time %u to time %u is: \n", START_TIME, END_TIME);

	for (t = START_TIME; t < END_TIME; t++)
		fprintf(out, "\t sbf(%u) = %u\n", t, sbf(ps, t));

	fprintf(out, "\n--------------------------------------------------------------------");
	fprintf(out, "\n----------------------------- END SBF ------------------------------");
	fprintf(out, "\n--------------------------------------------------------------------\n\n");

	return 0;
}
