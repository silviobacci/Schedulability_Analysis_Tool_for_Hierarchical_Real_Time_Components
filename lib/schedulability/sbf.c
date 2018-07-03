//------------------------------------------------------------------------------
// SBF:	Contains function to compute the supplied bound function.
//------------------------------------------------------------------------------

#include "task/types.h"
#include "schedulability/sbf.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

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
