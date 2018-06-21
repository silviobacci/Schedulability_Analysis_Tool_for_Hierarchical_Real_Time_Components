#include <stdio.h>
#include <string.h>

#include <task/task_io.h>
#include <task/testing_set.h>
#include <utilities/prints.h>
#include <dbf/fp.h>
#include <s_analysis/fp.h>

int main(int argc, char *argv[]) {
	FILE *in;
	taskset *ts;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <taskset> <Algorithm>\n", argv[0]);
		return -1;
	}
	
	if(!(strcmp(argv[2], "rm") == 0 || strcmp(argv[2], "RM") == 0 || strcmp(argv[2], "dm") == 0 || strcmp(argv[2], "DM") == 0)) {
		fprintf(stderr, "Error using the algorithm '%s'. Please choose one between DM or RM\n", argv[2]);
		return -1;
	}

	if ((in = fopen(argv[1], "r")) == NULL) {
		perror("FOpen");
		return -2;
	}

	if ((ts = load_taskset_fp(in, argv[2])) == NULL) {
		fprintf(stderr, "Error loading taskset!\n");
		return -3;
	}

	printf("\n--------------------------------------------------------------------");
	printf("\n-------------------- SCHEDULING ANLYSIS FP -------------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_taskset(ts, stdout);
	print_s_analysis_fp(ts, stdout);

	if(s_analysis_fp(ts))
		printf("The task set is schedulable under %s.\n", argv[2]);
	else
		printf("The task set is NOT schedulable under %s.\n", argv[2]);

	printf("\n--------------------------------------------------------------------");
	printf("\n------------------ END SCHEDULING ANLYSIS FP -----------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
