#ifndef TESTING_SET_H
#define TESTING_SET_H

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define MAX_TESTING_SET_SIZE	128		// maximum number of scheduling points

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT TESTING SET EDF: prints all the scheduling points for edf
//------------------------------------------------------------------------------

void print_testing_set_edf(unsigned int *testing_set, unsigned int n_testing_set, FILE *f);

//------------------------------------------------------------------------------
// PRINT TESTING SET FP: prints all the scheduling points for fp
//------------------------------------------------------------------------------

void print_testing_set_fp(unsigned int *testing_set, unsigned int n_testing_set, taskset * ts, unsigned int task_index, FILE *f);

//------------------------------------------------------------------------------
// MERGE TESTING SETS: merge two testing sets returning another one
//------------------------------------------------------------------------------

int merge_testing_sets(unsigned int *ts1, unsigned int ts1_points, unsigned int *ts2, unsigned int ts2_points, unsigned int* points);

//------------------------------------------------------------------------------
// TESTING SET FP: compute the schduling points for fp
//------------------------------------------------------------------------------

int testing_set_fp(taskset *ts, unsigned int *points, unsigned int i);

//------------------------------------------------------------------------------
// TESTING SET EDF: compute the schduling points for edf
//------------------------------------------------------------------------------

int testing_set_edf(taskset *ts, unsigned int *points);

//------------------------------------------------------------------------------
// TESTING SET SBF: compute the schduling points for sbf
//------------------------------------------------------------------------------

int testing_set_sbf(periodic_server *ps, unsigned int *points, unsigned int max);

#endif
