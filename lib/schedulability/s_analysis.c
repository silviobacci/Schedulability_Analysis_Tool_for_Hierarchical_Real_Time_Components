#include <utilities/utilities.h>
#include <task/testing_set.h>
#include <schedulability/dbf.h>

#include <schedulability/s_analysis.h>

unsigned int s_analysis_fp(taskset *ts) {
	unsigned int i, testing_set[MAX_TESTING_SET_SIZE];
	int n_testing_set, j;
	
	for(i = 0; i < ts->size; i++)
		if((n_testing_set = testing_set_fp(ts, testing_set, i)) > 0)
			for (j = 0; j < n_testing_set; j++)
				if (workload(ts, i, testing_set[j]) <= testing_set[i]) 
					return 1;

	return 0;
}

unsigned int s_analysis_edf(taskset *ts) {
	unsigned int testing_set[MAX_TESTING_SET_SIZE];
	int n_testing_set, i;

	if ((n_testing_set = testing_set_edf(ts, testing_set)) > 0)
		for (i = 0; i < n_testing_set; i++)
			if (dbf(ts, testing_set[i]) > testing_set[i])
				return 0;

	return 1;
}
