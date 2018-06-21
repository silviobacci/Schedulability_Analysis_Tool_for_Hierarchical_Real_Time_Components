#include <task/structs/task.h>
#include <task/structs/taskset.h>

unsigned int my_ceil(unsigned int n, unsigned int d) {
	unsigned int q = n / d;
	
	if (q * d == n) 
		return q;
	
	return q + 1;
}

unsigned int my_floor(unsigned int n, unsigned int d) {
	return n / d;
}

double my_max(double n1, double n2) {
	if(n1 > n2)
		return n1;
	return n2;
}

double my_min(double n1, double n2) {
	if(n1 < n2)
		return n1;
	return n2;
}

unsigned int max_deadline(taskset *ts) {
	unsigned int i, MAX = ts->tasks[0].D;

	for(i = 1; i < ts->size; i++)
		if(ts->tasks[i].D > MAX)
			MAX = ts->tasks[i].D;
	
	return MAX;
}

unsigned int min_period(taskset *ts) {
	unsigned int i, MIN = ts->tasks[0].T;

	for(i = 1; i < ts->size; i++)
		if(ts->tasks[i].T < MIN)
			MIN = ts->tasks[i].T;
	
	return MIN;
}

static unsigned int lcm_(int a, int b){
	int lcm_temp = a;
	
	while(1){
		if(lcm_temp % b == 0 && lcm_temp % a == 0)
			break;
		lcm_temp++;
	}

	return lcm_temp;
}

unsigned int lcm(taskset *ts) {
	unsigned int i, lcm_temp = ts->tasks[0].T;

	for(i = 1; i < ts->size; i++)
		if(lcm_temp > ts->tasks[i].T)
			lcm_temp = lcm_(lcm_temp, ts->tasks[i].T);
		else
			lcm_temp = lcm_(ts->tasks[i].T, lcm_temp);

    return lcm_temp;
}

void bubble_sort(unsigned int *array, int array_size) {
	int i, j, temp;
	
	for (i = 0; i < (array_size - 1); i++)
		for (j = 0; j < (array_size - 1 - i); j++)
			if (array[j] > array[j + 1]) {
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
}  
