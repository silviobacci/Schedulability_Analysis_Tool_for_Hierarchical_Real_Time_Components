#include <stdlib.h>
#include <stdio.h>

#include <utilities/utilities.h>
#include <task/testing_set.h>
#include <schedulability/sbf.h>
#include <schedulability/dbf.h>

#include <utilities/prints.h>

void print_s_algorithm(s_algorithm a, FILE *f) {
	fprintf(f, "The taskset schedulability will be checked under %s.\n\n", s_algorithm_to_string(a));
}

void print_a_algorithm(a_algorithm a, FILE *f) {
	fprintf(f, "The taskset schedulability will be checked using %s as allocation algorithm.\n\n", a_algorithm_to_string(a));
}

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

void print_vm(vm *v, FILE *f) {
	unsigned int i;

	sort_cpus_by_id(v);
	fprintf(f, "The vm is composed by the following %d cpus:\n", v->n_cpus);

	for (i = 0; i < v->n_cpus; i++)
		fprintf(f, "\t Cpu %u :\n\t\t Scheduling Algorithm : %s\n\t\t Periodic Server : (Qs = %d,  Ts = %d)\n\t\t U : %f\n\n", v->cpus[i].id, v->cpus[i].algorithm, v->cpus[i].ps->Qs, v->cpus[i].ps->Ts, v->cpus[i].u);
}

void print_vm_load(vm *v, FILE *f) {
	unsigned int i, j, k, round_u, drawn;

	fprintf(f, "The computational load on the vm is the following:\n");
	sort_cpus_by_id(v);
	
	for (i = 0; i < v->n_cpus; i++) {
		fprintf(f, "\t Cpu %u :\n\t\t U : %f", v->cpus[i].id, v->cpus[i].u);
		for (j = 0; j < v->cpus[i].ts->size; j++)
			fprintf(f, "\n\t\t Task %u : (%u, %u, %u)", v->cpus[i].ts->tasks[j].id, v->cpus[i].ts->tasks[j].C, v->cpus[i].ts->tasks[j].D, v->cpus[i].ts->tasks[j].T);
		fprintf(f, "\n");
	}
	
	fprintf(f, "\n");
	
	for (i = 0; i < v->n_cpus; i++) {
		fprintf(f, "\t Cpu %u : [", v->cpus[i].id);
		drawn = 0;
		for (j = 0; j < v->cpus[i].ts->size; j++) {
			round_u = v->cpus[i].ts->tasks[j].C;
			for (k = 0; k < round_u; k++) {
				fprintf(f, "%u",v->cpus[i].ts->tasks[j].id);
				drawn++;
			}
		}
		for (j = drawn; j < 10; j++)
				fprintf(f, " ");
		fprintf(f, "]\n");
	}
}

void print_testing_set_edf(unsigned int *testing_set, unsigned int n_testing_set, FILE *f) {
	unsigned int i;

	fprintf(f, "The taskset has %d points in the testing set: { ", n_testing_set);

	for (i = 0; i < n_testing_set; i++)
		fprintf(f, "%u ", testing_set[i]);
	
	fprintf(f, "}\n");
}

void print_testing_set_fp(unsigned int *testing_set, unsigned int n_testing_set, taskset * ts, unsigned int task_index, FILE *f) {
	unsigned int i;
	
	fprintf(f, "Task %d has %d points in the testing set: { ", ts->tasks[task_index].id, n_testing_set);

	for (i = 0; i < n_testing_set; i++)
		fprintf(f, "%u ", testing_set[i]);
	
	fprintf(f, "}\n");
}

void print_periodic_server(periodic_server *ps, FILE *f) {
	fprintf(f, "The periodic server has the following paramters: \n\t Qs = %d \n\t Ts = %d \n\n", ps->Qs, ps->Ts);
}

void print_s_schedulability(unsigned int is_schedulable, s_algorithm a, FILE *f) {
	if(is_schedulable)
		fprintf(f, "The taskset is schedulable under %s.\n", s_algorithm_to_string(a));
	else
		fprintf(f, "The taskset is NOT schedulable under %s.\n", s_algorithm_to_string(a));
}

