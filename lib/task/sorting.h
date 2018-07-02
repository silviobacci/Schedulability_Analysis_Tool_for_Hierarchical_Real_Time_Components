#ifndef TASK_SORTING_H
#define TASK_SORTING_H

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SORT TASKSET BY ID: sort tasks for increasing values of the identifiers
//------------------------------------------------------------------------------

void sort_taskest_by_id(taskset *ts);

//------------------------------------------------------------------------------
// SORT BY INCREASING PERIODS: sort tasks for increasing tasks' periods
//------------------------------------------------------------------------------

void sort_by_increasing_periods(taskset *ts);

//------------------------------------------------------------------------------
// SORT BY INCREASING DEADLINES: sort tasks for increasing tasks' deadlines
//------------------------------------------------------------------------------

void sort_by_increasing_deadlines(taskset *ts);

//------------------------------------------------------------------------------
// SORT BY INCREASING UTILIZATION FACTOR: sort tasks for increasing tasks' U
//------------------------------------------------------------------------------

void sort_by_increasing_utilization_factor(taskset *ts);

//------------------------------------------------------------------------------
// SORT BY DECREASING PERIODS: sort tasks for decreasing tasks' periods
//------------------------------------------------------------------------------

void sort_by_decreasing_periods(taskset *ts);

//------------------------------------------------------------------------------
// SORT BY DECREASING DEADLINES: sort tasks for decreasing tasks' deadlines
//------------------------------------------------------------------------------

void sort_by_decreasing_deadlines(taskset *ts);

//------------------------------------------------------------------------------
// SORT BY DECREASING UTILIZATION FACTOR: sort tasks for decreasing tasks' U
//------------------------------------------------------------------------------

void sort_by_decreasing_utilization_factor(taskset *ts);

#endif
