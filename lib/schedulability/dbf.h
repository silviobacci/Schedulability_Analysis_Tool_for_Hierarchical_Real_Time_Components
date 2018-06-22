#ifndef DBF_H
#define DBF_H

double ulub_fp(taskset *ts);
int ulub_edf();
unsigned int workload(taskset *ts, unsigned int n, unsigned int t);
double dbf(taskset *ts, unsigned int t);

#endif
