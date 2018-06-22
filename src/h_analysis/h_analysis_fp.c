#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>
#include <cpu/cpu_io.h>
#include <task/testing_set.h>
#include <utilities/prints.h>
#include <h_analysis/fp.h>

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
	printf("\n------------------------- H ANALYSIS RM ----------------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_taskset(ts, stdout);
	print_periodic_server(ps, stdout);
	print_h_analysis_fp(ts, ps, stdout);

	if(h_analysis_fp(ts, ps))
		printf("The task set is schedulable under RM with the specified periodic server.\n");
	else {
		printf("The task set is NOT schedulable under RM with the specified periodic server.\n");
		printf("Let's try to find a periodic server that can schedule the entire taskset. ");
		ps = find_periodic_server_rm(ts);
		print_periodic_server(ps, stdout);
		print_h_analysis_fp(ts, ps, stdout);
	}

	printf("\n--------------------------------------------------------------------");
	printf("\n----------------------- END H ANALYSIS RM --------------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
