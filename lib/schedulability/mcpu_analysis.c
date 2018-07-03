//------------------------------------------------------------------------------
// MCPU ANALYSIS:	Contains functions to perform mcpu sched. analysis.
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <task/task_io.h>
#include <task/sorting.h>
#include <vm/structs/cpu.h>
#include <vm/structs/vm.h>
#include <vm/utilities.h>
#include <vm/sorting.h>
#include <vm/vm_io.h>
#include <schedulability/s_analysis.h>
#include <schedulability/h_analysis.h>
#include <schedulability/mcpu_analysis.h>

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SCHEDULABLE: check if a task can be allocated to a given cpu
//------------------------------------------------------------------------------

static unsigned int schedulable(taskset *ts, unsigned int task_index, vm *v, unsigned int cpu_index, s_algorithm a) {
	double u = (double) ts->tasks[task_index].C / ts->tasks[task_index].T;
	double expected_u = (double) u + v->cpus[cpu_index].u;
	unsigned int is_schedulable = 0;
	
	if(expected_u > v->cpus[cpu_index].max_u)
		return is_schedulable;
		
	taskset * temp = add_to_temp_taskset(v->cpus[cpu_index].ts, ts->tasks[task_index]);

	switch(a) {
		case FP:
		case RM:
		case DM:
			is_schedulable = (!v->ps_set) ? s_analysis_fp(temp, NULL) : h_analysis_fp(temp, v->cpus[cpu_index].ps, NULL);
			break;
		case EDF:
			is_schedulable = (!v->ps_set) ? s_analysis_edf(temp, NULL) : h_analysis_edf(temp, v->cpus[cpu_index].ps, NULL);
			break;
	}

	free(temp);
		
	return is_schedulable;
}

//------------------------------------------------------------------------------
// ALLOCATE_VM: allocate a task to a given cpu
//------------------------------------------------------------------------------

static void allocate(taskset *ts, unsigned int task_index, vm *v, unsigned int cpu_index) {
	v->cpus[cpu_index].u += (double) ts->tasks[task_index].C / ts->tasks[task_index].T;
	v->cpus[cpu_index].ts = add_to_taskset(v->cpus[cpu_index].ts, ts->tasks[task_index]);
}

//------------------------------------------------------------------------------
// PRINT MCPU SCHEDULABILITY: print if the taskset is schedulable or not
//------------------------------------------------------------------------------

void print_mcpu_schedulability(unsigned int is_schedulable, a_algorithm a, FILE *f) {
	if(is_schedulable)
		fprintf(f, "\nThe taskset is schedulable under multi-CPU partitioned scheduling with the specified cpus and using %s as allocation algorithm.\n", a_algorithm_to_string(a));
	else
		fprintf(f, "\nThe taskset is NOT schedulable under multi-CPU partitioned scheduling with the specified cpus and using %s as allocation algorithm.\n", a_algorithm_to_string(a));
}

//------------------------------------------------------------------------------
// MCPU ANALYSIS: performs the sched. analysis running in the specified vm
//------------------------------------------------------------------------------

unsigned int mcpu_analysis(taskset *ts, vm* v, s_algorithm algorithm, a_algorithm allocation, FILE *f) {
	unsigned int i, j = 0;
	
	if(algorithm == EDF && allocation == FFD)
		sort_by_decreasing_utilization_factor(ts);
	
	fprintf(f, "Let's try to assign the tasks to the different cpus according to the %s heuristic algorithm:\n", a_algorithm_to_string(allocation));
	for (i = 0; i < ts->size; i++) {
		if(allocation != NF) j = 0;
		if(allocation == BF) {if(algorithm == EDF) sort_by_increasing_empty_space(v); else sort_by_increasing_empty_space_workload(v);}
		if(allocation == WF) {if(algorithm == EDF) sort_by_decreasing_empty_space(v); else sort_by_decreasing_empty_space_workload(v);}
		
		fprintf(f, "Task %d :\n", ts->tasks[i].id);
		fprintf(f, "\tCpu %d : ", v->cpus[j].id);
		while(!schedulable(ts, i, v, j, algorithm) && (j < v->n_cpus)) {
			fprintf(f, "UNSCHEDULABLE\n");
			if (++j == v->n_cpus) return 0;
			fprintf(f, "\tCpu %d : ", v->cpus[j].id);
		}
		
		fprintf(f, "SCHEDULABLE\n\n");
		allocate(ts, i, v, j);
	}
	
	return 1;
}
