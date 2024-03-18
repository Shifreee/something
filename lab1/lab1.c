#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "myinput.h"

Matrix matrix_task(Matrix *matr) {
	Matrix res;
	res.size = matr -> size;
	res.lines = (Line *) malloc((res.size) * sizeof(Line));
	if (res.lines == NULL) {
		res.size = 0;
		return res;
	}
	Line* lines = res.lines;
	for (int k = 0; k < res.size; k++) {
		int num = (matr -> lines)[k].size;
		lines[k].size = num;
		lines[k].array = (int *) malloc(num * sizeof(int));
		if ((lines)[k].array == NULL) {
			res.size = 0;
			return res;
		}
		for (int l = 0; l < num; l++) {
			(lines[k].array)[l] = ((matr -> lines)[k].array)[l];
		}

		int i = -1, j = -1, flagi = 1, flagj = 1;
		for (int l = 1; l < num; l++) {
			if (flagi && (lines[k].array)[l] > (lines[k].array)[l - 1]) {
				i = l;
				flagi = 0;
			}
			if (flagj && (lines[k].array)[num - l] < (lines[k].array)[num - l - 1]) {
				j = num - l;
				flagj = 0;
			}
		}

		if (i != -1 && j != -1) {
			num = (lines[k].array)[i];
			(lines[k].array)[i] = (lines[k].array)[j];
			(lines[k].array)[j] = num;
		}
	}
	return res;
}
////////////////////////////////////////////////////////////////////////////////
int main() {
	Matrix matr;
	int flag = matrix_input(&matr);
	if (flag) {
		printf("\nExiting...\n");
		matrix_delete(&matr);
		return 0;
	}
	Matrix res = matrix_task(&matr);
	if (res.size == 0) {
		printf("Error of memory allocate!\n");
	}
	printf("First matrix:\n");
	matrix_print(&matr);
	printf("Second matrix:\n");
	matrix_print(&res);
	matrix_delete(&matr);
	matrix_delete(&res);
	return 0;
}
