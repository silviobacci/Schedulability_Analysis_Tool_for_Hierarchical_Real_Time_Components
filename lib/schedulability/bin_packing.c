#include <stdio.h>

#include <utilities/utilities.h>
#include <schedulability/mcpu_analysis.h>

#include <schedulability/bin_packing.h>

unsigned int best_fit_allocation(taskset *ts, vm* v, s_algorithm a, FILE * f) {
	unsigned int i, j;
	
	fprintf(f, "Let's try to assign the tasks to the different cpus according to the best fit heuristic algorithm:\n");
	for (i = 0; i < ts->size; i++) {
		sort_by_increasing_empty_space(v);
		fprintf(f, "Task %d :\n", ts->tasks[i].id);
		j = 0;
		fprintf(f, "\tCore %d : ", v->cpus[j].id);
		while(!schedulable(ts, i, v, j, a) && (j < v->n_cpus)) {
			j++;
			fprintf(f, "UNSCHEDULABLE\n");
			fprintf(f, "\tCore %d : ", v->cpus[j].id);
		}

		if (j == v->n_cpus) {
			return 0;
		}
		
		fprintf(f, "SCHEDULABLE\n");
		allocate_vm(ts, i, v, j);
	}

	fprintf(f, "\n");
	
	return 1;
}

unsigned int first_fit_allocation(taskset *ts, vm* v, s_algorithm a, FILE * f) {
	unsigned int i, j;
	
	fprintf(f, "Let's try to assign the tasks to the different cpus according to the first fit heuristic algorithm:\n");
	for (i = 0; i < ts->size; i++) {
		fprintf(f, "Task %d :\n", ts->tasks[i].id);
		j = 0;
		fprintf(f, "\tCore %d : ", v->cpus[j].id);
		while(!schedulable(ts, i, v, j, a) && (j < v->n_cpus)) {
			j++;
			fprintf(f, "UNSCHEDULABLE\n");
			fprintf(f, "\tCore %d : ", v->cpus[j].id);
		}

		if (j == v->n_cpus) {
			return 0;
		}
		
		fprintf(f, "SCHEDULABLE\n");
		allocate_vm(ts, i, v, j);
	}

	fprintf(f, "\n");
	
	return 1;
}

unsigned int next_fit_allocation(taskset *ts, vm* v, s_algorithm a, FILE * f) {
	unsigned int i, j = 0;
	
	fprintf(f, "Let's try to assign the tasks to the different cpus according to the next fit heuristic algorithm:\n");
	for (i = 0; i < ts->size; i++) {
		fprintf(f, "Task %d :\n", ts->tasks[i].id);
		fprintf(f, "\tCore %d : ", v->cpus[j].id);
		while(!schedulable(ts, i, v, j, a) && (j < v->n_cpus)) {
			j++;
			fprintf(f, "UNSCHEDULABLE\n");
			fprintf(f, "\tCore %d : ", v->cpus[j].id);
		}

		if (j == v->n_cpus) {
			return 0;
		}
		
		fprintf(f, "SCHEDULABLE\n");
		allocate_vm(ts, i, v, j);
	}

	fprintf(f, "\n");
	
	return 1;
}

unsigned int worst_fit_allocation(taskset *ts, vm* v, s_algorithm a, FILE * f) {
	unsigned int i, j;
	
	fprintf(f, "Let's try to assign the tasks to the different cpus according to the worst fit heuristic algorithm:\n");
	for (i = 0; i < ts->size; i++) {
		sort_by_decreasing_empty_space(v);
		j = 0;
		fprintf(f, "Task %d :\n", ts->tasks[i].id);
		fprintf(f, "\tCore %d : ", v->cpus[j].id);
		while(!schedulable(ts, i, v, j, a) && (j < v->n_cpus)) {
			j++;
			fprintf(f, "UNSCHEDULABLE\n");
			fprintf(f, "\tCore %d : ", v->cpus[j].id);
		}

		if (j == v->n_cpus) {
			return 0;
		}
		
		fprintf(f, "SCHEDULABLE\n");
		allocate_vm(ts, i, v, j);
	}

	fprintf(f, "\n");
	
	return 1;
}

unsigned int first_fit_decreasing_allocation(taskset *ts, vm* v, s_algorithm a, FILE * f) {
	unsigned int i, j;
	sort_by_decreasing_utilization_factor(ts);
	
	fprintf(f, "Let's try to assign the tasks to the different cpus according to the decreasing first fit heuristic algorithm:\n");
	for (i = 0; i < ts->size; i++) {
		fprintf(f, "Task %d :\n", ts->tasks[i].id);
		j = 0;
		fprintf(f, "\tCore %d : ", v->cpus[j].id);
		while(!schedulable(ts, i, v, j, a) && (j < v->n_cpus)) {
			j++;
			fprintf(f, "UNSCHEDULABLE\n");
			fprintf(f, "\tCore %d : ", v->cpus[j].id);
		}

		if (j == v->n_cpus)
			return 0;
		
		fprintf(f, "SCHEDULABLE\n");
		allocate_vm(ts, i, v, j);
	}

	fprintf(f, "\n");
	
	return 1;
}
