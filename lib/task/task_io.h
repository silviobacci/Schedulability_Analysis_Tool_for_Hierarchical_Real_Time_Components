#ifndef TASK_IO_H
#define TASK_IO_H

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>

taskset * load_taskset(FILE *f);
periodic_server * load_periodic_server(unsigned int Qs, unsigned int Ts);

#endif
