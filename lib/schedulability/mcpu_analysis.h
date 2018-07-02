#ifndef MCPU_ANALYSIS_H
#define MCPU_ANALYSIS_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT MCPU SCHEDULABILITY: print if the taskset is schedulable or not
//------------------------------------------------------------------------------

void print_mcpu_schedulability(unsigned int is_schedulable, a_algorithm a, FILE *f);

//------------------------------------------------------------------------------
// MCPU ANALYSIS: performs the sched. analysis running in the specified vm
//------------------------------------------------------------------------------

unsigned int mcpu_analysis(taskset *ts, vm* v, s_algorithm algorithm, a_algorithm allocation, FILE *f);

#endif
