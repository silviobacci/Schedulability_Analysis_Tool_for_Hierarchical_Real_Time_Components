//------------------------------------------------------------------------------
// SORTING:	Contains sorting function for cpus.
//------------------------------------------------------------------------------

#include <stdlib.h>

#include "task/types.h"
#include "task/utilities.h"
#include "vm/types.h"
#include "vm/sorting.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SORT CPUS BY ID: sort cpus by increasing identifier values
//------------------------------------------------------------------------------

void sort_cpus_by_id(vm *v) {
	unsigned int i, j;
	cpu * temp = malloc(sizeof(cpu));
	
	for (i = v->n_cpus - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (v->cpus[j].id > v->cpus[j + 1].id) {
				*temp = v->cpus[j + 1];
				v->cpus[j + 1] = v->cpus[j];
				v->cpus[j] = *temp;
			}
	free(temp);
}

//------------------------------------------------------------------------------
// SORT CPUS BY INCREASING EMPTY SPACE: sort cpus by increasing empty space
//------------------------------------------------------------------------------

void sort_by_increasing_empty_space(vm *v) {
	unsigned int i, j;
	cpu * temp = malloc(sizeof(cpu));
	
	for (i = v->n_cpus - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (v->cpus[j].u < v->cpus[j + 1].u) {
				*temp = v->cpus[j + 1];
				v->cpus[j + 1] = v->cpus[j];
				v->cpus[j] = *temp;
			}
	free(temp);
}

//------------------------------------------------------------------------------
// SORT CPUS BY DECREASING EMPTY SPACE: sort cpus by decreasing empty space
//------------------------------------------------------------------------------

void sort_by_decreasing_empty_space(vm *v) {
	unsigned int i, j, n_cpus = 0;
	cpu * temp = malloc(sizeof(cpu));

	sort_by_increasing_empty_space(v);

	for (i = 0; i < v->n_cpus; i++)
		if(v->cpus[i].u > 0)
			n_cpus++;

	if(n_cpus == 0)
		n_cpus++;
	
	for (i = n_cpus - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (v->cpus[j].u > v->cpus[j + 1].u) {
				*temp = v->cpus[j + 1];
				v->cpus[j + 1] = v->cpus[j];
				v->cpus[j] = *temp;
			}
	free(temp);
}

//------------------------------------------------------------------------------
// SORT CPUS BY INCREASING EMPTY SPACE WORKLOAD: sort using the modified U
//------------------------------------------------------------------------------

void sort_by_increasing_empty_space_workload(vm *v) {
	unsigned int i, j;
	cpu * temp = malloc(sizeof(cpu));
	
	for (i = v->n_cpus - 1; i > 0; i--)
		for (j = 0; j < i; j++) 
			if (utilization_factor_modified(v->cpus[j].ts) < utilization_factor_modified(v->cpus[j + 1].ts)) {
				*temp = v->cpus[j + 1];
				v->cpus[j + 1] = v->cpus[j];
				v->cpus[j] = *temp;
			}
	free(temp);
}

//------------------------------------------------------------------------------
// SORT CPUS BY DECREASING EMPTY SPACE WORKLOAD: sort using the modified U
//------------------------------------------------------------------------------

void sort_by_decreasing_empty_space_workload(vm *v) {
	unsigned int i, j, n_cpus = 0;
	cpu * temp = malloc(sizeof(cpu));

	sort_by_increasing_empty_space_workload(v);

	for (i = 0; i < v->n_cpus; i++)
		if(v->cpus[i].ts->size > 0)
			n_cpus++;

	if(n_cpus == 0)
		n_cpus++;
	
	for (i = n_cpus - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (utilization_factor_modified(v->cpus[j].ts) > utilization_factor_modified(v->cpus[j + 1].ts)) {
				*temp = v->cpus[j + 1];
				v->cpus[j + 1] = v->cpus[j];
				v->cpus[j] = *temp;
			}
	free(temp);
}
