#include <stdlib.h>

#include <utilities/utilities.h>

char * s_algorithm_to_string(s_algorithm a) {
	char * ret = malloc(sizeof(char) * 5);
	switch(a) {
		case RM:
			ret = "RM";
			break;
		case DM:
			ret = "DM";
			break;
		case EDF:
			ret = "EDF";
			break;
	}
	
	return ret;
}

char * a_algorithm_to_string(a_algorithm a) {
	char * ret = malloc(sizeof(char) * 25);
	switch(a) {
		case BF:
			ret = "BEST FIT";
			break;
		case FF:
			ret = "FIRST FIT";
			break;
		case NF:
			ret = "NEXT FIT";
			break;
		case WF:
			ret = "WORST FIT";
			break;
		case FFD:
			ret = "FIRST FIT DECREASING";
			break;
	}
	
	return ret;
}

double utilization_factor(taskset *ts) {
	unsigned int i;
	double U = 0;

	for(i = 0; i < ts->size; i++)
		U += (double) ts->tasks[i].C / ts->tasks[i].T;
	
	return U;
}

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

taskset * create_empty_ts() {
	taskset *ts = malloc(sizeof(taskset));

	if (ts == NULL)
		return NULL;

	ts->tasks = malloc(sizeof(task) * MAX_NUMBER_TASKS);
	
	if (ts->tasks == NULL) {
		free(ts);
		return NULL;
	}
	
	ts->size = 0;

	return ts;
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

void sort_by_increasing_empty_space(vm *v) {
	unsigned int i, j;
	cpu * temp = malloc(sizeof(cpu));
	
	for (i = v->n_cpus - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (v->cpus[j].u < v->cpus[j + 1].u) {
				*temp = v->cpus[j + 1];
				v->cpus[j + 1] = v->cpus[j];
				v->cpus[j] = *temp;
			}
	free(temp);
}

void sort_by_decreasing_empty_space(vm *v) {
	unsigned int i, j, n_cpus = 0;
	cpu * temp = malloc(sizeof(cpu));

	sort_by_increasing_empty_space(v);

	for (i = 0; i < v->n_cpus; i++)
		if(v->cpus[i].u > 0)
			n_cpus++;

	if(n_cpus == 0)
		n_cpus++;
	
	for (i = n_cpus - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (v->cpus[j].u > v->cpus[j + 1].u) {
				*temp = v->cpus[j + 1];
				v->cpus[j + 1] = v->cpus[j];
				v->cpus[j] = *temp;
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

void sort_cpus_by_id(vm *v) {
	unsigned int i, j;
	cpu * temp = malloc(sizeof(cpu));
	
	for (i = v->n_cpus - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (v->cpus[j].id > v->cpus[j + 1].id) {
				*temp = v->cpus[j + 1];
				v->cpus[j + 1] = v->cpus[j];
				v->cpus[j] = *temp;
			}
	free(temp);
}
