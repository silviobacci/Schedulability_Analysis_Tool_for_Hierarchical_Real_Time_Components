//------------------------------------------------------------------------------
// H ANALYSIS: Contain the testing code to perform hierarchical sched. analysis.
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "task/types.h"
#include "task/task_io.h"
#include "task/sorting.h"
#include "task/utilities.h"
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
	unsigned int is_schedulable;
	
	if (argc < 5) {
		fprintf(stderr, "Usage: %s <taskset> <Qs> <Ts> <algorithm>\n", argv[0]);
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
	
	ps = load_periodic_server(atoi(argv[2]), atoi(argv[3]));
	
	algorithm = atoi(argv[4]);
	
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
	fprintf(out, "\n---------------- HIERARCHICAL SCHEDULING ANALYSIS ------------------");
	fprintf(out, "\n--------------------------------------------------------------------\n\n");
	
	print_taskset(ts, out);
	print_periodic_server(ps, out);
	
	is_schedulable = (algorithm == EDF) ? h_analysis_edf(ts, ps) : h_analysis_fp(ts, ps);
	
	if(is_schedulable)
		fprintf(out, "\nThe taskset is schedulable under %s with the specified periodic server (Qs = %u, Ts = %u).\n", s_algorithm_to_string(algorithm), ps->Qs, ps->Ts);
	else
		fprintf(out, "\nThe taskset is NOT schedulable under %s with the specified periodic server (Qs = %u, Ts = %u).\n", s_algorithm_to_string(algorithm), ps->Qs, ps->Ts);

	
	if(!is_schedulable) {
		fprintf(out, "Let's try to find a periodic server that can schedule the entire taskset. ");
		
		if((ps = find_periodic_server(ts, algorithm)) != NULL)
			print_periodic_server(ps, out);
		else
			fprintf(out, "Sorry, it is impossible to find the desired periodic server. ");
	}

	fprintf(out, "\n--------------------------------------------------------------------");
	fprintf(out, "\n-------------- END HIERARCHICAL SCHEDULING ANALYSIS ----------------");
	fprintf(out, "\n--------------------------------------------------------------------\n\n");

	return 0;
}
