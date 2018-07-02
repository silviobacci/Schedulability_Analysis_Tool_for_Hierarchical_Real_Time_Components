#ifndef TASK_IO_H
#define TASK_IO_H

void print_taskset(taskset *ts, FILE *f);
void print_periodic_server(periodic_server *ps, FILE *f);
taskset * create_empty_ts();
periodic_server * create_empty_ps();
taskset *add_to_temp_taskset(taskset *previous_ts, task to_add);
taskset *add_to_taskset(taskset *previous_ts, task to_add);
taskset * load_taskset(FILE *f);
periodic_server * load_periodic_server(unsigned int Qs, unsigned int Ts);

#endif
