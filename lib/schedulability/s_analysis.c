#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <task/testing_set.h>
#include <task/utilities.h>
#include <schedulability/dbf.h>

#include <schedulability/s_analysis.h>

void print_s_schedulability(unsigned int is_schedulable, s_algorithm a, FILE *f) {
	if(is_schedulable)
		fprintf(f, "The taskset is schedulable under %s.\n", s_algorithm_to_string(a));
	else
		fprintf(f, "The taskset is NOT schedulable under %s.\n", s_algorithm_to_string(a));
}

unsigned int s_analysis_fp(taskset *ts, FILE *f) {
	unsigned int i, testing_set[MAX_TESTING_SET_SIZE], is_schedulable = 0;
	int n_testing_set, j;
	if(f == NULL) f = fopen("./null", "w");
	
	for(i = 0; i < ts->size; i++)
		if((n_testing_set = testing_set_fp(ts, testing_set, i)) > 0) {
			print_testing_set_fp(testing_set, n_testing_set, ts, i, f);
			for (j = 0; j < n_testing_set; j++) {
				fprintf(f, "\t dbf(%u) = %u\n", testing_set[j], workload(ts, i, testing_set[j]));
				
				if (workload(ts, i, testing_set[j]) <= testing_set[i]) 
					is_schedulable = 1;
			}

			fprintf(f, "\n");
		}

	return is_schedulable;
}

unsigned int s_analysis_edf(taskset *ts, FILE *f) {
	unsigned int testing_set[MAX_TESTING_SET_SIZE], is_schedulable = 1;
	int n_testing_set, i;
	if(f == NULL) f = fopen("./null", "w");

	if ((n_testing_set = testing_set_edf(ts, testing_set)) > 0) {
		print_testing_set_edf(testing_set, n_testing_set, f);
		for (i = 0; i < n_testing_set; i++) {
			fprintf(f, "\t dbf(%u) = %f\n", testing_set[i], dbf(ts, testing_set[i]));

			if (dbf(ts, testing_set[i]) > testing_set[i])
				is_schedulable = 0;
		}

		fprintf(f, "\n");
	}

	return is_schedulable && utilization_factor(ts) < 1;
}
