#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

void display_file_properties(struct stat file_stat);

int compare(const void *a, const void *b) {
	return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char **argv) {
	DIR *dp;
	char *dir;
	struct dirent *d;
	struct stat st;
	char path[BUFSIZ+1];
	int long_option;
	int l_flag = 0;
	int b_flag = 0;
	int a_flag = 0;
	int i_flag = 0;
	int file_count = 0;
	int i;

	static struct option long_options[] = {
		{"long", no_argument, 0, 'l'},
		{"alpha", no_argument, 0, 'b'},
		{"almost-all", no_argument, 0, 'A'},
		{"inode", no_argument, 0, 'i'},
		{0, 0, 0, 0}
	};

	while ((long_option = getopt_long(argc, argv, "lbAi", long_options, 0)) != -1) {
		switch (long_option) {
			case 'l':
				l_flag = 1;
				break;
			case 'b':
				b_flag = 1;
				break;
			case 'A':
				a_flag = 1;
				break;
			case 'i':
				i_flag = 1;
				break;
			default:
				printf("사용법: %s [options] <directory>\n", argv[0]);
				printf("\n-l, --long\t 파일의 자세한 정보를 출력한다.\n");
				printf("-b, --alpha\t 파일 이름을 알파벳 순서대로 정렬하여 출력한다.\n");
				printf("-A, --almost-all\t .(현재 디렉터리)와 ..(상위 디렉터리)를 제외한 거의 모든 항목을 출력한다.\n");
				printf("-i, --inode\t 각 파일의 inode 번호를 함께 출력한다.\n");
		}
	}

	if (argc - optind == 0) {
		dir = ".";
	} else {
		dir = argv[optind];
	}

	if ((dp = opendir(dir)) == NULL) {
		perror(dir);
	}

	while ((d = readdir(dp)) != NULL) {
		if (a_flag && (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)) {
			continue;
		}
		file_count++;
	}

	char **file_list = malloc(file_count * sizeof(char *));
	rewinddir(dp);
	i = 0;

	while ((d = readdir(dp)) != NULL) {
		if (a_flag && (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)) {
			continue;
		}
		file_list[i] = malloc(strlen(d->d_name) + 1);
		strcpy(file_list[i], d->d_name);
		i++;
	}

	if (b_flag) {
		qsort(file_list, file_count, sizeof(char *), compare);
	}

	for (i = 0; i < file_count; i++) {
		if (l_flag) {
			sprintf(path, "%s/%s", dir, file_list[i]);
			if (stat(path, &st) == -1) {
				perror(path);
			} else {
				display_file_properties(st);
			}
		}
		if (i_flag) {
			sprintf(path, "%s/%s", dir, file_list[i]);
			if (stat(path, &st) == -1) {
				perror(path);
			} else {
				printf("%lu ", (unsigned long)st.st_ino);
			}
		}
		printf("%s\n", file_list[i]);
	}

	for (i = 0; i < file_count; i++) {
		free(file_list[i]);
	}
	free(file_list);
	closedir(dp);
	exit(0);
}

void display_file_properties(struct stat file_stat) {
	printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
	printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
	printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
	printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
	printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
	printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
	printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
	printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
	printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

	printf(" %ld ", file_stat.st_nlink);
	printf("%d %d ", file_stat.st_uid, file_stat.st_gid);
	printf("%ld ", file_stat.st_size);

	printf(" ");
}
