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
#include <vm/sorting.h>
#include <vm/utilities.h>
#include <schedulability/h_analysis.h>
#include <schedulability/mcpu_analysis.h>

unsigned int (* allocation_algorithm) (taskset *ts, vm* v, s_algorithm a, FILE * f);

int main(int argc, char *argv[]) {
	FILE *in;
	vm *v;
	taskset *ts;
	a_algorithm allocation;
	s_algorithm algorithm;
	unsigned int is_schedulable, i;
	int ps_present;
	
	if (argc < 5) {
		fprintf(stderr, "Usage: %s <cpu> <taskset> <algorithm> <allocation>\n", argv[0]);
		return -1;
	}

	if ((in = fopen(argv[1], "r")) == NULL) {
		perror("FOpen");
		return -2;
	}
	
	if((ps_present = is_ps_in_file(in, argv[1])) < 0) {
		perror("FOpen");
		return -2;
	}
	
	if ((v = load_vm(in, ps_present)) == NULL) {
		fprintf(stderr, "Error loading cpu!\n");
		return -3;
	}
	
	printf("v->ps_set = %d\n", v->ps_set);
	
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
	
	is_schedulable = mcpu_analysis(ts, v, algorithm, allocation, stdout);
	print_mcpu_schedulability(is_schedulable, allocation, stdout);
	
	if(is_schedulable) {
		print_vm_load(v, stdout);
		if(!v->ps_set) {
			sort_cpus_by_id(v);
			for(i = 0; i < v->n_cpus; i++) {
				if(v->cpus[i].u > 0) {
					v->cpus[i].ps = find_periodic_server(v->cpus[i].ts, algorithm);
					print_find_periodic_server_vm(v->cpus[i].id, stdout);	
					print_periodic_server(v->cpus[i].ps, stdout);
				}
			}
		}
	}
	
	printf("\n--------------------------------------------------------------------");
	printf("\n------------------ END M-CPU SCHEDULING ANALYSIS -------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
