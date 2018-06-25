#ifndef H_ANALYSIS_H
#define H_ANALYSIS_H

unsigned int h_analysis_fp(taskset *ts, periodic_server *ps);
unsigned int h_analysis_edf(taskset *ts, periodic_server *ps);
periodic_server * find_periodic_server(taskset *ts, s_algorithm a);

#endif
