#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "stack_v.h"

int push(Stack *stack, char *s) {
	int n = strlen(s);
	char *str = (char *)calloc(n + 1, sizeof(char));
	if (str == NULL) {
		return 1;
	}
	memcpy(str, s, n + 1);
    if (stack->top == STACK_LENGTH - 1) {
        free((stack->data)[0]);
        for (int i = 0; i < STACK_LENGTH - 1; i++) {
            (stack->data)[i] = (stack->data)[i + 1];
        }
        (stack->data)[stack->top] = str;
    }
    else {
        (stack->top)++;
        (stack->data)[stack->top] = str;
    }
    return 0;
}

int pop(Stack *stack, char **s) {
    if (stack->top == -1) {
        return 1;
    }
    *s = (stack->data)[stack->top];
    (stack->top)--;
    return 0;
}

int stack_print(Stack stack) {
    if (stack.top == -1) {
        return 1;
    }
    for (int i = stack.top; i >= 0; i--) {
        printf("%s\n", (stack.data)[i]);
    }
    printf("\n");
    return 0;
}

void stack_free(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        free((stack->data)[i]);
    }
}

int str_to_unsint(char *s) {
    int n = 0, a = 0;
    char *q = s;
    while (*q) {
        a = *q - '0';
        if (a > -1 && a < 10) {
            n = n * 10 + a;
        }
        else {
            return -1;
        }
        q++;
    }
    return n;
}

int com_cdh_v(Stack *stack, char *s, char **q) {
    strtok(s, " \t");
    s = strtok(NULL, " \t");
    if (s == NULL) {
        return 1;
    }
    int n = str_to_unsint(s);
    if (stack->top == -1) {
        return 2;
    }
    if (n == -1 || n == 0|| n > stack->top + 1) {
        return 1;
    }
    n = n - 1;
    n = stack->top - n;
    int a = strlen((stack->data)[n]) + 1;
    *q = (char *)realloc(*q, a * sizeof(char));
    memcpy(*q, stack->data[n], a);
    return 0;
}
