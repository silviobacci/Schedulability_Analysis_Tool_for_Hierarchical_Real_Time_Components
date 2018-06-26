#ifndef S_ANALYSIS_H
#define S_ANALYSIS_H

void print_s_schedulability(unsigned int is_schedulable, s_algorithm a, FILE *f);
unsigned int s_analysis_fp(taskset *ts, FILE *f);
unsigned int s_analysis_edf(taskset *ts, FILE *f);

#endif
