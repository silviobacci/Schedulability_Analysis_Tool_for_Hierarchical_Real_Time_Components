//------------------------------------------------------------------------------
// FIND PS ANALYSIS: Contains the testing code for finding a periodic server.
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "task/types.h"
#include "task/task_io.h"
#include "task/sorting.h"
#include "task/s_algorithm.h"
#include "schedulability/h_analysis.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MAIN: entry poiny
//------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	FILE *in, *out = stdout;
	taskset *ts;
	periodic_server * ps;
	s_algorithm algorithm;
	
	if (argc < 3) {
		fprintf(stderr, "Usage: %s <taskset> <algorithm>\n", argv[0]);
		return -1;
	}

	if ((in = fopen(argv[1], "r")) == NULL) {
		perror("FOpen");
		return -2;
	}
	
	if ((ts = load_taskset(in)) == NULL) {
		fprintf(stderr, "Error loading taskset!\n");
		return -3;
	}
	
	algorithm = atoi(argv[2]);
	
	if (algorithm < FP || algorithm > EDF) {
		fprintf(stderr, "Error loading algorithm!\n");
			return -3;
	}
	
	switch(algorithm) {
		case RM:
			sort_by_increasing_periods(ts);
			break;
		case DM:
			sort_by_increasing_deadlines(ts);
			break;
		case FP:
		case EDF:
			break;
	}
	
	fprintf(out, "\n--------------------------------------------------------------------");
	fprintf(out, "\n----------------- FIND PERIODIC SERVER ANALYSIS --------------------");
	fprintf(out, "\n--------------------------------------------------------------------\n\n");
	
	print_s_algorithm(algorithm, out);
	print_taskset(ts, stdout);
	
	fprintf(out, "Let's try to find a periodic server that can schedule the entire taskset under %s. ",  s_algorithm_to_string(algorithm));
	
	if((ps = find_periodic_server(ts, algorithm)) != NULL)
		print_periodic_server(ps, out);
	else
		fprintf(out, "Sorry, it is impossible to find the desired periodic server. ");

	fprintf(out, "\n--------------------------------------------------------------------");
	fprintf(out, "\n--------------- END FIND PERIODIC SERVER ANALYSIS ------------------");
	fprintf(out, "\n--------------------------------------------------------------------\n\n");

	return 0;
}
