#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	int opt;
	int verbose = 0;
	struct option long_options[] = {
		{"verbose", no_argument, NULL, 'v'},
		{NULL, 0, NULL, 0}
	};

	while ((opt = getopt_long(argc, argv, "v", long_options, NULL)) != -1) {
		switch (opt) {
			case 'v':
				verbose = 1;
				break;
			default:
				fprintf(stderr, "사용법: %s [-v] directory_name\n", argv[0]);
				exit(-1);
		}
	}


	int status;

	status = rmdir(argv[optind]);

	if (status == -1) {
		perror("rmdir");
		exit(-1);
	} else if (verbose) {
		printf("'%s' 디렉터리가 성공적으로 삭제되었습니다.\n", argv[optind]);
	}

	return 0;
}
