#ifndef MCPU_ANALYSIS_H
#define MCPU_ANALYSIS_H

void print_mcpu_schedulability(unsigned int is_schedulable, a_algorithm a, FILE *f);
void print_mcpu_analysis(taskset *ts, vm* v, s_algorithm algorithm, a_algorithm allocation, FILE * f);
unsigned int mcpu_analysis(taskset *ts, vm* v, s_algorithm algorithm, a_algorithm allocation, FILE * f);

#endif
