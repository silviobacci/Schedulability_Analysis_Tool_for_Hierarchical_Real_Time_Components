//------------------------------------------------------------------------------
// S ANALYSIS: Contains the testing code to perform the sched. analysis.
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "task/types.h"
#include "task/task_io.h"
#include "task/sorting.h"
#include "task/utilities.h"
#include "task/s_algorithm.h"
#include "schedulability/s_analysis.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MAIN: entry poiny
//------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	FILE *in, *out = stdout;
	taskset *ts;
	s_algorithm algorithm;
	unsigned int is_schedulable;

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
	fprintf(out, "\n---------------------- SCHEUDLING ANLYSIS --------------------------");
	fprintf(out, "\n--------------------------------------------------------------------\n\n");
	
	print_s_algorithm(algorithm, out);
	print_taskset(ts, out);
	
	is_schedulable = (algorithm == EDF) ? processor_demand_analysis(ts) : workload_analysis(ts);
	
	if(is_schedulable)
		fprintf(out, "The taskset is schedulable under %s.\n", s_algorithm_to_string(algorithm));
	else
		fprintf(out, "The taskset is NOT schedulable under %s.\n", s_algorithm_to_string(algorithm));

	fprintf(out, "\n--------------------------------------------------------------------");
	fprintf(out, "\n-------------------- END SCHEUDLING ANLYSIS ------------------------");
	fprintf(out, "\n--------------------------------------------------------------------\n\n");

	return 0;
}
