#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>
#include <utilities/utilities.h>
#include <utilities/prints.h>
#include <schedulability/h_analysis.h>

int main(int argc, char *argv[]) {
	FILE *in;
	taskset *ts;
	periodic_server * ps;
	s_algorithm algorithm;
	unsigned int is_schedulable;
	
	if (argc < 5) {
		fprintf(stderr, "Usage: %s <taskset> <Qs> <Ts> <algorithm>\n", argv[0]);
		return -1;
	}

	if ((in = fopen(argv[1], "r")) == NULL) {
		perror("FOpen");
		return -2;
	}
	
	if ((ts = load_taskset(in)) == NULL) {
		fprintf(stderr, "Error loading taskset!\n");
		return -3;
	}
	
	ps = load_periodic_server(atoi(argv[2]), atoi(argv[3]));
	
	algorithm = atoi(argv[4]);
	
	if (algorithm < RM || algorithm > EDF) {
		fprintf(stderr, "Error loading algorithm!\n");
			return -3;
	}
	
	switch(algorithm) {
		case RM:
			sort_by_increasing_periods(ts);
			break;
		case DM:
			sort_by_increasing_deadlines(ts);
			break;
		case EDF:
			break;
	}
	
	printf("\n--------------------------------------------------------------------");
	printf("\n---------------- HIERARCHICAL SCHEDULING ANALYSIS ------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_taskset(ts, stdout);
	print_periodic_server(ps, stdout);
	
	if(algorithm == EDF) {
		print_h_analysis_edf(ts, ps, stdout);
		is_schedulable = h_analysis_edf(ts, ps);
	}
	else {
		print_h_analysis_fp(ts, ps, stdout);
		is_schedulable = h_analysis_fp(ts, ps);
	}
	
	print_h_schedulability(is_schedulable, algorithm, ps, stdout);

	if(!is_schedulable){
		print_find_periodic_server(stdout);
		ps = find_periodic_server(ts);
		print_periodic_server(ps, stdout);
		if(algorithm == EDF) 
			print_h_analysis_edf(ts, ps, stdout); 
		else 
			print_h_analysis_fp(ts, ps, stdout);
	}

	printf("\n--------------------------------------------------------------------");
	printf("\n-------------- END HIERARCHICAL SCHEDULING ANALYSIS ----------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
