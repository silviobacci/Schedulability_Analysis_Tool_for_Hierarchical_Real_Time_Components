#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <task/utilities.h>
#include <task/testing_set.h>

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

static void bubble_sort(unsigned int *array, int array_size) {
	int i, j, temp;
	
	for (i = array_size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (array[j] > array[j + 1]) {
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
}

void print_testing_set_edf(unsigned int *testing_set, unsigned int n_testing_set, FILE *f) {
	unsigned int i;

	fprintf(f, "The taskset has %d points in the testing set: { ", n_testing_set);

	for (i = 0; i < n_testing_set; i++)
		fprintf(f, "%u ", testing_set[i]);
	
	fprintf(f, "}\n");
}

void print_testing_set_fp(unsigned int *testing_set, unsigned int n_testing_set, taskset * ts, unsigned int task_index, FILE *f) {
	unsigned int i;
	
	fprintf(f, "Task %d has %d points in the testing set: { ", ts->tasks[task_index].id, n_testing_set);

	for (i = 0; i < n_testing_set; i++)
		fprintf(f, "%u ", testing_set[i]);
	
	fprintf(f, "}\n");
}

int merge_testing_sets(unsigned int *ts1, unsigned int ts1_points, unsigned int *ts2, unsigned int ts2_points, unsigned int* points) {
	unsigned int i, j = 0, k = 0, n_points = 0;

	for (i = 0; i < ts1_points + ts2_points && i < MAX_TESTING_SET_SIZE;) {
		if (j < ts1_points && k < ts2_points) {
			if (ts1[j] < ts2[k]) {
				points[i] = ts1[j];
				j++;
			}
			else {
				points[i] = ts2[k];
				k++;
			}
			i++;
		}
		else if (j == ts1_points) {
			for (; i < ts1_points + ts2_points && i < MAX_TESTING_SET_SIZE;) {
				points[i] = ts2[k];
				k++;
				i++;
			}
		}
		else {
			for (; i < ts1_points + ts2_points && i < MAX_TESTING_SET_SIZE;) {
				points[i] = ts1[j];
				j++;
				i++;
			}
		}
	}

	n_points = i;

	for (i = 0; i < n_points; i++)
		for (j = i + 1; j < n_points;)
			if (points[j] == points[i]) {
				for (k = j; k < n_points; k++)
					points[k] = points[k + 1];
				n_points--;
			} 
			else
				j++;

	return n_points;
}

int testing_set_fp(taskset *ts, unsigned int *points, unsigned int i) {
	unsigned int j, k, index, already_present, n_points = 0;

	if (i >= ts->size)
		return -1;

	points[n_points++] = ts->tasks[i].D;
	
	for (j = 0; j < i; j++) {
		k = 1;
		while (k * ts->tasks[j].T < ts->tasks[i].D) {
			if (n_points == MAX_TESTING_SET_SIZE) 
				return n_points;
			
			already_present = 0;
			for(index = 0; index < n_points; index++)
				if(points[index] == k * ts->tasks[j].T)
					already_present = 1;
				
			if(!already_present)	
				points[n_points++] =  k++ * ts->tasks[j].T;
		}
	}

	bubble_sort(points, n_points);

	return n_points;
}

int testing_set_edf(taskset *ts, unsigned int *points) {
	unsigned int i, k, index, already_present, Dmax, H, n_points = 0;
	double L, Lstar = 0;
	
	for (i = 0; i < ts->size; i++)
		Lstar += (double) (ts->tasks[i].T - ts->tasks[i].D) * utilization_factor_i(ts, i);

	Lstar = Lstar / (1 - utilization_factor(ts));
	
	Dmax = max_deadline(ts);
	H = lcm(ts);
	L = min(H, max(Dmax, Lstar));
	
	for (i = 0; i < ts->size; i++) {
		k = 0;
		while (k * ts->tasks[i].T + ts->tasks[i].D <= L) {
			if (n_points == MAX_TESTING_SET_SIZE)
				return n_points;
			
			already_present = 0;
			for(index = 0; index < n_points; index++)
				if(points[index] == k * ts->tasks[i].T + ts->tasks[i].D)
					already_present = 1;
				
			if(!already_present)	
				points[n_points++] = k++ * ts->tasks[i].T + ts->tasks[i].D;
			else
				k++;			
		}
	}

	bubble_sort(points, n_points);

	return n_points;
}

int testing_set_sbf(periodic_server *ps, unsigned int *points, unsigned int max) {
	unsigned int n = 2, n_points = 0;
	
	while (n * ps->Ts - ps->Qs < max) {
		if (n_points == MAX_TESTING_SET_SIZE) 
			return n_points;
			
		points[n_points++] =  n++ * ps->Ts - ps->Qs;
	}

	return n_points;
}
