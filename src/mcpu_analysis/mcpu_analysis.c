#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>
#include <cpu/cpu_io.h>
#include <task/testing_set.h>
#include <bin_packing/best_fit.h>
#include <bin_packing/first_fit.h>
#include <bin_packing/next_fit.h>
#include <bin_packing/worst_fit.h>
#include <utilities/prints.h>

unsigned int (* allocation_algorithm) (taskset *ts, cpu* c, FILE * f);

int main(int argc, char *argv[]) {
	FILE *in;
	cpu *c;
	taskset *ts;
	if (argc < 4) {
		fprintf(stderr, "Usage: %s <cpu> <taskset> <allocation>\n", argv[0]);
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
	
	if ((in = fopen(argv[2], "r")) == NULL) {
		perror("FOpen");
		return -2;
	}
	
	if ((ts = load_taskset(in)) == NULL) {
		fprintf(stderr, "Error loading taskset!\n");
		return -3;
	}

	switch(atoi(argv[3])) {
		case 0:
			allocation_algorithm = best_fit_allocation;
			break;
		case 1:
			allocation_algorithm = first_fit_allocation;
			break;
		case 2:
			allocation_algorithm = next_fit_allocation;
			break;
		case 3:
			allocation_algorithm = worst_fit_allocation;
			break;
		case 4:
			allocation_algorithm = first_fit_decreasing_allocation;
			break;
		default:
			fprintf(stderr, "Error loading allocation algorithm!\n");
			return -3;
	}
	
	printf("\n--------------------------------------------------------------------");
	printf("\n------------------------ MCPU ANALYSIS EDF -------------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_cpu(c, stdout);
	print_taskset(ts, stdout);

	if(allocation_algorithm(ts, c, stdout)) {
		printf("The task set is schedulable under multi-CPU partitioned scheduling with the specified cores.\n");
		print_cpu_load(c, stdout);
	}
	else
		printf("The task set is NOT schedulable under multi-CPU partitioned scheduling with the specified cores.\n");

	printf("\n--------------------------------------------------------------------");
	printf("\n---------------------- END MCPU ANALYSIS EDF -----------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
