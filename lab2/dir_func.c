#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "dir_func.h"

void dir_print(DIR *dr) {
    struct dirent *de;
    while ((de = readdir(dr)) != NULL) {
        printf("%s\n", de->d_name);
    }
    free(de);
}

int dir_open(DIR **dr, char *s) {
    if (s == NULL) {
        return -1;
    }
    *dr = opendir(s);
    if (*dr == NULL) {
        return 1;
    }
    chdir(s); //Если не сможет поменять, то и opendir тоже не сможет открыть, а потому можно проверять только 1 из них
    return 0;
}

int iden_com (char *s) {
    int n = strlen(s);
    if (n < 2) {
        return -1;
    }
    char buf[256];
    memcpy(buf, s, n + 1);
    char *q = strtok(buf, " \t");
    if (!strcmp(q, "ls")) {
        q = strtok(NULL, " \t");
        if (q == NULL) {
            return 1;
        }
    }
    if (!strcmp(q, "cd")) {
        return 2;
    }
    if (!strcmp(q, "lsh")) {
        q = strtok(NULL, " \t");
        if (q == NULL) {
            return 3;
        }
    }
    if (!strcmp(q, "cdh")) {
        return 4;
    }
    return 0;
}

void com_ls(DIR *dr) {
    char buf[256];
    getcwd(buf, 256);
    dr = opendir(buf);
    dir_print(dr);
    closedir(dr);
}

int com_cd(DIR **dr, char *s) {
    strtok(s, " \t");
    s = strtok(NULL, " \t");
    if (s == NULL) {
        return 1;
    }
    int q = dir_open(dr, s);
    if (q == -1) {
        return -1;
    }
    if (q) {
        return 2;
    }
    return 0;
}
