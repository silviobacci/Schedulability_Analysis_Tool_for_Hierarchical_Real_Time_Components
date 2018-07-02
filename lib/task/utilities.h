#ifndef TASK_UTILITIES_H
#define TASK_UTILITIES_H

void print_s_algorithm(s_algorithm a, FILE *f);
char * s_algorithm_to_string(s_algorithm a);
double utilization_factor_i(taskset *ts, unsigned int task_index);
double utilization_factor(taskset *ts);
double utilization_factor_modified(taskset *ts);
unsigned int max_deadline(taskset *ts);
unsigned int max_period(taskset *ts);
unsigned int min_deadline(taskset *ts);
unsigned int min_period(taskset *ts);
unsigned int lcm(taskset *ts);

#endif
