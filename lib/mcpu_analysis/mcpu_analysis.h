#ifndef MCPU_ANALYSIS_H
#define MCPU_ANALYSIS_H

#include <cpu/structs/core.h>
#include <cpu/structs/cpu.h>

unsigned int schedulable(taskset *ts, unsigned int task_index, cpu *c, unsigned int core_index);
void allocate_cpu(taskset *ts, unsigned int task_index, cpu *c, unsigned int core_index);

#endif
