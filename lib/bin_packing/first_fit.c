#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <cpu/structs/core.h>
#include <cpu/structs/cpu.h>
#include <mcpu_analysis/mcpu_analysis.h>
#include <bin_packing/first_fit.h>
#include <utilities/utilities.h>

unsigned int first_fit_allocation(taskset *ts, cpu* c, FILE * f) {
	unsigned int i, j;
	
	fprintf(f, "Let's try to assign the tasks to the different cores according to the first fit heuristic algorithm:\n");
	for (i = 0; i < ts->size; i++) {
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

unsigned int first_fit_decreasing_allocation(taskset *ts, cpu* c, FILE * f) {
	unsigned int i, j;
	sort_by_decreasing_utilization_factor(ts);
	
	fprintf(f, "Let's try to assign the tasks to the different cores according to the decreasing first fit heuristic algorithm:\n");
	for (i = 0; i < ts->size; i++) {
		fprintf(f, "Task %d :\n", i);
		j = 0;
		fprintf(f, "\tCore %d : ", j);
		while(!schedulable(ts, i, c, j) && (j < c->n_cores)) {
			j++;
			fprintf(f, "\tCore %d : ", j);
		}

		if (j == c->n_cores) {
			fprintf(f, "UNSCHEDULABLE\n");
			return 0;
		}
		
		fprintf(f, "SCHEDULABLE\n");
		allocate_cpu(ts, i, c, j);
	}

	fprintf(f, "\n");
	
	return 1;
}
