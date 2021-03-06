#ifndef H_ANALYSIS_H
#define H_ANALYSIS_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// H ANALYSIS FP: performs the sched. analysis under fp with the given server
//------------------------------------------------------------------------------

unsigned int h_analysis_fp(taskset *ts, periodic_server *ps);

//------------------------------------------------------------------------------
// H ANALYSIS EDF: performs the sched. analysis under edf with the given server
//------------------------------------------------------------------------------

unsigned int h_analysis_edf(taskset *ts, periodic_server *ps);

//------------------------------------------------------------------------------
// FIND PERIODIC SERVER: returns the server with min bandwidth able to schedule
//------------------------------------------------------------------------------

periodic_server * find_periodic_server(taskset *ts, s_algorithm a);

#endif
