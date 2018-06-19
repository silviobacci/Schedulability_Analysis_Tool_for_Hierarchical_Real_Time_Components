#include <stdio.h>

#include <task/task_io.h>
#include <task/scheduling_points.h>
#include <utilities/prints.h>
#include <dbf/edf.h>
#include <tda/edf.h>

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
	printf("\n----------------------------- TDA EDF ------------------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_taskset(ts, stdout);
	print_tda_rm(ts, stdout);

	if(tda_edf(ts))
		printf("\nThe task set is schedulable under EDF.\n");
	else
		printf("\nThe task set is NOT schedulable under EDF.\n");

	printf("\n--------------------------------------------------------------------");
	printf("\n--------------------------- END TDA EDF ----------------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
