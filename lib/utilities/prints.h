#ifndef PRINTS_H
#define PRINTS_H

void print_taskset(taskset *ts, FILE *f);
void print_taskset_scheduling_points(unsigned int *sp, unsigned int n_sp, FILE *f);
void print_task_scheduling_points(unsigned int task_index, unsigned int *sp, unsigned int n_sp, FILE *f);
void print_periodic_server(periodic_server *ps, FILE *f);
void print_sbf(periodic_server *ps, unsigned int start_time, unsigned int end_time, FILE *f);
void print_s_analysis_fp(taskset *ts, FILE *f);
void print_s_analysis_edf(taskset *ts, FILE *f);
void print_h_analysis_fp(taskset *ts, periodic_server *ps, FILE *f);
void print_h_analysis_edf(taskset *ts, periodic_server *ps, FILE *f);

#endif
