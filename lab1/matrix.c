#include <stdio.h>
#include <stdlib.h>
#include "myinput.h"
#include "matrix.h"

int matrix_input(Matrix *matr) {
	matr -> size = 0;
	matr -> lines = NULL;
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
	if (matr -> lines == NULL) {
		printf("Error of memory allocate!\n");
		return -1;
	}

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
		(matr -> lines)[i].size = size;
		(matr -> lines)[i].array = (int *) malloc(size * sizeof(int));
		if ((matr -> lines)[i].array == NULL) {
			printf("Error of memory allocate!\n");
			return -1;
		}

		for (int j = 0; j < size; j++) {
			flag = intinput(((matr -> lines)[i].array) + j);
			if (flag) {
				matr -> size = i;
				free((matr -> lines)[i].array);
				return 1;
			}
		}
	}
    return 0;
}

void matrix_print(Matrix *matr) {
	for (int i = 0; i < (matr -> size); i++) {
		for (int j = 0; j < (matr -> lines)[i].size; j++) {
			printf("%d ", ((matr -> lines)[i].array)[j]);
		}
		printf("\n");
	}
	printf("\n");
}

void matrix_delete(Matrix *matr) {
	for (int i = 0; i < matr -> size; i++) {
		free((matr -> lines)[i].array);
	}
	free(matr -> lines);
}
