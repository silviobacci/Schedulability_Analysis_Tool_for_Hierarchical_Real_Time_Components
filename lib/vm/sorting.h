#ifndef VM_SORTING_H
#define VM_SORTING_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SORT CPUS BY ID: sort cpus by increasing identifier values
//------------------------------------------------------------------------------

void sort_cpus_by_id(vm *v);

//------------------------------------------------------------------------------
// SORT CPUS BY INCREASING EMPTY SPACE: sort cpus by increasing empty space
//------------------------------------------------------------------------------

void sort_by_increasing_empty_space(vm *v);

//------------------------------------------------------------------------------
// SORT CPUS BY DECREASING EMPTY SPACE: sort cpus by decreasing empty space
//------------------------------------------------------------------------------

void sort_by_decreasing_empty_space(vm *v);

//------------------------------------------------------------------------------
// SORT CPUS BY INCREASING EMPTY SPACE WORKLOAD: sort using the modified U
//------------------------------------------------------------------------------

void sort_by_increasing_empty_space_workload(vm *v);

//------------------------------------------------------------------------------
// SORT CPUS BY DECREASING EMPTY SPACE WORKLOAD: sort using the modified U
//------------------------------------------------------------------------------

void sort_by_decreasing_empty_space_workload(vm *v);

#endif
