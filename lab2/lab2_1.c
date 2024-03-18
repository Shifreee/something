#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "myinput.h"
#include "dir_func.h"
#include "stack_v.h"

int switchcd(DIR *dr, char *s, Stack *history) {
    int q = com_cd(&dr, s);
    switch (q) {
        case 0: {
            dir_print(dr);
            closedir(dr);
            char buf[256];
            getcwd(buf, 256);
            if (push(history, buf)) {
                printf("ERROR of allocation memory, exiting...\n");
                free(s);
                stack_free(history);
                return 1;
            }
        } break;
        case 1: {
            printf("Error of input\n");
        } break;
        case 2: {
            printf("Could not open current directory\n");
        } break;
        case -1: {
            printf("Exiting...\n");
            stack_free(history);
            closedir(dr);
            free(s);
            return 1;
        }
    }
    return 0;
}

int switchcdh(DIR *dr, char *s, Stack *history) {
    char *fub = NULL;
    int q = com_cdh_v(history, s, &fub);
    switch (q) {
        case 0: {
            chdir(fub);
            com_cd(&dr, fub);
            if (push(history, fub)) {
                printf("ERROR of allocation memory, exiting...\n");
                free(s); free(fub);
                stack_free(history);
                return 1;
            }
            com_ls(dr);
        } break;
        case 1: {
            printf("Error of input\n");
        } break;
        case 2: {
            printf("History is empty\n");
        } break;
    }
    free(fub);
    return 0;
}

int main() {
    Stack history;
    history.top = -1;
    char *s = NULL;
    int n;
    DIR *dr = NULL;

    s = myreadline("Enter the name of the folder: ");   //тут по заданию так надо сначало выбрать, а потом выполнять
    if (s == NULL) {
        printf("Exiting...\n");
        free(s);
        stack_free(&history);
        return 1;
    }
    dr = opendir(s);
    chdir(s);
    free(s);
    while (dr == NULL) {
        s = myreadline("Could not open current directory, retry: ");
        if (s == NULL) {
            printf("Exiting...\n");
            closedir(dr);
            stack_free(&history);
            free(s);
            return 1;
        }
        closedir(dr);
        dr = opendir(s);
        chdir(s);
        free(s);
    }
    dir_print(dr);
    closedir(dr);
    while (1) {
        s = myreadline("Enter the comand: ");
        if (s == NULL) {
            printf("Exiting...\n");
            stack_free(&history);
            free(s);
            return 1;
        }
        n = iden_com(s);
        switch (n) {
            case 1: {
                com_ls(dr);
            } break;
            case 2: {
                if (switchcd(dr, s, &history)) {
                    return 1;
                }
            } break;
            case 3: {
                if (stack_print(history)) {
                    printf("History is empty\n");
                }
            } break;
            case 4: {
                if (switchcdh(dr, s, &history)) {
                    return 1;
                }
            } break;
            default: {
                printf("Error of input\n");
            } break;
        }
        free(s);
    }
    closedir(dr);
    free(s);
    stack_free(&history);
    return 0;
}
