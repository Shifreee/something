#ifndef MATRIX_H
#define MATRIX_H

typedef struct Line {
	int size;
	int *array;
} Line;

typedef struct Matrix {
	int size;
	Line *lines;
} Matrix;

int matrix_input(Matrix *matr);
void matrix_print(Matrix *matr);
void matrix_delete(Matrix *matr);

#endif
