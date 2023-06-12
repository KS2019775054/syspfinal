#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("현재 작업 디렉토리 : %s\n", cwd);
	} else {
		perror("getcwd() 에러");
		return 1;
	}
	return 0;
}
