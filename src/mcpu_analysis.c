#include <stdlib.h>
#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <task/task_io.h>
#include <task/sorting.h>
#include <task/utilities.h>
#include <vm/structs/cpu.h>
#include <vm/structs/vm.h>
#include <vm/vm_io.h>
#include <vm/utilities.h>
#include <schedulability/mcpu_analysis.h>

unsigned int (* allocation_algorithm) (taskset *ts, vm* v, s_algorithm a, FILE * f);

int main(int argc, char *argv[]) {
	FILE *in;
	vm *v;
	taskset *ts;
	a_algorithm allocation;
	s_algorithm algorithm;
	unsigned int is_schedulable;
	
	if (argc < 5) {
		fprintf(stderr, "Usage: %s <cpu> <taskset> <algorithm> <allocation>\n", argv[0]);
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
	allocation = atoi(argv[4]);
	
	if (allocation < BF || allocation > FFD) {
		fprintf(stderr, "Error loading allocation algorithm!\n");
			return -3;
	}
	
	printf("\n--------------------------------------------------------------------");
	printf("\n-------------------- M-CPU SCHEDULING ANALYSIS ---------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_a_algorithm(allocation, stdout);
	print_vm(v, stdout);
	print_taskset(ts, stdout);
	
	print_mcpu_analysis(ts, v, algorithm, allocation, stdout);
	is_schedulable = mcpu_analysis(ts, v, algorithm, allocation);
	
	print_mcpu_schedulability(is_schedulable, allocation, stdout);

	if(is_schedulable)
		print_vm_load(v, stdout);

	printf("\n--------------------------------------------------------------------");
	printf("\n------------------ END M-CPU SCHEDULING ANALYSIS -------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
