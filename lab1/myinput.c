#include <stdlib.h>
#include <stdio.h>

int intinput(int *n) {
	char check_line;
	do {
		int flag = scanf("%d", n);
		if (flag == -1) {
			return 1;
		}
	} while (scanf("%c", &check_line) && check_line != '\n');
	return 0;
}
