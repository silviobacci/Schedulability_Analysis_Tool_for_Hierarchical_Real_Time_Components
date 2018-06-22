#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>
#include <vm/vm_io.h>
#include <utilities/prints.h>
#include <schedulability/bin_packing.h>

unsigned int (* allocation_algorithm) (taskset *ts, vm* v, FILE * f);

int main(int argc, char *argv[]) {
	FILE *in;
	vm *v;
	taskset *ts;
	a_algorithm algorithm;
	unsigned int is_schedulable;
	
	if (argc < 4) {
		fprintf(stderr, "Usage: %s <cpu> <taskset> <allocation>\n", argv[0]);
		return -1;
	}

	if ((in = fopen(argv[1], "r")) == NULL) {
		perror("FOpen");
		return -2;
	}
	
	if ((v = load_vm(in)) == NULL) {
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
	
	algorithm = atoi(argv[3]);
	
	if (algorithm < BF || algorithm > FFD) {
		fprintf(stderr, "Error loading allocation algorithm!\n");
			return -3;
	}

	switch(algorithm) {
		case BF:
			allocation_algorithm = best_fit_allocation;
			break;
		case FF:
			allocation_algorithm = first_fit_allocation;
			break;
		case NF:
			allocation_algorithm = next_fit_allocation;
			break;
		case WF:
			allocation_algorithm = worst_fit_allocation;
			break;
		case FFD:
			allocation_algorithm = first_fit_decreasing_allocation;
			break;
	}
	
	printf("\n--------------------------------------------------------------------");
	printf("\n-------------------- M-CPU SCHEDULING ANALYSIS ---------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_a_algorithm(algorithm, stdout);
	print_vm(v, stdout);
	print_taskset(ts, stdout);
	
	is_schedulable = allocation_algorithm(ts, v, stdout);
	
	print_mcpu_schedulability(is_schedulable, algorithm, stdout);

	if(is_schedulable)
		print_vm_load(v, stdout);

	printf("\n--------------------------------------------------------------------");
	printf("\n------------------ END M-CPU SCHEDULING ANALYSIS -------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
