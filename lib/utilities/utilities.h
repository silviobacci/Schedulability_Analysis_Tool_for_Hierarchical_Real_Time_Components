#ifndef UTILITIES_H
#define UTILITIES_H

unsigned int my_ceil(unsigned int n, unsigned int d);
unsigned int my_floor(unsigned int n, unsigned int d);
double my_max(double n1, double n2);
double my_min(double n1, double n2);
unsigned int max_deadline(taskset *ts);
unsigned int min_period(taskset *ts);
unsigned int lcm(taskset *ts);
void bubble_sort(unsigned int *array, int array_size);

#endif
