#include <stdio.h>

#include <task/task_io.h>
#include <task/testing_set.h>
#include <utilities/prints.h>
#include <dbf/fp.h>
#include <s_analysis/fp.h>

int main(int argc, char *argv[]) {
	FILE *in;
	taskset *ts;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <taskset>\n", argv[0]);
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

	printf("\n--------------------------------------------------------------------");
	printf("\n-------------------- SCHEDULING ANLYSIS FP -------------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_taskset(ts, stdout);
	print_s_analysis_fp(ts, stdout);

	if(s_analysis_fp(ts))
		printf("The task set is schedulable under FP.\n");
	else
		printf("The task set is NOT schedulable under FP.\n");

	printf("\n--------------------------------------------------------------------");
	printf("\n------------------ END SCHEDULING ANLYSIS FP -----------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
