#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "stack_s.h"

int push(Stack *stack, char *s) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return 1;
    }
    int len = strlen(s) + 1;
    char *str = (char *) calloc(len, sizeof(char));
    memcpy(str, s, len);
    newNode->data = str;
    newNode->next = NULL;
    if (stack->top == NULL) {
        stack->top = newNode;
    }
    else {
        newNode->next = stack->top;
        stack->top = newNode;
    }
    return 0;
}

Node *pop(Stack *stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    Node *temp = stack->top;
    stack->top = stack->top->next;
    return temp;
}

int stack_print(Stack *stack) {
	Node *ptr = stack->top;
    if (ptr == NULL) {
        return 1;
    }
    while (ptr) {
        printf("%s\n", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
    return 0;
}

int stack_print_p(Stack *stack) {
	Node *ptr = stack->top;
    while (ptr) {
        printf("%p - %s\n", ptr->data, ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
    return 0;
}

void stack_free(Stack *stack) {
    Node *ptr = stack -> top, *ptr_prev = NULL;
    while (ptr) {
        ptr_prev = ptr;
        ptr = ptr -> next;
        free(ptr_prev->data);
		free(ptr_prev);
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

int com_cdh_l(Stack *stack, char *s, char **res) {
    strtok(s, " \t");
    s = strtok(NULL, " \t");
    if (s == NULL) {
        return 1;
    }
    int n = str_to_unsint(s);
    if (stack->top == NULL) {
        return 2;
    }
    if (n < 1) {
        return 1;
    }
    n = n - 1;
    Node *ptr = stack->top;
    for (int i = 0; i < n; i ++) {
        ptr = ptr -> next;
        if (!ptr) {
            return 1;
        }
    }
    int len = strlen(ptr->data) + 1;
    *res = (char *)calloc(len, sizeof(char));
    memcpy(*res, ptr->data, len);
    return 0;
}
