#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	int verbose = 0;
	int opt;
	int option_index;
	struct option long_options[] = {
		{"verbose", no_argument, 0, 'v'},
		{0, 0, 0, 0}
	};

	while ((opt = getopt_long(argc, argv, "v", long_options, &option_index)) != -1)
	{
		switch (opt) {
			case 'v':
				verbose = 1;
				break;
			default:
				printf("사용법: %s [-v | --verbose] [source] [destination]\n", argv[0]);
				return 1;
		}
	}


	char *src = argv[optind];
	char *dst = argv[optind + 1];

	if (rename(src, dst) != 0)
	{
		perror("Error moving file");
		return 1;
	}

	if (verbose)
	{
		printf("'%s' -> '%s'\n", src, dst);
	}

	return 0;
}
