#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>
#include <cpu/cpu_io.h>
#include <task/testing_set.h>
#include <bin_packing/first_fit.h>
#include <utilities/prints.h>

int main(int argc, char *argv[]) {
	FILE *in;
	cpu *c;
	taskset *ts;
	if (argc < 3) {
		fprintf(stderr, "Usage: %s <cpu> <taskset>\n", argv[0]);
		return -1;
	}

	if ((in = fopen(argv[1], "r")) == NULL) {
		perror("FOpen");
		return -2;
	}
	
	if ((c = load_cpu(in)) == NULL) {
		fprintf(stderr, "Error loading cpu!\n");
		return -3;
	}
	
	print_cpu(c, stdout);
	
	if ((in = fopen(argv[2], "r")) == NULL) {
		perror("FOpen");
		return -2;
	}
	
	if ((ts = load_taskset(in)) == NULL) {
		fprintf(stderr, "Error loading taskset!\n");
		return -3;
	}
	
	printf("\n--------------------------------------------------------------------");
	printf("\n------------------------ MCPU ANALYSIS EDF -------------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_cpu(c, stdout);
	print_taskset(ts, stdout);

	if(first_fit_allocation(ts, c))
		printf("\nThe task set is schedulable under EDF with the specified periodic server.\n");
	else
		printf("\nThe task set is NOT schedulable under EDF with the specified periodic server.\n");

	printf("\n--------------------------------------------------------------------");
	printf("\n---------------------- END MCPU ANALYSIS EDF -----------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
