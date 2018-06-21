#ifndef SCHEDULING_POINTS_H
#define SCHEDULING_POINTS_H

#define MAX_SCHEDULING_POINTS	128

int testing_set_fp(taskset *ts, unsigned int *points, unsigned int i);
int testing_set_edf(taskset *ts, unsigned int *points);

#endif
