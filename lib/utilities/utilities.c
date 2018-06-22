#include <stdlib.h>

#include <utilities/utilities.h>

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
	
	for (i = array_size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (array[j] > array[j + 1]) {
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
}

void sort_by_increasing_periods(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (ts->tasks[j].T > ts->tasks[j + 1].T) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_increasing_deadlines(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (ts->tasks[j].D > ts->tasks[j + 1].D) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_increasing_utilization_factor(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if ((double) ts->tasks[j].C / ts->tasks[j].T > (double) ts->tasks[j + 1].C / ts->tasks[j + 1].T) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_decreasing_periods(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (ts->tasks[j].T < ts->tasks[j + 1].T) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_decreasing_deadlines(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (ts->tasks[j].D < ts->tasks[j + 1].D) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_decreasing_utilization_factor(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));

	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if ((double) ts->tasks[j].C / ts->tasks[j].T < (double) ts->tasks[j + 1].C / ts->tasks[j + 1].T) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_by_increasing_empty_space(cpu *c) {
	unsigned int i, j;
	core * temp = malloc(sizeof(core));
	
	for (i = c->n_cores - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (c->cores[j].u < c->cores[j + 1].u) {
				*temp = c->cores[j + 1];
				c->cores[j + 1] = c->cores[j];
				c->cores[j] = *temp;
			}
	free(temp);
}

void sort_by_decreasing_empty_space(cpu *c) {
	unsigned int i, j, n_cores = 0;
	core * temp = malloc(sizeof(core));

	sort_by_increasing_empty_space(c);

	for (i = 0; i < c->n_cores; i++)
		if(c->cores[i].u > 0)
			n_cores++;

	if(n_cores == 0)
		n_cores++;
	
	for (i = n_cores - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (c->cores[j].u > c->cores[j + 1].u) {
				*temp = c->cores[j + 1];
				c->cores[j + 1] = c->cores[j];
				c->cores[j] = *temp;
			}
	free(temp);
}

void sort_taskest_by_id(taskset *ts) {
	unsigned int i, j;
	task * temp = malloc(sizeof(task));
	
	for (i = ts->size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (ts->tasks[j].id > ts->tasks[j + 1].id) {
				*temp = ts->tasks[j + 1];
				ts->tasks[j + 1] = ts->tasks[j];
				ts->tasks[j] = *temp;
			}
	free(temp);
}

void sort_cores_by_id(cpu *c) {
	unsigned int i, j;
	core * temp = malloc(sizeof(core));
	
	for (i = c->n_cores - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (c->cores[j].id > c->cores[j + 1].id) {
				*temp = c->cores[j + 1];
				c->cores[j + 1] = c->cores[j];
				c->cores[j] = *temp;
			}
	free(temp);
}
