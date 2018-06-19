#ifndef TASK_IO_H
#define TASK_IO_H

#include <task/task.h>
#include <task/taskset.h>

taskset *taskset_load(FILE *f);
void taskset_print(taskset *ts, FILE *f);

#endif
