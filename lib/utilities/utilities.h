#ifndef UTILITIES_H
#define UTILITIES_H

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <cpu/structs/core.h>
#include <cpu/structs/cpu.h>

unsigned int my_ceil(unsigned int n, unsigned int d);
unsigned int my_floor(unsigned int n, unsigned int d);
double my_max(double n1, double n2);
double my_min(double n1, double n2);
unsigned int max_deadline(taskset *ts);
unsigned int min_period(taskset *ts);
unsigned int lcm(taskset *ts);
void bubble_sort(unsigned int *array, int array_size);
void sort_by_increasing_periods(taskset *ts);
void sort_by_increasing_deadlines(taskset *ts);
void sort_by_increasing_utilization_factor(taskset *ts);
void sort_by_decreasing_periods(taskset *ts);
void sort_by_decreasing_deadlines(taskset *ts);
void sort_by_decreasing_utilization_factor(taskset *ts);
void sort_by_increasing_empty_space(cpu *c);
void sort_by_decreasing_empty_space(cpu *c);
void sort_taskest_by_id(taskset *ts);
void sort_cores_by_id(cpu *c);

#endif
