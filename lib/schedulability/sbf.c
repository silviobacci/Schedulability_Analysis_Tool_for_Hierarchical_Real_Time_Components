//------------------------------------------------------------------------------
// SBF:	Contains function to compute the supplied bound function.
//------------------------------------------------------------------------------

#include <stdio.h>

#include <task/structs/periodic_server.h>
#include <schedulability/sbf.h>

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT SBF: print the sbf function in a given interval
//------------------------------------------------------------------------------

void print_sbf(periodic_server *ps, unsigned int start_time, unsigned int end_time, FILE *f) {
	unsigned int t;
	
	fprintf(f, "The sbf computed from time %u to time %u is: \n", start_time, end_time);

	for (t = start_time; t < end_time; t++)
		fprintf(f, "\t sbf(%u) = %u\n", t, sbf(ps, t));
}

//------------------------------------------------------------------------------
// SBF: compute the supplied bound function of the periodic server at time t
//------------------------------------------------------------------------------

unsigned int sbf(periodic_server *ps, unsigned int t) {
	unsigned int n;

	if (t < 2 * (ps->Ts - ps->Qs))
		return 0;
	
	t -= 2 * (ps->Ts - ps->Qs);
	n = t / ps->Ts;
	t = t % ps->Ts;

	if (t > ps->Qs) 
		return (n + 1) * ps->Qs;
	
	return t + n * ps->Qs; 
}
