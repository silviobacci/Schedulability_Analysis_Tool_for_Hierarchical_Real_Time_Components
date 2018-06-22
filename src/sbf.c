#include <stdlib.h>
#include <stdio.h>

#include <task/task_io.h>
#include <utilities/utilities.h>
#include <utilities/prints.h>

#define 	START_TIME		0
#define 	END_TIME		100

int main(int argc, char *argv[]) {
	periodic_server * ps;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <Qs> <Ts>\n", argv[0]);
		return -1;
	}
	
	ps = load_periodic_server(atoi(argv[1]), atoi(argv[2]));

	printf("\n--------------------------------------------------------------------");
	printf("\n------------------------------- SBF --------------------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	print_periodic_server(ps, stdout);
	print_sbf(ps, START_TIME, END_TIME, stdout);

	printf("\n--------------------------------------------------------------------");
	printf("\n----------------------------- END SBF ------------------------------");
	printf("\n--------------------------------------------------------------------\n\n");

	return 0;
}
