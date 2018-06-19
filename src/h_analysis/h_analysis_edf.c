#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>
#include <task/scheduling_points.h>
#include <utilities/prints.h>
#include <dbf/edf.h>
#include <tda/edf.h>
#include <h_analysis/edf.h>
#include <sbf/sbf.h>

int main(int argc, char *argv[]) {
	FILE *in;
	taskset *ts;
	periodic_server * ps;
	
	if (argc < 4) {
		fprintf(stderr, "Usage: %s <taskset> <Q> <T>\n", argv[0]);
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
	
	printf("\n--------------------------------------------------------------------");
	printf("\n------------------------- H ANALYSIS EDF ---------------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_taskset(ts, stdout);
	print_periodic_server(ps, stdout);
	printf_h_analysis_edf(ts, ps, stdout);

	if(h_analysis_edf(ts, ps))
		printf("\nThe task set is schedulable under EDF with the specified periodic server.\n");
	else
		printf("\nThe task set is NOT schedulable under EDF with the specified periodic server.\n");

	printf("\n--------------------------------------------------------------------");
	printf("\n----------------------- END H ANALYSIS EDF -------------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
