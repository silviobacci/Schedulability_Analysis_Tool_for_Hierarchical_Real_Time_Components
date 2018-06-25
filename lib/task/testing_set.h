#ifndef TESTING_SET_H
#define TESTING_SET_H

#define MAX_TESTING_SET_SIZE	128

void print_testing_set_edf(unsigned int *testing_set, unsigned int n_testing_set, FILE *f);
void print_testing_set_fp(unsigned int *testing_set, unsigned int n_testing_set, taskset * ts, unsigned int task_index, FILE *f);
int testing_set_fp(taskset *ts, unsigned int *points, unsigned int i);
int testing_set_edf(taskset *ts, unsigned int *points);

#endif
