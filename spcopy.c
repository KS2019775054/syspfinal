#include <stdio.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
	char c;
	FILE *fp1, *fp2;
	int verbose = 0;
	int interactive = 0;
	int opt;
	static struct option long_options[] = {
		{"verbose", no_argument, NULL, 'v'},
		{"interactive", no_argument, NULL, 'i'},
		{NULL, 0, NULL, 0}
	};

	while ((opt = getopt_long(argc, argv, "vi", long_options, NULL)) != -1) {
		switch (opt) {
			case 'v':
				verbose = 1;
				break;
			case 'i':
				interactive = 1;
				break;
			default:
				fprintf(stderr, "사용법: %s [-v] [-i] 파일1 파일2\n", argv[0]);
				return 1;
		}
	}

	if (argc - optind != 2) {
		fprintf(stderr, "사용법: %s [-v] [-i] 파일1 파일2\n", argv[0]);
		return 1;
	}

	if (interactive) {
		char confirm;
		printf("파일 복사를 진행하시겠습니까? (y/n): ");
		scanf(" %c", &confirm);
		if (confirm != 'y' && confirm != 'Y') {
			printf("복사를 취소합니다.\n");
			return 0;
		}
	}

	fp1 = fopen(argv[optind], "r");
	if (fp1 == NULL) {
		fprintf(stderr, "파일 %s 열기 오류\n", argv[optind]);
		return 2;
	}

	fp2 = fopen(argv[optind + 1], "w");

	if (verbose) {
		printf("복사 시작: %s -> %s\n", argv[optind], argv[optind + 1]);
	}

	while ((c = fgetc(fp1)) != EOF) {
		fputc(c, fp2);
	}

	fclose(fp1);
	fclose(fp2);

	if (verbose) {
		printf("복사 완료: %s -> %s\n", argv[optind], argv[optind + 1]);
	}

	return 0;
}
