#include <sbf/sbf.h>

unsigned int sbf(unsigned int Qs, unsigned int Ts, unsigned int t) {
	unsigned int n;

	if (t < 2 * (Ts - Qs))
		return 0;
	
	// starts the time in the point in which the sbf starts to increase
	t -= 2 * (Ts - Qs);

	// compute n that is 0 the first time the sbf increases, 2 the second time and so on
	n = t / Ts;

	// compute the time once again as if the time 0 was when the sbf starts to increase the last time
	t = t % Ts;

	if (t > Qs) 
		return (n + 1) * Qs;
	
	return t + n * Qs; 
}
