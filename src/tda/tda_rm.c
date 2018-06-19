#include <stdio.h>

#include <task/task_io.h>
#include <task/scheduling_points.h>
#include <utilities/prints.h>
#include <dbf/rm.h>
#include <tda/rm.h>

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
	printf("\n----------------------------- TDA RM -------------------------------");
	printf("\n--------------------------------------------------------------------\n\n");
	
	print_taskset(ts, stdout);
	print_tda_rm(ts, stdout);

	if(tda_rm(ts))
		printf("The task set is schedulable under RM.\n");
	else
		printf("The task set is NOT schedulable under RM.\n");

	printf("\n--------------------------------------------------------------------");
	printf("\n--------------------------- END TDA RM -----------------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
