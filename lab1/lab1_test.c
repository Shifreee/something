#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line {
	int size;
	int *array;
} Line;

typedef struct Matrix {
	int size;
	Line *lines;
} Matrix;

////////////////////////////////////////////////////////////////////////////////
char *myreadline(const char *into) {
	printf("%s", into);
	char buf[80] = {0};
	char *res = NULL;
	int len = 0, n;
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0) {
			return NULL;
		}
		else {
			if (n > 0) {
				int chunk_len = strlen(buf);
				int str_len = len + chunk_len;
				res = (char*)realloc(res, str_len + 1);
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
	}
	return res;
}

int intinput(int *n) {
    char cheak_line;
    do {
        int flag = scanf("%d", n);
        if (flag == -1) {
            return 1;
            break;
        }
    } while(scanf("%c", &cheak_line) && cheak_line != '\n');
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////
int matrix_input(Matrix *matr) {
	matr -> size = 0;
	matr -> lines = malloc(1);
	int num;
	printf("Enter the number of lines in the matrix: ");
	int flag = intinput(&num);
	if (flag) {
		return 1;
	}
	while (num < 1) {
		printf("Error of input number, retry: ");
		flag = intinput(&num);
		if (flag) {
			return 1;
		}
	}
	matr -> size = num;
	matr -> lines = (Line *) realloc(matr -> lines, num * sizeof(Line));

	for (int i = 0; i < num; i++) {
		int size;
		printf("Enter the size of line: ");
		flag = intinput(&size);
		if (flag) {
			matr -> size = i;
			return 1;
		}
		while (size < 1) {
			printf("Error of input number, retry: ");
			flag = intinput(&size);
			if (flag) {
				matr -> size = i;
				return 1;
			}
		}
		((matr -> lines) + i) -> size = size;
		((matr -> lines) + i) -> array = (int *) malloc(size * sizeof(int));

		for (int j = 0; j < size; j++) {
			flag = intinput((((matr -> lines) + i) -> array) + j);
			if (flag) {
				matr -> size = i;
				free(((matr -> lines) + i) -> array);
				return 1;
			}
		}
	}
    return 0;
}

void matrix_print(Matrix *matr) {
	for (int i = 0; i < (matr -> size); i++) {
		for (int j = 0; j < ((matr -> lines) + i) -> size; j++) {
			printf("%d ", *((((matr -> lines) + i) -> array) + j));
		}
		printf("\n");
	}
	printf("\n");
}

void matrix_delete(Matrix *matr) {
	for (int i = 0; i < matr -> size; i++) {
		free(((matr -> lines) + i) -> array);
	}
	free(matr -> lines);
	free(matr);
}

Matrix *matrix_task(Matrix *matr) {
	Matrix *res = (Matrix *) malloc(sizeof(Matrix));
	res -> size = matr -> size;
	res -> lines = (Line *) malloc((res -> size) * sizeof(Line));

	for (int k = 0; k < res -> size; k++) {
		int num = ((matr -> lines) + k) -> size;
		((res -> lines) + k) -> size = num;
		((res -> lines) + k) -> array = (int *) malloc(num * sizeof(int));
		for (int l = 0; l < num; l++) {
			*((((res -> lines) + k) -> array) + l) = *((((matr -> lines) + k) -> array) + l);
		}

		int i = -1, j = -1, flagi = 1, flagj = 1;
		for (int l = 1; l < num; l++) {
			if (flagi && (*((((res -> lines) + k) -> array) + l) > *((((res -> lines) + k) -> array) + l - 1))) {
				i = l;
				flagi = 0;
			}
			if (flagj && (*((((res -> lines) + k) -> array) + num - l) < *((((res -> lines) + k) -> array) + num - l - 1))) {
				j = num - l;
				flagj = 0;
			}
		}

		if (i != -1 && j != -1) {
			num = *((((res -> lines) + k) -> array) + i);
			*((((res -> lines) + k) -> array) + i) = *((((res -> lines) + k) -> array) + j);
			*((((res -> lines) + k) -> array) + j) = num;
		}
	}
	return res;
}
////////////////////////////////////////////////////////////////////////////////
int main() {
	Matrix *matr = (Matrix *) malloc(sizeof(Matrix));
	int flag = matrix_input(matr);
	if (flag) {
		printf("\nExiting...\n");
		matrix_delete(matr);
		return 0;
	}
	Matrix *res = matrix_task(matr);
	printf("First matrix:\n");
	matrix_print(matr);
	printf("Second matrix:\n");
	matrix_print(res);
	matrix_delete(matr);
	matrix_delete(res);
	return 0;
}
