#ifndef TESTING_SET_H
#define TESTING_SET_H

#define MAX_TESTING_SET_SIZE	128

int merge_testing_sets(unsigned int *ts1, unsigned int ts1_points, unsigned int *ts2, unsigned int ts2_points, unsigned int* points);
void print_testing_set_edf(unsigned int *testing_set, unsigned int n_testing_set, FILE *f);
void print_testing_set_fp(unsigned int *testing_set, unsigned int n_testing_set, taskset * ts, unsigned int task_index, FILE *f);
int testing_set_fp(taskset *ts, unsigned int *points, unsigned int i);
int testing_set_edf(taskset *ts, unsigned int *points);
int testing_set_sbf(periodic_server *ps, unsigned int *points, unsigned int max);

#endif
