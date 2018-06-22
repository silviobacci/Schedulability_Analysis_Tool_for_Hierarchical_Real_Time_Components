#ifndef BIN_PACKING_H
#define BIN_PACKING_H

unsigned int best_fit_allocation(taskset *ts, vm* c, FILE * f);
unsigned int first_fit_allocation(taskset *ts, vm* c, FILE * f);
unsigned int next_fit_allocation(taskset *ts, vm* c, FILE * f);
unsigned int worst_fit_allocation(taskset *ts, vm* c, FILE * f);
unsigned int first_fit_decreasing_allocation(taskset *ts, vm* c, FILE * f);

#endif
