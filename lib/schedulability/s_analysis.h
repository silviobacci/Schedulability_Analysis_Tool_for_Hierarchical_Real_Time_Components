#ifndef S_ANALYSIS_H
#define S_ANALYSIS_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT S SCHEDULABILITY: print if the taskset is schedulable or not
//------------------------------------------------------------------------------

void print_s_schedulability(unsigned int is_schedulable, s_algorithm a, FILE *f);

//------------------------------------------------------------------------------
// PRINT S ANALYSIS FP: perform the sched. analysis under fp
//------------------------------------------------------------------------------

unsigned int s_analysis_fp(taskset *ts, FILE *f);


//------------------------------------------------------------------------------
// PRINT S ANALYSIS EDF: perform the sched. analysis under edf
//------------------------------------------------------------------------------

unsigned int s_analysis_edf(taskset *ts, FILE *f);

#endif
