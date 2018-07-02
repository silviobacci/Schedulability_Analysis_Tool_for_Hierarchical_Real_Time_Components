#ifndef SBF_H
#define SBF_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT SBF: print the sbf function in a given interval
//------------------------------------------------------------------------------

void print_sbf(periodic_server *ps, unsigned int start_time, unsigned int end_time, FILE *f);

//------------------------------------------------------------------------------
// SBF: compute the supplied bound function of the periodic server at time t
//------------------------------------------------------------------------------

unsigned int sbf(periodic_server *ps, unsigned int t);

#endif
