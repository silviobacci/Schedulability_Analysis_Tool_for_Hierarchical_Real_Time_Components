#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>
#include <utilities/utilities.h>
#include <utilities/prints.h>
#include <schedulability/h_analysis.h>

int main(int argc, char *argv[]) {
	FILE *in;
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
	
	printf("\n--------------------------------------------------------------------");
	printf("\n----------------- FIND PERIODIC SERVER ANALYSIS --------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_taskset(ts, stdout);
	print_find_periodic_server(stdout);
	ps = find_periodic_server(ts, algorithm);
	print_periodic_server(ps, stdout);

	if(algorithm == EDF) 
		print_h_analysis_edf(ts, ps, stdout); 
	else 
		print_h_analysis_fp(ts, ps, stdout);

	printf("\n--------------------------------------------------------------------");
	printf("\n--------------- END FIND PERIODIC SERVER ANALYSIS ------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
