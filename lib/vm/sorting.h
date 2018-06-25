#ifndef VM_SORTING_H
#define VM_SORTING_H

void sort_cpus_by_id(vm *v);
static void sort_by_increasing_empty_space(vm *v);
static void sort_by_decreasing_empty_space(vm *v);

#endif
