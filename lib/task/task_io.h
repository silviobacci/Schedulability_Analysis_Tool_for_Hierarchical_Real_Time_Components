#ifndef TASK_IO_H
#define TASK_IO_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT TASKSET: prints all the parameters of a taskset
//------------------------------------------------------------------------------

void print_taskset(taskset *ts, FILE *f);

//------------------------------------------------------------------------------
// PRINT PERIODIC SERVER: prints all the parameters of a periodic server
//------------------------------------------------------------------------------

void print_periodic_server(periodic_server *ps, FILE *f);

//------------------------------------------------------------------------------
// CREATE EMPTY TS: allocate the memory space for an empty taskset
//------------------------------------------------------------------------------

taskset * create_empty_ts();

//------------------------------------------------------------------------------
// CREATE EMPTY PS: allocate the memory space for an empty periodic server
//------------------------------------------------------------------------------

periodic_server * create_empty_ps();

//------------------------------------------------------------------------------
// ADD TO TEMP TASKSET: returns a new taskset merging the taskset and the task
//------------------------------------------------------------------------------

taskset *add_to_temp_taskset(taskset *previous_ts, task to_add);

//------------------------------------------------------------------------------
// ADD TO TASKSET: as the previous function but it deallocates previous_ts
//------------------------------------------------------------------------------

taskset *add_to_taskset(taskset *previous_ts, task to_add);

//------------------------------------------------------------------------------
// LOAD TASKSET: load the taskset specified in the file f
//------------------------------------------------------------------------------

taskset * load_taskset(FILE *f);

//------------------------------------------------------------------------------
// LOAD PERIODIC SERVER: creates a periodic server with the specified Qs and Ts
//------------------------------------------------------------------------------

periodic_server * load_periodic_server(unsigned int Qs, unsigned int Ts);

#endif
