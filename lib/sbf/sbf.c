#include <sbf/sbf.h>

unsigned int sbf(unsigned int Qs, unsigned int Ts, unsigned int t) {
	unsigned int n;

	if (t < 2 * (Ts - Qs))
		return 0;
	
	t -= 2 * (Ts - Qs);
	n = t / Ts;
	t = t % Ts;

	if (t > Qs) 
		return (n + 1) * Qs;
	
	return t + n * Qs; 
}
