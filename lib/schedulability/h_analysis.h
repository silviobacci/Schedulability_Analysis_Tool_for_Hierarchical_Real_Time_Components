#ifndef H_ANALYSIS_H
#define H_ANALYSIS_H

void print_h_schedulability(unsigned int is_schedulable, s_algorithm a, periodic_server * ps, FILE *f);
void print_h_analysis_fp(taskset *ts, periodic_server *ps, FILE *f);
void print_h_analysis_edf(taskset *ts, periodic_server *ps, FILE *f);
void print_find_periodic_server(FILE *f);
void print_find_periodic_server_vm(unsigned int is, FILE *f);
unsigned int h_analysis_fp(taskset *ts, periodic_server *ps);
unsigned int h_analysis_edf(taskset *ts, periodic_server *ps);
periodic_server * find_periodic_server(taskset *ts, s_algorithm a);

#endif
