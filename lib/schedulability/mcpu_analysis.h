#ifndef MCPU_ANALYSIS_H
#define MCPU_ANALYSIS_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MCPU ANALYSIS: performs the sched. analysis running in the specified vm
//------------------------------------------------------------------------------

unsigned int mcpu_analysis(taskset *ts, vm* v, s_algorithm algorithm, a_algorithm allocation);

#endif
