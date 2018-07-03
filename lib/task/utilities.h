#ifndef TASK_UTILITIES_H
#define TASK_UTILITIES_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// UTILIZATION FACTOR I: utilization factor of a task
//------------------------------------------------------------------------------

double utilization_factor_i(taskset *ts, unsigned int task_index);

//------------------------------------------------------------------------------
// UTILIZATION FACTOR: utilization factor of a taskset
//------------------------------------------------------------------------------

double utilization_factor(taskset *ts);

//------------------------------------------------------------------------------
// PRINT TESTING SET EDF: prints all the scheduling points for edf
//------------------------------------------------------------------------------

double utilization_factor_modified(taskset *ts);

//------------------------------------------------------------------------------
// MAX DEADLINE: returns the maximum deadline among the tasks
//------------------------------------------------------------------------------

unsigned int max_deadline(taskset *ts);

//------------------------------------------------------------------------------
// MAX PERIOD: returns the maximum period among the tasks
//------------------------------------------------------------------------------

unsigned int max_period(taskset *ts);

//------------------------------------------------------------------------------
// MIN DEADLINE: returns the minimum deadline among the tasks
//------------------------------------------------------------------------------

unsigned int min_deadline(taskset *ts);

//------------------------------------------------------------------------------
// MIN PERIOD: returns the minimum period among the tasks
//------------------------------------------------------------------------------

unsigned int min_period(taskset *ts);

//------------------------------------------------------------------------------
// LCM: returns the hyper period of the taskset (least common multiple of all T)
//------------------------------------------------------------------------------	

unsigned int lcm(taskset *ts);

#endif
