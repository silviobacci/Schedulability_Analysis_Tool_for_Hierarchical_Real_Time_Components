#ifndef UTILITIES_H
#define UTILITIES_H

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <vm/structs/cpu.h>
#include <vm/structs/vm.h>

char * s_algorithm_to_string(s_algorithm a);
char * a_algorithm_to_string(a_algorithm a);
double utilization_factor(taskset *ts);
unsigned int my_ceil(unsigned int n, unsigned int d);
unsigned int my_floor(unsigned int n, unsigned int d);
double my_max(double n1, double n2);
double my_min(double n1, double n2);
unsigned int max_deadline(taskset *ts);
unsigned int min_period(taskset *ts);
unsigned int max_period(taskset *ts);
unsigned int lcm(taskset *ts);
void bubble_sort(unsigned int *array, int array_size);
void sort_by_increasing_periods(taskset *ts);
void sort_by_increasing_deadlines(taskset *ts);
void sort_by_increasing_utilization_factor(taskset *ts);
void sort_by_decreasing_periods(taskset *ts);
void sort_by_decreasing_deadlines(taskset *ts);
void sort_by_decreasing_utilization_factor(taskset *ts);
void sort_by_increasing_empty_space(vm *c);
void sort_by_decreasing_empty_space(vm *c);
void sort_taskest_by_id(taskset *ts);
void sort_cpus_by_id(vm *v);

#endif
