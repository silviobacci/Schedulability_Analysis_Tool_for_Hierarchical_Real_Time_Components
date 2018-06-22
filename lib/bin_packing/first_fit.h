#ifndef FIRST_FIT_H
#define FIRST_FIT_H

unsigned int first_fit_allocation(taskset *ts, cpu* c, FILE * f);
unsigned int first_fit_decreasing_allocation(taskset *ts, cpu* c, FILE * f);

#endif
