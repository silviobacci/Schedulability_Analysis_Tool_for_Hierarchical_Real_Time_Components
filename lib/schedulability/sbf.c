#include <utilities/utilities.h>

#include <schedulability/sbf.h>

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