void print_h_schedulability(unsigned int is_schedulable, s_algorithm a, periodic_server * ps, FILE *f) {
	if(is_schedulable)
		fprintf(f, "\nThe taskset is schedulable under %s with the specified periodic server (Qs = %u, Ts = %u).\n", s_algorithm_to_string(a), ps->Qs, ps->Ts);
	else
		fprintf(f, "\nThe taskset is NOT schedulable under %s with the specified periodic server (Qs = %u, Ts = %u).\n", s_algorithm_to_string(a), ps->Qs, ps->Ts);
}

void print_mcpu_schedulability(unsigned int is_schedulable, a_algorithm a, FILE *f) {
	if(is_schedulable)
		fprintf(f, "\nThe taskset is schedulable under multi-CPU partitioned scheduling with the specified cpus and using %s as allocation algorithm.\n", a_algorithm_to_string(a));
	else
		fprintf(f, "\nThe taskset is NOT schedulable under multi-CPU partitioned scheduling with the specified cpus and using %s as allocation algorithm.\n", a_algorithm_to_string(a));
}

void print_find_periodic_server(FILE *f) {
	fprintf(f, "Let's try to find a periodic server that can schedule the entire taskset. ");
}

void print_sbf(periodic_server *ps, unsigned int start_time, unsigned int end_time, FILE *f) {
	unsigned int t;
	
	fprintf(f, "The sbf computed from time %u to time %u is: \n", start_time, end_time);

	for (t = start_time; t < end_time; t++)
		fprintf(f, "\t sbf(%u) = %u\n", t, sbf(ps, t));
}

void print_s_analysis_fp(taskset *ts, FILE *f) {
	unsigned int testing_set[MAX_TESTING_SET_SIZE], i;
	int j, n_testing_set;
	
	for(i = 0; i < ts->size; i++)
		if ((n_testing_set = testing_set_fp(ts, testing_set, i)) > 0) {
			print_testing_set_fp(testing_set, n_testing_set, ts, i, f);
	
			for (j = 0; j < n_testing_set; j++)
				fprintf(f, "\t dbf(%u) = %u\n", testing_set[j], workload(ts, i, testing_set[j]));

			fprintf(f, "\n");
		}
}

void print_s_analysis_edf(taskset *ts, FILE *f) {
	unsigned int testing_set[MAX_TESTING_SET_SIZE];
	int i, n_testing_set;
		
	if ((n_testing_set = testing_set_edf(ts, testing_set)) > 0) {
		print_testing_set_edf(testing_set, n_testing_set, f);
		for (i = 0; i < n_testing_set; i++)
			fprintf(f, "\t dbf(%u) = %f\n", testing_set[i], dbf(ts, testing_set[i]));
			
		fprintf(f, "\n");
	}
}

void print_h_analysis_fp(taskset *ts, periodic_server *ps, FILE *f){
	unsigned int testing_set[MAX_TESTING_SET_SIZE], i;
	int j, n_testing_set;

	for(i = 0; i < ts->size; i++)
		if ((n_testing_set = testing_set_fp(ts, testing_set, i)) > 0) {
			print_testing_set_fp(testing_set, n_testing_set, ts, i, f);

			for (j = 0; j < n_testing_set; j++)
				fprintf(f, "\t dbf(%d) = %u; sbf(%d) = %u\n", testing_set[j], workload(ts, i, testing_set[j]), testing_set[j], sbf(ps, testing_set[j]));

			fprintf(f, "\n");
		}
}

void print_h_analysis_edf(taskset *ts, periodic_server *ps, FILE *f){
	unsigned int testing_set[MAX_TESTING_SET_SIZE];
	int i, n_testing_set;

	if ((n_testing_set = testing_set_edf(ts, testing_set)) > 0) {
		print_testing_set_edf(testing_set, n_testing_set, f);

		for (i = 0; i < n_testing_set; i++)
			fprintf(f, "\t dbf(%d) = %f; sbf(%d) = %u\n", testing_set[i], dbf(ts, testing_set[i]), testing_set[i], sbf(ps, testing_set[i]));
	}
}
