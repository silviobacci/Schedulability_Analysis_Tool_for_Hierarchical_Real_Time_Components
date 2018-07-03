#ifndef S_ANALYSIS_H
#define S_ANALYSIS_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// WORKLOAD ANALYSIS: perform the sched. analysis under fp
//------------------------------------------------------------------------------

unsigned int workload_analysis(taskset *ts);


//------------------------------------------------------------------------------
// PROCESSOR DEMAND ANALYSIS: perform the sched. analysis under edf
//------------------------------------------------------------------------------

unsigned int processor_demand_analysis(taskset *ts);

#endif
