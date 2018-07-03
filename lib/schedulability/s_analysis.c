//------------------------------------------------------------------------------
// S ANALYSIS:	Contains functions to perform sched. analysis.
//------------------------------------------------------------------------------

#include <stdio.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <task/testing_set.h>
#include <task/utilities.h>
#include <schedulability/dbf.h>

#include <schedulability/s_analysis.h>

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT S SCHEDULABILITY: print if the taskset is schedulable or not
//------------------------------------------------------------------------------

void print_s_schedulability(unsigned int is_schedulable, s_algorithm a, FILE *f) {
	if(is_schedulable)
		fprintf(f, "The taskset is schedulable under %s.\n", s_algorithm_to_string(a));
	else
		fprintf(f, "The taskset is NOT schedulable under %s.\n", s_algorithm_to_string(a));
}

//------------------------------------------------------------------------------
// PRINT S ANALYSIS FP: perform the sched. analysis under fp
//------------------------------------------------------------------------------

unsigned int s_analysis_fp(taskset *ts, FILE *f) {
	unsigned int i, testing_set[MAX_TESTING_SET_SIZE], is_schedulable = 0;
	int n_testing_set, j;
	FILE *out = (f != NULL) ? f : stdout;
	
	for(i = 0; i < ts->size; i++) {
		fprintf(out, "sono qui i = %u, ts->size = %u\n", i, ts->size);
		is_schedulable = 0;
		if((n_testing_set = testing_set_fp(ts, testing_set, i)) > 0) {
			print_testing_set_fp(testing_set, n_testing_set, ts, i, out);
			for (j = 0; j < n_testing_set; j++) {
				fprintf(out, "\t dbf(%u) = %u ", testing_set[j], workload(ts, i, testing_set[j]));
				
				if (workload(ts, i, testing_set[j]) <= testing_set[j]) {
					fprintf(out, "\tOK\n");
					is_schedulable = 1;					
				}
				else
					fprintf(out, "\tNO\n");
			}
			
			fprintf(out, "\n");
			
			if(!is_schedulable)
				break;
		}	
	}


	fprintf(out, "sono qui\n");

	return is_schedulable;
}

//------------------------------------------------------------------------------
// PRINT S ANALYSIS EDF: perform the sched. analysis under edf
//------------------------------------------------------------------------------

unsigned int s_analysis_edf(taskset *ts, FILE *f) {
	unsigned int testing_set[MAX_TESTING_SET_SIZE], is_schedulable = 1;
	int n_testing_set, i;
	FILE *out = (f != NULL) ? f : fopen("./.null", "w");

	if ((n_testing_set = testing_set_edf(ts, testing_set)) > 0) {
		print_testing_set_edf(testing_set, n_testing_set, out);
		for (i = 0; i < n_testing_set; i++) {
			fprintf(out, "\t dbf(%u) = %f ", testing_set[i], pdf(ts, testing_set[i]));

			if (pdf(ts, testing_set[i]) > testing_set[i]) {
				fprintf(out, "\tNO\n");
				is_schedulable = 0;					
			}
			else
				fprintf(out, "\tOK\n");
		}

		fprintf(out, "\n");
	}

	if(f == NULL) fclose(out);

	return is_schedulable && utilization_factor(ts) < 1;
}
