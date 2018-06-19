#ifndef UTILITIES_H
#define UTILITIES_H

unsigned int my_ceil(unsigned int n, unsigned int d);
double my_max(double n1, double n2);
unsigned int task_with_min_period(taskset *ts);
unsigned int task_with_max_period(taskset *ts);
void bubble_sort(unsigned int *array, int array_size);

#endif
