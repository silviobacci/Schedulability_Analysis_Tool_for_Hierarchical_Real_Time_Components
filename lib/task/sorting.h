#ifndef TASK_SORTING_H
#define TASK_SORTING_H

void sort_taskest_by_id(taskset *ts);
void sort_by_increasing_periods(taskset *ts);
void sort_by_increasing_deadlines(taskset *ts);
void sort_by_increasing_utilization_factor(taskset *ts);
void sort_by_decreasing_periods(taskset *ts);
void sort_by_decreasing_deadlines(taskset *ts);
void sort_by_decreasing_utilization_factor(taskset *ts);

#endif
