//------------------------------------------------------------------------------
// H ANALYSIS:	Contains functions to perform hierarchical sched. analysis.
//------------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <task/structs/task.h>
#include <task/structs/taskset.h>
#include <task/structs/periodic_server.h>
#include <task/task_io.h>
#include <task/testing_set.h>
#include <task/utilities.h>
#include <schedulability/sbf.h>
#include <schedulability/dbf.h>
#include <schedulability/h_analysis.h>

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT H SCHEDULABILITY: print if the taskset is schedulable or not
//------------------------------------------------------------------------------

void print_h_schedulability(unsigned int is_schedulable, s_algorithm a, periodic_server * ps, FILE *f) {
	if(is_schedulable)
		fprintf(f, "\nThe taskset is schedulable under %s with the specified periodic server (Qs = %u, Ts = %u).\n", s_algorithm_to_string(a), ps->Qs, ps->Ts);
	else
		fprintf(f, "\nThe taskset is NOT schedulable under %s with the specified periodic server (Qs = %u, Ts = %u).\n", s_algorithm_to_string(a), ps->Qs, ps->Ts);
}

//------------------------------------------------------------------------------
// H ANALYSIS FP: performs the sched. analysis under fp with the given server
//------------------------------------------------------------------------------

unsigned int h_analysis_fp(taskset *ts, periodic_server *ps, FILE *f) {
	unsigned int testing_set_f[MAX_TESTING_SET_SIZE], testing_set_s[MAX_TESTING_SET_SIZE], testing_set[MAX_TESTING_SET_SIZE], i, is_schedulable = 0;
	int j, n_testing_set, n_testing_set_f, n_testing_set_s;
	FILE *out = (f != NULL) ? f : fopen("./.null", "w");

	for(i = 0; i < ts->size; i++) {
		is_schedulable = 0;
		n_testing_set_f = testing_set_fp(ts, testing_set_f, i);
		n_testing_set_s = testing_set_sbf(ps, testing_set_s, testing_set_f[n_testing_set_f - 1]);

		if ((n_testing_set = merge_testing_sets(testing_set_f, n_testing_set_f, testing_set_s, n_testing_set_s, testing_set)) > 0) {
			print_testing_set_fp(testing_set, n_testing_set, ts, i, out);
			for (j = 0; j < n_testing_set; j++) {
				fprintf(out, "\t dbf(%d) = %u; sbf(%d) = %u ", testing_set[j], workload(ts, i, testing_set[j]), testing_set[j], sbf(ps, testing_set[j]));

				if (workload(ts, i, testing_set[j]) <= sbf(ps, testing_set[j]))  {
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

	if(f == NULL) fclose(out);

	return is_schedulable;
}

//------------------------------------------------------------------------------
// H ANALYSIS EDF: performs the sched. analysis under edf with the given server
//------------------------------------------------------------------------------

unsigned int h_analysis_edf(taskset *ts, periodic_server *ps, FILE *f){
	unsigned int testing_set_e[MAX_TESTING_SET_SIZE], testing_set_s[MAX_TESTING_SET_SIZE], testing_set[MAX_TESTING_SET_SIZE], is_schedulable = 1;
	int i, n_testing_set, n_testing_set_e, n_testing_set_s;
	FILE *out = (f != NULL) ? f : fopen("./.null", "w");
	
	n_testing_set_e = testing_set_edf(ts, testing_set_e);
	n_testing_set_s = testing_set_sbf(ps, testing_set_s, testing_set_e[n_testing_set_e - 1]);

	if ((n_testing_set = merge_testing_sets(testing_set_e, n_testing_set_e, testing_set_s, n_testing_set_s, testing_set)) > 0) {
		print_testing_set_edf(testing_set, n_testing_set, out); 
		for (i = 0; i < n_testing_set; i++) {
			fprintf(out, "\t dbf(%d) = %f; sbf(%d) = %u ", testing_set[i], pdf(ts, testing_set[i]), testing_set[i], sbf(ps, testing_set[i]));

			if (pdf(ts, testing_set[i]) > sbf(ps, testing_set[i]))  {
				fprintf(out, "\tNO\n");
				is_schedulable = 0;					
			}
			else
				fprintf(out, "\tOK\n");
		}
	}

	if(f == NULL) fclose(out);
	
	return is_schedulable;
}

//------------------------------------------------------------------------------
// FIND PERIODIC SERVER: returns the server with min bandwidth able to schedule
//------------------------------------------------------------------------------

periodic_server * find_periodic_server(taskset *ts, s_algorithm a, int cpu, FILE *f) {
	unsigned int start_Qs, end_Qs, Qs, start_Ts, end_Ts, Ts, is_schedulable;
	double temp_bandwith, best_bandwith = 1.0;
	periodic_server * temp_ps = create_empty_ps(), * ps = create_empty_ps();

	if(cpu >= 0)	
		fprintf(f, "Cpu %d : finding a periodic server for the taskset. \n", cpu);
	else
		fprintf(f, "Let's try to find a periodic server that can schedule the entire taskset. \n");

	start_Ts = min_period(ts);
	end_Ts = 2 * max_period(ts);

	for(Ts = start_Ts; Ts <= end_Ts; Ts++) {
		start_Qs = 1;
		end_Qs = (unsigned int) ceil((double) Ts * best_bandwith);
		for(Qs = start_Qs; Qs <= end_Qs; Qs++) {
			temp_ps = load_periodic_server(Qs, Ts);
			temp_bandwith = (double) temp_ps->Qs / temp_ps->Ts;
			is_schedulable = (a == EDF) ? h_analysis_edf(ts, temp_ps, NULL) : h_analysis_fp(ts, temp_ps, NULL);
			if(is_schedulable && temp_bandwith <= best_bandwith) {
				fprintf(f, "\t\t\tPS : (Qs = %u, Ts = %u)\n", temp_ps->Qs, temp_ps->Ts);
				free(ps);	
				ps = temp_ps;
				best_bandwith = temp_bandwith;
			}
			else
				free(temp_ps);
		}
	}
	
	fprintf(f, "\n");

	if(ps->Qs != 0 && ps->Ts != 0) {
		print_periodic_server(ps, f);
		return ps;
	}
	
	fprintf(f, "Sorry, it is not possible to find the desired periodic server.\n");	
	free(ps);	
	return NULL;
}
