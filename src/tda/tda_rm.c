#include <stdio.h>

#include <task/task_io.h>
#include <task/scheduling_points.h>
#include <dbf/rm.h>
#include <tda/rm.h>

static void stats_print(taskset *ts) {
	unsigned int sp[MAX_SCHEDULING_POINTS], i;
	int j, n_sp;
	
	for(i = 0; i < ts->size; i++) {
		n_sp = scheduling_points(ts, i, sp, MAX_SCHEDULING_POINTS);
		
		if (n_sp > 0) {
			printf("The %d° task has %d scheduling points:", i + 1, n_sp);
			for (j = 0; j < n_sp; j++)
				printf(" %u", sp[j]);
			printf("\n");
	
			for (j = 0; j < n_sp; j++)
				printf("\tdbf(%u) = %u\n", sp[j], dbf_rm(ts, i, sp[j]));
			printf("\n");
		}
	}
}

int main(int argc, char *argv[]) {
	FILE *in;
	taskset *ts;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <taskset>\n", argv[0]);
		return -1;
	}

	in = fopen(argv[1], "r");
	if (in == NULL) {
		perror("FOpen");
		return -2;
	}

	ts = taskset_load(in);
	if (ts == NULL) {
		fprintf(stderr, "Error loading taskset!\n");
		return -3;
	}
	
	printf("Taskset:\n");
	taskset_print(ts, stdout);
	stats_print(ts);

	if(tda_rm(ts))
		printf("The task set is schedulable under RM.\n");
	else
		printf("The task set is NOT schedulable under RM.\n");

	return 0;
}
