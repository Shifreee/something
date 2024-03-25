#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

char *myreadline(const char *into) {
	printf("%s", into);
	char buf[80] = {0};
	char *res = NULL;
	int len = 0, n;
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0) {
			free(res);
			return NULL;
		}
		else {
			if (n > 0) {
				int chunk_len = strlen(buf);
				int str_len = len + chunk_len;
				res = (char*)realloc(res, str_len + 1);
				if (res == NULL) {
					return NULL;
				}
				memcpy(res + len, buf, chunk_len);
				len = str_len;
			}
			else {
				scanf("%*c");
			}
		}
	} while (n > 0);
	if (len > 0) {
		res[len] = '\0';
	}
	else {
		res = (char*)calloc(1, sizeof(char));
		if (res == NULL) {
			return NULL;
		}
	}
	return res;
}
