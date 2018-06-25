#include <stdio.h>

#include <schedulability/mcpu_analysis.h>

#include <schedulability/bin_packing.h>

static taskset *temp_taskset(taskset *previous_ts, task to_add) {
	unsigned int i = 0;

	taskset * new_ts = create_empty_ts();
	
	for(i = 0; i < previous_ts->size; i++)
		new_ts->tasks[i] = previous_ts->tasks[i];
	new_ts->tasks[i] = to_add;
	
	new_ts->size = i + 1;
	new_ts->is_deadline_costrained = 0;

	for(i = 0; i < new_ts->size; i++)
		if(new_ts->tasks[i].D < new_ts->tasks[i].T)
			new_ts->is_deadline_costrained = 1;
	
	return new_ts;
}

static taskset *create_taskset(taskset *previous_ts, task to_add) {
	taskset *new_ts = temp_taskset(previous_ts, to_add);
	free(previous_ts);
	return new_ts;
}

static unsigned int schedulable(taskset *ts, unsigned int task_index, vm *v, unsigned int cpu_index, s_algorithm a) {
	double u = (double) ts->tasks[task_index].C / ts->tasks[task_index].T;
	double expected_u = (double) u + v->cpus[cpu_index].u;
	unsigned int is_schedulable = 0;
	
	if(expected_u > v->cpus[cpu_index].max_u)
		return is_schedulable;
		
	taskset * temp = temp_taskset(v->cpus[cpu_index].ts, ts->tasks[task_index]);

	switch(a) {
		case FP:
			is_schedulable = h_analysis_fp(temp, v->cpus[cpu_index].ps);
			break;
		case RM:
			sort_by_increasing_periods(ts);
			is_schedulable = h_analysis_fp(temp, v->cpus[cpu_index].ps);
			break;
		case DM:
			sort_by_increasing_deadlines(ts);
			is_schedulable = h_analysis_fp(temp, v->cpus[cpu_index].ps);
			break;
		case EDF:
			is_schedulable = h_analysis_edf(temp, v->cpus[cpu_index].ps);
			break;
	}

	free(temp);
		
	return is_schedulable;
}

static void allocate_vm(taskset *ts, unsigned int task_index, vm *v, unsigned int cpu_index) {
	v->cpus[cpu_index].u += (double) ts->tasks[task_index].C / ts->tasks[task_index].T;
	v->cpus[cpu_index].ts = create_taskset(v->cpus[cpu_index].ts, ts->tasks[task_index]);
}

void print_mcpu_schedulability(unsigned int is_schedulable, a_algorithm a, FILE *f) {
	if(is_schedulable)
		fprintf(f, "\nThe taskset is schedulable under multi-CPU partitioned scheduling with the specified cpus and using %s as allocation algorithm.\n", a_algorithm_to_string(a));
	else
		fprintf(f, "\nThe taskset is NOT schedulable under multi-CPU partitioned scheduling with the specified cpus and using %s as allocation algorithm.\n", a_algorithm_to_string(a));
}

void print_mcpu_analysis(taskset *ts, vm* v, s_algorithm algorithm, a_algorithm allocation, FILE * f) {
	unsigned int i, j;
	
	if(allocation == FFD)
		sort_by_decreasing_utilization_factor(ts);
	
	fprintf(f, "Let's try to assign the tasks to the different cpus according to the %s heuristic algorithm:\n", a_algorithm_to_string(allocation));
	for (i = 0; i < ts->size; i++) {
		if(allocation != NF) j = 0;
		if(allocation == BF) sort_by_increasing_empty_space(v);
		if(allocation == WF) sort_by_decreasing_empty_space(v);
		
		fprintf(f, "Task %d :\n", ts->tasks[i].id);
		fprintf(f, "\tCpu %d : ", v->cpus[j].id);
		while(!schedulable(ts, i, v, j, algorithm) && (j < v->n_cpus)) {
			fprintf(f, "UNSCHEDULABLE\n");
			j++;
			fprintf(f, "\tCpu %d : ", v->cpus[j].id);
		}

		if (j == v->n_cpus) {
			fprintf(f, "UNSCHEDULABLE\n");
			return;
		}
		
		fprintf(f, "SCHEDULABLE\n\n");
	}
}

unsigned int mcpu_analysis(taskset *ts, vm* v, s_algorithm algorithm, a_algorithm allocation, FILE * f) {
	unsigned int i, j;
	
	if(allocation == FFD)
		sort_by_decreasing_utilization_factor(ts);
	
	for (i = 0; i < ts->size; i++) {
		if(allocation != NF) j = 0;
		if(allocation == BF) sort_by_increasing_empty_space(v);
		if(allocation == WF) sort_by_decreasing_empty_space(v);
		
		while(!schedulable(ts, i, v, j, algorithm) && (j < v->n_cpus))
			j++;

		if (j == v->n_cpus)
			return 0;
		
		allocate_vm(ts, i, v, j);
	}
	
	return 1;
}
