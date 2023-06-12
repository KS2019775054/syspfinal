#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int opt;
	int verbose = 0;
	mode_t mode = 0755;
	struct option long_options[] = {
		{"verbose", no_argument, NULL, 'v'},
		{"mode", required_argument, NULL, 'm'},
		{NULL, 0, NULL, 0}
	};

	while ((opt = getopt_long(argc, argv, "vm:", long_options, NULL)) != -1) {
		switch (opt) {
			case 'v':
				verbose = 1;
				break;
			case 'm':
				mode = strtol(optarg, NULL, 8);
				break;
			default:
				fprintf(stderr, "사용법: %s [-v] [-m mode] directory_name\n", argv[0]);
				exit(-1);
		}
	}

	if (optind >= argc) {
		fprintf(stderr, "사용법: %s [-v] [-m mode] directory_name\n", argv[0]);
		exit(-1);
	}

	int status;

	status = mkdir(argv[optind], mode);

	if (status == -1) {
		perror("mkdir");
		exit(-1);
	} else if (verbose) {
		printf("'%s' 디렉터리가 성공적으로 생성되었습니다. 권한 설정: %04o\n", argv[optind], mode);
	}

	return 0;
}
