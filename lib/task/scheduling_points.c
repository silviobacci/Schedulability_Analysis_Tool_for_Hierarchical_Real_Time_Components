#include <stdlib.h>
#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <utilities/utilities.h>

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
