#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "myinput.h"
#include "dir_func.h"
#include "stack_s.h"

int main() {
    Stack history;
    history.top = NULL;
    char *s = NULL;
    int n;

    DIR *dr = NULL;
    s = myreadline("Enter the name of the folder: ");
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
                int q = com_cd(&dr, s);
                switch (q) {
                    case 0: {
                        dir_print(dr);
                        closedir(dr);
                        char buf[256];
                        getcwd(buf, 256);
                        if (push(&history, buf)) {
                        	printf("ERROR of allocation memory, exiting...\n");
         	                free(s);
         	                stack_free(&history);
         	        		return 0;
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
                        stack_free(&history);
                        closedir(dr);
                        free(s);
                        return 1;
                    }
                }
            } break;
            case 3: {
                if (stack_print(&history)) {
                    printf("History is empty\n");
                }
            } break;
            case 4: {
                char *fub = NULL;
                int q = com_cdh_l(&history, s, &fub);
                switch (q) {
                    case 0: {
                        chdir(fub);
                        com_cd(&dr, fub);
                        //dir_open(&dr, fub);
                         //closedir(dr);
                        if (push(&history, fub)) {
                        	printf("ERROR of allocation memory, exiting...\n");
         	                free(s); free(fub);
         	                stack_free(&history);
         	        		return 0;
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
