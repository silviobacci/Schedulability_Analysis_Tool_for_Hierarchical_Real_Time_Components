#ifndef DBF_H
#define DBF_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// WORKLOAD: compute the workload function at time t for the given task
//------------------------------------------------------------------------------

unsigned int workload(taskset *ts, unsigned int n, unsigned int t);

//------------------------------------------------------------------------------
// PDF: compute the processor demand function at time t for the taskset
//------------------------------------------------------------------------------

double pdf(taskset *ts, unsigned int t);

#endif
