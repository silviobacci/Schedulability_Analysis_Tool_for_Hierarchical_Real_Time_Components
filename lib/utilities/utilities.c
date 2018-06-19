#include <task/structs/task.h>
#include <task/structs/taskset.h>

unsigned int my_ceil(unsigned int n, unsigned int d) {
	unsigned int q = n / d;
	
	if (q * d == n) 
		return q;
	
	return q + 1;
}

double my_max(double n1, double n2) {
	if(n1 > n2)
		return n1;
	return n2;
}

unsigned int task_with_min_period(taskset *ts) {
	unsigned int i;
	unsigned int MIN = ts->tasks[0].P;

	for(i = 1; i < ts->size; i++)
		if(ts->tasks[i].P < MIN)
			MIN = ts->tasks[i].P;
	
	return MIN;
}

unsigned int task_with_max_period(taskset *ts) {
	unsigned int i, max_period = 0, thread_index = 0;

	for (i = 0; i < ts->size; i++)
		if(ts->tasks[i].P > max_period) {
			max_period = ts->tasks[i].P;
			thread_index = i;
		}

	return thread_index;
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
