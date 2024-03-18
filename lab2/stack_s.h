#ifndef INPUT_FUNC_H
#define INPUT_FUNC_H
#define STACK_LENGTH 5

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

typedef struct Stack {
	Node *top;
} Stack;


int push(Stack *stack, char *s);
Node *pop(Stack *stack);
int stack_print(Stack *stack);
void stack_free(Stack *stack);

int str_to_unsint(char *s);
int com_cdh_l(Stack *stack, char *s, char **q);

#endif
