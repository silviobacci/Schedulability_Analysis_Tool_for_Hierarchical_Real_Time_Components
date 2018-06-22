#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <cpu/structs/core.h>
#include <cpu/structs/cpu.h>
#include <mcpu_analysis/mcpu_analysis.h>
#include <bin_packing/best_fit.h>
#include <utilities/utilities.h>
#include <utilities/prints.h>

unsigned int best_fit_allocation(taskset *ts, cpu* c, FILE * f) {
	unsigned int i, j;
	
	fprintf(f, "Let's try to assign the tasks to the different cores according to the best fit heuristic algorithm:\n");
	for (i = 0; i < ts->size; i++) {
		//print_cpu(c, stdout);
		sort_by_increasing_empty_space(c);
		fprintf(f, "Task %d :\n", ts->tasks[i].id);
		j = 0;
		fprintf(f, "\tCore %d : ", c->cores[j].id);
		while(!schedulable(ts, i, c, j) && (j < c->n_cores)) {
			j++;
			fprintf(f, "UNSCHEDULABLE\n");
			fprintf(f, "\tCore %d : ", c->cores[j].id);
		}

		if (j == c->n_cores) {
			return 0;
		}
		
		fprintf(f, "SCHEDULABLE\n");
		allocate_cpu(ts, i, c, j);
	}

	fprintf(f, "\n");
	
	return 1;
}
