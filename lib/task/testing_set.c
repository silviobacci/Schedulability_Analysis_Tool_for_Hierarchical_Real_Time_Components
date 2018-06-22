#include <utilities/utilities.h>

#include <task/testing_set.h>

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
		Lstar += (double) (ts->tasks[i].T - ts->tasks[i].D) * ts->tasks[i].C / ts->tasks[i].T;

	Lstar = Lstar / (1 - utilization_factor(ts));
	
	Dmax = max_deadline(ts);
	H = lcm(ts);
	L = my_min(H, my_max(Dmax, Lstar));
	
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
