#ifndef DBF_H
#define DBF_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// WORKLOAD FUNCTION: compute the workload function at time t for the given task
//------------------------------------------------------------------------------

unsigned int workload_function(taskset *ts, unsigned int n, unsigned int t);

//------------------------------------------------------------------------------
// PROCESSOR DEMAND FUNCTION: compute the processor demand function at time t
//------------------------------------------------------------------------------

double processor_demand_function(taskset *ts, unsigned int t);

#endif
