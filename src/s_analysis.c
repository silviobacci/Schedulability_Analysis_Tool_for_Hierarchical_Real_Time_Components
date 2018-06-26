#include <stdlib.h>
#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <task/task_io.h>
#include <task/sorting.h>
#include <task/utilities.h>
#include <schedulability/s_analysis.h>

int main(int argc, char *argv[]) {
	FILE *in;
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

	printf("\n--------------------------------------------------------------------");
	printf("\n---------------------- SCHEUDLING ANLYSIS --------------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_s_algorithm(algorithm, stdout);
	print_taskset(ts, stdout);
	
	if(algorithm == EDF) {
		print_s_analysis_edf(ts, stdout);
		is_schedulable = s_analysis_edf(ts);
	}
	else {
		print_s_analysis_fp(ts, stdout);
		is_schedulable = s_analysis_fp(ts);
	}

	print_s_schedulability(is_schedulable, algorithm, stdout);

	printf("\n--------------------------------------------------------------------");
	printf("\n-------------------- END SCHEUDLING ANLYSIS ------------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
