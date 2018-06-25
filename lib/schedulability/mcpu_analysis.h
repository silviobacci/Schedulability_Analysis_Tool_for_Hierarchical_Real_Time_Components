#ifndef MCPU_ANALYSIS_H
#define MCPU_ANALYSIS_H

unsigned int schedulable(taskset *ts, unsigned int task_index, vm *v, unsigned int cpu_index, s_algorithm a);
void allocate_vm(taskset *ts, unsigned int task_index, vm *v, unsigned int cpu_index);

#endif
