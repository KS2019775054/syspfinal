#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	int c;
	int count_characters = 0;
	int current_line = 1;
	int line_number = 0;
	int print_char_count = 0;
	int print_line_number = 0;
	int one_line = 0;
	int no_double_empty_lines = 0;
	int is_empty_line = 0;
	int show_tab_as_caretI = 0;

	struct option long_options[] = {
		{"count", no_argument, 0, 'c'},
		{"one-line", no_argument, 0, 'o'},
		{"line-number", no_argument, 0, 'l'},
		{"no-double-empty-lines", no_argument, 0, 'd'},
		{"show-tab-as-caretI", no_argument, 0, 'T'},
		{0, 0, 0, 0}
	};

	int option_index = 0;
	int option;
	while ((option = getopt_long(argc, argv, "coldT", long_options, &option_index)) != -1) {
		if (option == 'c') {
			print_char_count = 1;
		} else if (option == 'o') {
			one_line = 1;
		} else if (option == 'l') {
			print_line_number = 1;
		} else if (option == 'd') {
			no_double_empty_lines = 1;
		} else if (option == 'T') {
			show_tab_as_caretI = 1;
		} else {
			fprintf(stderr, "사용법 : %s [--count / -c ] [--one-line / -o ] [--line-number / -l] [--no-double-empty-lines / -d ] [--show-tab-as-caretI / -T ] [file]\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	if (optind < argc) {
		fp = fopen(argv[optind], "r");
		if (fp == NULL) {
			perror("Error file");
			exit(EXIT_FAILURE);
		}
	} else {
		fp = stdin;
	}

	c = getc(fp);
	while (c != EOF) {
		if (print_line_number && !line_number) {
			printf("%d: ", current_line);
			line_number = 1;
		}

		if (!isspace(c) || (one_line && c != '\n')) {
			count_characters++;
		}
		if (one_line) {
			if (c == '\n') {
				c = getc(fp);
				continue;
			}
		}

		if (no_double_empty_lines && c == '\n') {
			is_empty_line++;
			if (is_empty_line >= 2) {
				c = getc(fp);
				continue;
			}
		} else {
			is_empty_line = 0;
		}

		if (show_tab_as_caretI && c == '\t') {
			printf("^I");
		} else {
			putc(c, stdout);
		}

		if (c == '\n') {
			line_number = 0;
			current_line++;
		}

		c = getc(fp);
	}
	fclose(fp);

	if (print_char_count) {
		printf("\n글자수는 : %d 개 입니다.\n", count_characters);
	}

	return 0;
}

