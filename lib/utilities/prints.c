#include <stdlib.h>
#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <cpu/structs/core.h>
#include <cpu/structs/cpu.h>
#include <task/testing_set.h>
#include <utilities/prints.h>
#include <utilities/utilities.h>
#include <sbf/sbf.h>
#include <dbf/edf.h>
#include <dbf/fp.h>

void print_taskset(taskset *ts, FILE *f) {
	unsigned int i;

	fprintf(f, "The taskset is composed by the following tasks expressed with the (C,D,T) model:\n");

	for (i = 0; i < ts->size; i++)
		fprintf(f, "\t Task %u : (%u, %u, %u)\n", ts->tasks[i].id, ts->tasks[i].C, ts->tasks[i].D, ts->tasks[i].T);

	if(ts->is_deadline_costrained)
		fprintf(f, "Note that the taskset has the deadlines that less than or equal to the periods.\n");
	else
		fprintf(f, "Note that the taskset has the deadlines always equal to the periods.\n");

	fprintf(f, "\n");
}

void print_cpu(cpu *c, FILE *f) {
	unsigned int i;

	sort_cores_by_id(c);
	fprintf(f, "The cpu is composed by the following %d cores:\n", c->n_cores);

	for (i = 0; i < c->n_cores; i++)
		fprintf(f, "\t Core %u :\n\t\t Scheduling Algorithm : %s\n\t\t Periodic Server : (Qs = %d,  Ts = %d)\n\t\t U : %f\n\n", c->cores[i].id, c->cores[i].algorithm, c->cores[i].ps->Qs, c->cores[i].ps->Ts, c->cores[i].u);
}

void print_cpu_load(cpu *c, FILE *f) {
	unsigned int i, j;

	fprintf(f, "The computational load on the cpu is the following:\n");
	sort_cores_by_id(c);
	
	sort_cores_by_id(c);
	for (i = 0; i < c->n_cores; i++) {
		fprintf(f, "\t Core %u :\n\t\t U : %f", c->cores[i].id, c->cores[i].u);
		for (j = 0; j < c->cores[i].ts->size; j++)
			fprintf(f, "\n\t\t Task %u : (%u, %u, %u)", c->cores[i].ts->tasks[j].id, c->cores[i].ts->tasks[j].C, c->cores[i].ts->tasks[j].D, c->cores[i].ts->tasks[j].T);
		fprintf(f, "\n");
	}
}

void print_testing_set_edf(unsigned int *testing_set, unsigned int n_testing_set, FILE *f) {
	unsigned int i;

	fprintf(f, "The taskset has %d points in the testing set: { ", n_testing_set);

	for (i = 0; i < n_testing_set; i++)
		fprintf(f, "%u ", testing_set[i]);
	
	fprintf(f, "}\n");
}

void print_testing_set_fp(unsigned int *testing_set, unsigned int n_testing_set, unsigned int task_index, FILE *f) {
	unsigned int i;
	
	fprintf(f, "The %d° task has %d points in the testing set: { ", task_index, n_testing_set);

	for (i = 0; i < n_testing_set; i++)
		fprintf(f, "%u ", testing_set[i]);
	
	fprintf(f, "}\n");
}

void print_periodic_server(periodic_server *ps, FILE *f) {
	fprintf(f, "The periodic server has the following paramters: \n\t Qs = %d \n\t Ts = %d \n\n", ps->Qs, ps->Ts);
}

void print_sbf(periodic_server *ps, unsigned int start_time, unsigned int end_time, FILE *f) {
	unsigned int t;
	
	fprintf(f, "The sbf computed from time %u to time %u is: \n", start_time, end_time);

	for (t = start_time; t < end_time; t++)
		fprintf(f, "\t sbf(%u) = %u\n", t, sbf(ps, t));
}

void print_s_analysis_fp(taskset *ts, FILE *f) {
	unsigned int testing_set[MAX_SCHEDULING_POINTS], i;
	int j, n_testing_set;
	
	for(i = 0; i < ts->size; i++)
		if ((n_testing_set = testing_set_fp(ts, testing_set, i)) > 0) {
			print_testing_set_fp(testing_set, n_testing_set, i + 1, f);
	
			for (j = 0; j < n_testing_set; j++)
				fprintf(f, "\t dbf(%u) = %u\n", testing_set[j], workload(ts, i, testing_set[j]));

			fprintf(f, "\n");
		}
}

void print_s_analysis_edf(taskset *ts, FILE *f) {
	unsigned int testing_set[MAX_SCHEDULING_POINTS];
	int i, n_testing_set;
		
	if ((n_testing_set = testing_set_edf(ts, testing_set)) > 0) {
		print_testing_set_edf(testing_set, n_testing_set, f);
		for (i = 0; i < n_testing_set; i++)
			fprintf(f, "\t dbf(%u) = %f\n", testing_set[i], dbf(ts, testing_set[i]));
	}
}

void print_h_analysis_fp(taskset *ts, periodic_server *ps, FILE *f){
	unsigned int testing_set[MAX_SCHEDULING_POINTS], i;
	int j, n_testing_set;

	for(i = 0; i < ts->size; i++)
		if ((n_testing_set = testing_set_fp(ts, testing_set, i)) > 0) {
			print_testing_set_fp(testing_set, n_testing_set, i + 1, f);

			for (j = 0; j < n_testing_set; j++)
				fprintf(f, "\t dbf(%d) = %u; sbf(%d) = %u\n", testing_set[j], workload(ts, i, testing_set[j]), testing_set[j], sbf(ps, testing_set[j]));

			fprintf(f, "\n");
		}
}

void print_h_analysis_edf(taskset *ts, periodic_server *ps, FILE *f){
	unsigned int testing_set[MAX_SCHEDULING_POINTS];
	int i, n_testing_set;

	if ((n_testing_set = testing_set_edf(ts, testing_set)) > 0) {
		print_testing_set_edf(testing_set, n_testing_set, f);

		for (i = 0; i < n_testing_set; i++)
			fprintf(f, "\t dbf(%d) = %f; sbf(%d) = %u\n", testing_set[i], dbf(ts, testing_set[i]), testing_set[i], sbf(ps, testing_set[i]));
	}
}
