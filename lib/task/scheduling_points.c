#include <stdlib.h>
#include <stdio.h>

#include <task/task.h>
#include <task/taskset.h>

static void bubble_sort(unsigned int *array, int array_size) {
	int i, j, temp;
	
	for (i = 0; i < (array_size - 1); i++)
		for (j = 0; j < (array_size - 1 - i); j++)
			if (array[j] > array[j + 1]) {
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
}  

int scheduling_points(taskset *ts, unsigned int task_index, unsigned int *sp, unsigned int sp_size) {
	unsigned int i, j, points = 1;

	if (task_index >= ts->size)
		return -1;

	sp[0] = ts->tasks[task_index].D;
	
	for (i = 0; i < task_index; i++) {
		j = 1;
		while (ts->tasks[i].P * j < sp[0]) {
			if (points == sp_size) 
				return points;
			
			sp[points++] = ts->tasks[i].P * j++;
		}
	}

	bubble_sort(sp, points);

	return points;
}
