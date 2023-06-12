#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	long strtol();
	struct option long_options[] = {
		{"verbose", no_argument, NULL, 'v'},
		{0, 0, 0, 0}};

	int option_index = 0;
	int c;
	bool verbose_output = false;
	while ((c = getopt_long(argc, argv, "v", long_options, &option_index)) != -1)
	{
		switch (c)
		{
			case 'v':
				verbose_output = true;
				break;
			default:
				printf("사용법: %s [-v|--verbose] MODE FILE\n", argv[0]);
				return 1;
		}
	}

	if (argc - optind < 2)
	{
		printf("Usage: %s [-v|--verbose] MODE FILE\n", argv[0]);
		return 1;
	}

	int newmode = (int)strtol(argv[optind], (char **)NULL, 8);
	struct stat st;
	if (stat(argv[optind + 1], &st) == -1)
	{
		perror(argv[optind + 1]);
		return 1;
	}

	mode_t oldmode = st.st_mode;
	if (chmod(argv[optind + 1], newmode) == -1)
	{
		perror(argv[optind + 1]);
		return 1;
	}

	if (verbose_output)
	{
		printf("mode of '%s' changed from %o to %o\n", argv[optind + 1], oldmode & 07777, newmode);
	}

	return 0;
}
