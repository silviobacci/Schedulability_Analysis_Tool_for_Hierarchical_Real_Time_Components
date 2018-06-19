#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>
#include <task/scheduling_points.h>
#include <dbf/rm.h>
#include <sbf/sbf.h>

static void h_print(taskset *ts, unsigned int Qs, unsigned int Ts){
	unsigned int sp[MAX_SCHEDULING_POINTS], i;
	int j, n_sp, schedulable;

	for(i = 0; i < ts->size; i++) {
		n_sp = scheduling_points(ts, i, sp, MAX_SCHEDULING_POINTS);
		if (n_sp > 0) {
			printf("The %d-th task has %d scheduling points: ", i, n_sp);
			for (j = 0; j < n_sp; j++)
				printf(" %u", sp[j]);
			printf("\n");

			schedulable = 0;
	
			for (j = 0; j < n_sp; j++) {
				printf("\t dbf(%d) = %u; sbf(%d) = %u\n", sp[j], dbf_rm(ts, i, sp[j]), sp[j], sbf(Qs, Ts, sp[j]));
			
				if (dbf_rm(ts, i, sp[j]) <= sbf(Qs, Ts, sp[j])) 
					schedulable = 1;
			}

			if(schedulable)
				printf("The task set is schedulable with the specified periodic server.\n");
			else
				printf("The task set is NOT schedulable with the specified periodic server.\n");
		}
	}
}


int main(int argc, char *argv[]) {
	FILE *in;
	taskset *ts;
	unsigned int Qs, Ts;
	
	if (argc < 4) {
		fprintf(stderr, "Usage: %s <taskset> <Q> <T>\n", argv[0]);
		return -1;
	}

	in = fopen(argv[1], "r");
	
	if (in == NULL) {
		perror("FOpen");
		return -2;
	}

	Qs = atoi(argv[2]);
	Ts = atoi(argv[3]);

	ts = taskset_load(in);
	if (ts == NULL) {
		fprintf(stderr, "Error loading taskset!\n");
		return -3;
	}
	
	printf("Taskset:\n");
	taskset_print(ts, stdout);
	h_print(ts, Qs, Ts);

	return 0;
}
