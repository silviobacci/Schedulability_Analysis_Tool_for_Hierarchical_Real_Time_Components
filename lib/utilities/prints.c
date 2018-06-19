#include <stdlib.h>
#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <task/scheduling_points.h>
#include <utilities/prints.h>
#include <utilities/utilities.h>
#include <sbf/sbf.h>
#include <dbf/edf.h>
#include <dbf/rm.h>

void print_taskset(taskset *ts, FILE *f) {
	unsigned int i;

	fprintf(f, "The taskset is composed by the following tasks expressed with the (C,D,T) model:\n");

	for (i = 0; i < ts->size; i++)
		fprintf(f, "\t Task %u : (%u, %u, %u)\n", i + 1, ts->tasks[i].C, ts->tasks[i].D, ts->tasks[i].P);

	fprintf(f, "\n");
}

void print_taskset_scheduling_points(unsigned int *sp, unsigned int n_sp, FILE *f) {
	unsigned int i;

	fprintf(f, "The taskset has %d scheduling points: ", n_sp);

	for (i = 0; i < n_sp; i++)
		fprintf(f, " %u", sp[i]);
	
	fprintf(f, "\n");
}

void print_task_scheduling_points(unsigned int task_index, unsigned int *sp, unsigned int n_sp, FILE *f) {
	unsigned int i;
	
	fprintf(f, "The %d° task has %d scheduling points: ", task_index, n_sp);

	for (i = 0; i < n_sp; i++)
		fprintf(f, " %u", sp[i]);
	
	fprintf(f, "\n");
}

void print_periodic_server(periodic_server *ps, FILE *f) {
	fprintf(f, "The periodic server has the following paramters: \n\t Qs = %d \n\t Ts = %d \n\n", ps->Qs, ps->Ts);
}

void print_sbf(periodic_server *ps, unsigned int start_time, unsigned int end_time, FILE *f) {
	unsigned int t;
	
	fprintf(f, "The sbf computed from time %u to time %u is: \n", start_time, end_time);

	for (t = start_time; t < end_time; t++)
		fprintf(f, "\t sbf(%u) = %u\n", t, sbf(ps->Qs, ps->Ts, t));
}

void print_tda_rm(taskset *ts, FILE *f) {
	unsigned int sp[MAX_SCHEDULING_POINTS], i;
	int j, n_sp;
	
	for(i = 0; i < ts->size; i++) {
		n_sp = scheduling_points(ts, i, sp, MAX_SCHEDULING_POINTS);
		
		if (n_sp > 0) {
			print_task_scheduling_points(i + 1, sp, n_sp, f);
	
			for (j = 0; j < n_sp; j++)
				fprintf(f, "\t dbf(%u) = %u\n", sp[j], dbf_rm(ts, i, sp[j]));

			fprintf(f, "\n");
		}
	}
}

void print_tda_edf(taskset *ts, FILE *f) {
	unsigned int sp[MAX_SCHEDULING_POINTS];
	int i, n_sp;
	
	n_sp = scheduling_points(ts, task_with_max_period(ts), sp, MAX_SCHEDULING_POINTS);
		
	if (n_sp > 0) {
		print_taskset_scheduling_points(sp, n_sp, f);

		for (i = 0; i < n_sp; i++)
			fprintf(f, "\t dbf(%u) = %f\n", sp[i], dbf_edf(ts, sp[i]));
	}
}

void printf_h_analysis_rm(taskset *ts, periodic_server *ps, FILE *f){
	unsigned int sp[MAX_SCHEDULING_POINTS], i;
	int j, n_sp;

	for(i = 0; i < ts->size; i++) {
		n_sp = scheduling_points(ts, i, sp, MAX_SCHEDULING_POINTS);
		
		if (n_sp > 0) {
			print_task_scheduling_points(i + 1, sp, n_sp, f);

			for (j = 0; j < n_sp; j++)
				fprintf(f, "\t dbf(%d) = %u; sbf(%d) = %u\n", sp[j], dbf_rm(ts, i, sp[j]), sp[j], sbf(ps->Qs, ps->Ts, sp[j]));

			fprintf(f, "\n");
		}
	}
}

void printf_h_analysis_edf(taskset *ts, periodic_server *ps, FILE *f){
	unsigned int sp[MAX_SCHEDULING_POINTS];
	int i, n_sp;

	n_sp = scheduling_points(ts, task_with_max_period(ts), sp, MAX_SCHEDULING_POINTS);

	if (n_sp > 0) {
		print_taskset_scheduling_points(sp, n_sp, f);

		for (i = 0; i < n_sp; i++)
			fprintf(f, "\t dbf(%d) = %f; sbf(%d) = %u\n", sp[i], dbf_edf(ts, sp[i]), sp[i], sbf(ps->Qs, ps->Ts, sp[i]));
	}
}
