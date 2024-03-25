#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myinput.h"
#include "table.h"

int dialog (const char *messeges[], int size_messeges) {
    printf("----------\n");
    for (int i = 0; i < size_messeges; i++) {
        printf("%s\n", messeges[i]);
    }
    printf("That need to be done: ");
    int num;
    if (intinput(&num)) {
        return 0;
    }
    while (num < 0 || num >= size_messeges) {
        printf("Error of input, retry: ");
        if (intinput(&num)) {
            return 0;
        }
    }
    return num;
}

int Add_element(Table *table) {
    char *key = myreadline("Enter element's key: ");
    if (key == NULL) {
        return 0;
    }
    char *par = myreadline("Enter element's parent (press Enter if there is no parent): ");
    if (par == NULL) {
        free(key);
        return 0;
    }
    if (par[0] == '\0') {
        free(par); par = NULL;
    }
    char *info = myreadline("Enter element's information: ");
    if (info == NULL) {
        free(key); free(par);
        return 0;
    }
    
    //int n = table_insert(table, key, par, info);
    switch (table_insert(table, key, par, info)) {
        case 0: {
            free(key); free(par); free(info);
            return 1;
        } break;
        case 1: {
            printf("Error of memory allocation\n");
        } break;
        case 2: {
            printf("The table is already filled in\n");
        } break;
        case 3: {
            printf("There is no such parent in the table and this key is already in the table\n");
        } break;
        case 4: {
            printf("There is no such parent in the table\n");
        } break;
        case 5: {
            printf("This key is already in the table\n");
        } break;
        default: {
            //всё вынесено
        } break;
    }
    free(key); free(par); free(info);
    return 1;
}

int Delete_element(Table *table) {
    char *key = myreadline("Enter element's key: ");
    if (key == NULL) {
        free(key);
        return 0;
    }
    switch (table_delete(table, key)) {
        case 0: {
            //всё вынесено
        } break;
        case 1: {
            printf("There is no element with this key\n");
        } break;
        case -1: {
            free(key);
            return 0; //значит что key NULL, то-есть EOF
        } break;
        default: {
            //всё вынесено
        } break;
    }
    free(key);
    return 1;
}

int Find_element(Table *table) {
    char *key = myreadline("Enter element's key: ");
    if (key == NULL) {
        free(key);
        return 0;
    }
    Table res = table_find(table, key);
    if (res.ks == NULL) {
        if (key == NULL) {
            free(key);
            return 0;
        }
        if (res.csize != 0) {
            printf("Error of memory allocation\n");
            free(key);
            return 1;
        }
    }
    table_print(&res);
    table_free(&res);
    free(key);
    return 1;
}

int Print_table(Table *table) {
    table_print(table);
    return 1;
}

int Import_data_from_file(Table *table) {
    if (table->csize != 0) {
        for (int i = 0; i < table->csize; i++) {
            free(table->ks[i].key);
            free(table->ks[i].par);
            free(table->ks[i].info);
        }
        table->csize = 0;
    }
    switch (inputfromfile_t(table)) {
        case 1: {
            return 0;
        } break;
        case 0: {
            return 1;
        } break;
        default: {
            return 1;
        } break;
    }
    return 1;
}

int Delete_element_task(Table *table) {
    char *key = myreadline("Enter element's key: ");
    if (key == NULL) {
        free(key);
        return 0;
    }
    switch (table_delete_task(table, key)) {
        case -1: {
            return 0;
        } break;
        case 0: {
            //всё вынесено
        } break;
        case 1: {
            printf("There is no element with this key\n");
        } break;
        case 2: {
            printf("This element is someone's parent\n");
        } break;
        default: {
            //всё вынесено
        } break;
    }
    free(key);
    return 1;
}

int Find_element_task(Table *table) {
    char *par = myreadline("Enter element's parent (press Enter if there is no parent): ");
    if (par == NULL) {
        return 0;
    }
    if (par[0] == '\0') {
        free(par);
        par = NULL;
    }
    Table res = table_find_task(table, par);
    if (res.ks == NULL) {
        if (res.csize != 0) {
            printf("Error of memory allocation\n");
        }
        else {
            printf("There is no such parent\n");
        }
        free(par);
        return 1;
    }
    table_print(&res);
    table_free(&res);
    free(par);
    return 1;
}

int main() {
    Table table;
    int n = 0;
    printf("Enter size of table: ");
    while (n < 1) {
        if (intinput(&n)) {
            printf("Exiting...\n");
            return 1;
        }
        if (n < 1) {
            printf("Error of input, retry: ");
        }
    }
    if (table_init(&table, n)) {
        printf("Error of memory allocation\n");
        return 1;
    }
    const char *messeges[] = {"0) Quit", "1) Add a new element", "2) Delete an element", "3) Find an element", "4) Show the table", "5) Importing data from a text file", "6) Delete an element (individual task)", "7) Find an element (individual task)"};
    const int size_messeges = sizeof(messeges) / sizeof(messeges[0]);
    int (*funcs[])(Table *) = {NULL, Add_element, Delete_element, Find_element, Print_table, Import_data_from_file, Delete_element_task, Find_element_task};
    n = dialog(messeges, size_messeges);
    while (n) {
        if (!funcs[n](&table) || n == -1) {
            break;
        }
        table_sort(&table);
        n = dialog(messeges, size_messeges);
    }
    printf("Exiting...\n");
    table_free(&table);
    return 0;
}
