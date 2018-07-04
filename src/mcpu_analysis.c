//------------------------------------------------------------------------------
// MCPU ANALYSIS: Contains the testing code to perform the mcpu sched. analysis.
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "task/types.h"
#include "task/task_io.h"
#include "task/sorting.h"
#include "task/utilities.h"
#include "task/s_algorithm.h"
#include "vm/types.h"
#include "vm/vm_io.h"
#include "vm/sorting.h"
#include "vm/a_algorithm.h"
#include "schedulability/h_analysis.h"
#include "schedulability/mcpu_analysis.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MAIN: entry poiny
//------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	FILE *in, *out = stdout;	
	a_algorithm allocation;
	s_algorithm algorithm;
	int ps_present;
	unsigned int i;
	taskset *ts;
	vm *v;
	
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
	
	if ((in = fopen(argv[2], "r")) == NULL) {
		perror("FOpen");
		return -2;
	}
	
	if ((ts = load_taskset(in)) == NULL) {
		fprintf(stderr, "Error loading taskset!\n");
		return -3;
	}
	
	algorithm = atoi(argv[3]);
	
	if (algorithm < FP || algorithm > EDF) {
		fprintf(stderr, "Error loading scheduling algorithm!\n");
			return -3;
	}
	
	allocation = atoi(argv[4]);
	
	if (allocation < BF || allocation > FFD) {
		fprintf(stderr, "Error loading allocation algorithm!\n");
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
	fprintf(out, "\n-------------------- M-CPU SCHEDULING ANALYSIS ---------------------");
	fprintf(out, "\n--------------------------------------------------------------------\n\n");
	
	print_a_algorithm(allocation, out);
	print_s_algorithm(algorithm, out);
	print_vm(v, out);
	print_taskset(ts, out);
	
	if(mcpu_analysis(ts, v, algorithm, allocation)) {
		fprintf(out, "\nThe taskset is schedulable under multi-CPU partitioned scheduling with the specified cpus, using %s as allocation algorithm and using %s as scheduling algorithm.\n", a_algorithm_to_string(allocation), s_algorithm_to_string(algorithm));
		print_vm_load(v, out);
		
		if(!v->ps_set) {
			sort_cpus_by_id(v);
			for(i = 0; i < v->n_cpus; i++)
				if(v->cpus[i].u > 0) {
					fprintf(out, "Cpu %d : finding a periodic server for the taskset. ", v->cpus[i].id);
					if((v->cpus[i].ps = find_periodic_server(v->cpus[i].ts, algorithm)) != NULL)
						print_periodic_server(v->cpus[i].ps, out);
					else
						fprintf(out, "Sorry, it is impossible to find the desired periodic server. ");
				}
		}
	}
	else
		fprintf(out, "\nThe taskset is NOT schedulable under multi-CPU partitioned scheduling with the specified cpus, using %s as allocation algorithm and using %s as scheduling algorithm.\n", a_algorithm_to_string(allocation), s_algorithm_to_string(algorithm));
		
	fprintf(out, "\n--------------------------------------------------------------------");
	fprintf(out, "\n------------------ END M-CPU SCHEDULING ANALYSIS -------------------");
	fprintf(out, "\n--------------------------------------------------------------------\n\n");

	return 0;
}
