#ifndef VM_SORTING_H
#define VM_SORTING_H

void sort_cpus_by_id(vm *v);
void sort_by_increasing_empty_space(vm *v);
void sort_by_decreasing_empty_space(vm *v);
void sort_by_increasing_empty_space_workload(vm *v);
void sort_by_decreasing_empty_space_workload(vm *v);

#endif
