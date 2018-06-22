#ifndef PRINTS_H
#define PRINTS_H

void print_s_algorithm(s_algorithm a, FILE *f);
void print_a_algorithm(a_algorithm a, FILE *f);
void print_taskset(taskset *ts, FILE *f);
void print_vm(vm *c, FILE *f);
void print_vm_load(vm *c, FILE *f);
void print_testing_set_fp(unsigned int *sp, unsigned int n_sp, taskset * ts, unsigned int task_index, FILE *f);
void print_testing_set_edf(unsigned int *sp, unsigned int n_sp, FILE *f);
void print_periodic_server(periodic_server *ps, FILE *f);
void print_s_schedulability(unsigned int is_schedulable, s_algorithm a, FILE *f);
void print_h_schedulability(unsigned int is_schedulable, s_algorithm a, periodic_server * ps, FILE *f);
void print_mcpu_schedulability(unsigned int is_schedulable, a_algorithm a, FILE *f);
void print_find_periodic_server(FILE *f);
void print_sbf(periodic_server *ps, unsigned int start_time, unsigned int end_time, FILE *f);
void print_s_analysis_fp(taskset *ts, FILE *f);
void print_s_analysis_edf(taskset *ts, FILE *f);
void print_h_analysis_fp(taskset *ts, periodic_server *ps, FILE *f);
void print_h_analysis_edf(taskset *ts, periodic_server *ps, FILE *f);

#endif
