#ifndef INPUT_FUNC_H
#define INPUT_FUNC_H
#define STACK_LENGTH 5

typedef struct Stack {
	char *data[STACK_LENGTH];
	int top;
} Stack;

int push(Stack *stack, char *s);
int pop(Stack *stack, char **s);
int stack_print(Stack stack);
void stack_free(Stack *stack);

int str_to_unsint(char *s);
int com_cdh_v(Stack *stack, char *s, char **q);

#endif
