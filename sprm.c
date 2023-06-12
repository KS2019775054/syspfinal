#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
	int opt;
	int verbose_flag = 0, interactive_flag = 0;

	static struct option long_options[] = {
		{"verbose", no_argument, 0, 'v'},
		{"interactive", no_argument, 0, 'i'},
		{0,0,0,0}
	};

	int long_index = 0;

	while ((opt = getopt_long(argc, argv, "vi", long_options, &long_index)) != -1) {
		switch (opt) {
			case 'v':
				verbose_flag = 1;
				break;
			case 'i':
				interactive_flag = 1;
				break;
			default:
				printf("사용법: %s [options] <filename(s)>\n", argv[0]);
				printf("\n-v, --verbose\t 삭제되는 대상의 정보를 출력한다.\n");
				printf("-i, --interactive\t 사용자에게 삭제할 것인지 묻는다.\n");
				return 1;
		}
	}

	for (int i = optind; i < argc; i++) {
		if (interactive_flag) {
			char user_input;
			printf("'%s' 파일을 삭제하시겠습니까? (y/n): ", argv[i]);
			scanf(" %c", &user_input);

			if (user_input != 'y' && user_input != 'Y') {
				if (verbose_flag) {
					printf("'%s' 파일 삭제를 건너뜁니다.\n", argv[i]);
				}
				continue;
			}
		}

		if (unlink(argv[i]) == -1) {
			perror(argv[i]);
			continue;
		}

		if (verbose_flag) {
			printf("'%s' 파일이 삭제되었습니다.\n", argv[i]);
		}
	}

	return 0;
}

