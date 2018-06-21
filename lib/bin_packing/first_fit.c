#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <cpu/structs/core.h>
#include <cpu/structs/cpu.h>
#include <mcpu_analysis/mcpu_analysis.h>

unsigned int first_fit_allocation(taskset *ts, cpu* c) {
	unsigned int i, j;
	for (i = 0; i < ts->size; i++) {
		j = 0;
		while(!schedulable(ts, i, c, j) && (j < c->n_cores)) 
			j++;
	
		if (j == c->n_cores) 
			return 0;
		
		allocate_cpu(ts, i, c, j);
	}
	
	return 1;
}
