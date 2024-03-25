#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myinput.h"
#include "table.h"

int table_init(Table *table, int msize) {
    table->msize = msize;
    table->csize = 0;
    table->ks = (Keyspace *) calloc(msize, sizeof(Keyspace));
    if (!(table->ks)) {
        return 1;
    }
    return 0;
}

void table_print(Table *table) {
    printf("key | par | info\n");
    for (int i = 0; i < table->csize; i++) {
        printf("%s | ", table->ks[i].key);
        printf("%s | ", table->ks[i].par);
        printf("%s\n", table->ks[i].info);
    }
}

void table_free(Table *table) {
    for (int i = 0; i < table->csize; i++) {
        free(table->ks[i].key);
        free(table->ks[i].par);
        free(table->ks[i].info);
    }
    free(table->ks);
}

int table_insert(Table *table, char *key, char *par, char *info) {
    if (table->csize >= table->msize) {
        return 2;
    }

    int flag_key = 0;
    if (par == NULL) {
        for (int i = 0; i < table->csize; i++) {
            if (!strcmp((table->ks[i]).key, key)) {
                flag_key = 1;
            }
        }
        if (flag_key) {
            return 5; //такой ключ уже есть
        }
    }
    else {
        int flag_par = 0;
        for (int i = 0; i < table->csize; i++) {
            if (!strcmp((table->ks[i]).key, par)) {
                flag_par = 1;
            }
            if (!strcmp((table->ks[i]).key, key)) {
                flag_key = 1;
            }
        }
        if (!flag_par && flag_key) {
            return 3; //оба неправильные 
        }
        if (!flag_par) {
            return 4; //нет элемента родителя;
        }
        if (flag_key) {
            return 5; //такой ключ уже есть
        }
    }
    int size = strlen(key);///////////////////////////
    char *s = (char *) calloc (size + 1, sizeof(char));
    if (s == NULL) {
        return 1;
    }
    memcpy(s, key, size + 1);
    (table->ks[table->csize]).key = s;

    if (par) {//////////////////////////////////////
        size = strlen(par);
        s = (char *) calloc (size + 1, sizeof(char));
        if (s == NULL) {
            free((table->ks[table->csize]).key);
            return 1;
        }
        memcpy(s, par, size + 1);
        (table->ks[table->csize]).par = s;
    }
    else {
        (table->ks[table->csize]).par = NULL;
    }

    size = strlen(info);////////////////////////////
    s = (char *) calloc (size + 1, sizeof(char));
    if (s == NULL) {
        free((table->ks[table->csize]).key);
        free((table->ks[table->csize]).par);
        return 1;
    }
    memcpy(s, info, size + 1);
    (table->ks[table->csize]).info = s;
    
    (table->csize)++;
    return 0;
}

int table_delete(Table *table, char *key) {
    if (key == NULL) { return -1;}
    for (int i = 0; i < table->csize; i++) {
        if (!strcmp(table->ks[i].key, key)) {
            for (int j = 0; j < table->csize; j++) {
                if (table->ks[j].par && !strcmp(table->ks[j].par, key)) {
                    free(table->ks[j].par);
                    table->ks[j].par = NULL;
                }
            }
            free(table->ks[i].key);
            free(table->ks[i].par);
            free(table->ks[i].info);
            (table->csize)--;
            if (i == table->csize) {
                return 0;
            }
            table->ks[i].key = table->ks[table->csize].key;
            table->ks[i].par = table->ks[table->csize].par;
            table->ks[i].info = table->ks[table->csize].info;
            table->ks[table->csize].key = NULL;
            table->ks[table->csize].par = NULL;
            table->ks[table->csize].info = NULL;
            return 0;
        }
    }
    return 1; //ничего не нашёл
}

Table table_find(Table *table, char *key) {
    Table res;
    res.csize = 0; res.msize = 0;
    if (!key) {
        res.ks = NULL;
        return res;
    }
    res.ks = (Keyspace *) calloc(table->csize, sizeof(Keyspace)); // добавить проверку
    if (res.ks == NULL) {
        return res;
    }
    for (int i = 0; i < table->csize; i++) {
        if (!strcmp((table->ks[i]).key, key)) {
            int len_info = strlen(table->ks[i].info); //копируем info и key
            int len_key = strlen(table->ks[i].key);
            res.ks[res.csize].info = (char *) calloc(len_info + 1, sizeof(char));
            res.ks[res.csize].key = (char *) calloc(len_key + 1, sizeof(char));
            memcpy(res.ks[res.csize].info, table->ks[i].info, len_info + 1);
            memcpy(res.ks[res.csize].key, table->ks[i].key, len_key + 1);
            int len_par = 0; // отдельно смотрим par, так как может быть NULL
            res.ks[res.csize].par = NULL;
            if (table->ks[i].par) {
                len_par = strlen(table->ks[i].par);
                res.ks[res.csize].par = (char *) calloc(len_par + 1, sizeof(char));
                memcpy(res.ks[res.csize].par, table->ks[i].par, len_par + 1);
            }
            (res.msize)++; (res.csize)++;
        }
    }
    if (res.csize == 0) {
        free(res.ks);
        res.ks = NULL;
    }
    else {
        res.ks = realloc(res.ks, res.csize * sizeof(Keyspace)); // добавить проверку
    }
    return res;
}

int table_delete_task(Table *table, char *key) {
    if (key == NULL) { return -1;}
    for (int i = 0; i < table->csize; i++) {
        if (!strcmp(table->ks[i].key, key)) {
            for (int j = 0; j < table->csize; j++) {
                if (table->ks[j].par && !strcmp(table->ks[j].par, key)) {
                    return 2; //нашёл что он чей-то родитель
                }
            }
            free(table->ks[i].key);
            free(table->ks[i].par);
            free(table->ks[i].info);
            (table->csize)--;
            if (i == table->csize) {
                return 0;
            }
            table->ks[i].key = table->ks[table->csize].key;
            table->ks[i].par = table->ks[table->csize].par;
            table->ks[i].info = table->ks[table->csize].info;
            table->ks[table->csize].key = NULL;
            table->ks[table->csize].par = NULL;
            table->ks[table->csize].info = NULL;
            return 0;
        }
    }
    return 1; //ничего не нашёл
}

Table table_find_task(Table *table, char *par) {
    Table res;
    res.csize = 0; res.msize = 0;
    res.ks = (Keyspace *) calloc(table->csize, sizeof(Keyspace)); // добавить проверку
    if (res.ks == NULL) {
        res.csize = 1;
        return res;
    }
    if (!par) {
        for (int i = 0; i < table->csize; i++) {
            if (table->ks[i].par == par) {
                int len_info = strlen(table->ks[i].info);
                int len_key = strlen(table->ks[i].key);
                res.ks[res.csize].info = (char *) calloc(len_info + 1, sizeof(char));
                res.ks[res.csize].key = (char *) calloc(len_key + 1, sizeof(char));
                memcpy(res.ks[res.csize].info, table->ks[i].info, len_info + 1);
                memcpy(res.ks[res.csize].key, table->ks[i].key, len_key + 1);
                res.ks[res.csize].par = NULL;
                (res.msize)++; (res.csize)++;
            }
        }
    }
    else {
        for (int i = 0; i < table->csize; i++) {
            if (table->ks[i].par && !strcmp((table->ks[i]).par, par)) {
                int len_info = strlen(table->ks[i].info);
                int len_key = strlen(table->ks[i].key);
                int len_par = strlen(table->ks[i].par);
                res.ks[res.csize].info = (char *) calloc(len_info + 1, sizeof(char));
                res.ks[res.csize].key = (char *) calloc(len_key + 1, sizeof(char));
                res.ks[res.csize].par = (char *) calloc(len_par + 1, sizeof(char));
                memcpy(res.ks[res.csize].info, table->ks[i].info, len_info + 1);
                memcpy(res.ks[res.csize].key, table->ks[i].key, len_key + 1);
                memcpy(res.ks[res.csize].par, table->ks[i].par, len_par + 1);
                (res.msize)++; (res.csize)++;
            }
        }
    }
    if (res.csize == 0) {
        free(res.ks);
        res.ks = NULL;
    }
    else {
        res.ks = realloc(res.ks, res.csize * sizeof(Keyspace)); // добавить проверку
    }
    return res;
}
///////////////////////////////////////////////////////

char *myfilereadline_t(FILE *file) {
	char buf[80] = {0};
	char *res = NULL;
	int len = 0, n;
	do {
		n = fscanf(file, "%80[^\n]", buf);
		if (n < 0) {
			return NULL;
		}
		else {
			if (n > 0) {
				int chunk_len = strlen(buf);
				int str_len = len + chunk_len;
				res = (char*)realloc(res, str_len + 1);
				memcpy(res + len, buf, chunk_len);
				len = str_len;
			}
			else {
				fscanf(file, "%*c");
			}
		}
	} while (n > 0);
	if (len > 0) {
		res[len] = '\0';
	}
	else {
		res = (char*)calloc(1, sizeof(char));
	}
	return res;
}

int inputfromfile_t(Table *table) {
    char *filename_input = myreadline("Enter the name of file: ");
    if (filename_input == NULL) {
        free(filename_input);
        return 1;
    }
    FILE *file_t = NULL;
    file_t = fopen(filename_input, "r");
    while (file_t == NULL) {
        free(filename_input);
        filename_input = myreadline("File opening error, try again: ");
        if (filename_input == NULL) {
            free(filename_input);
            //fclose(file_t);
            return 1;
        }
        file_t = fopen(filename_input, "r");
    }
    int len = 0;
    fscanf(file_t, "%d%*c", &len);
    if (len > table->msize) {
        printf("Not all elements will be read\n");
        len = table->msize;
    }
    int read = 0;
    char *key = NULL;
    char *par = NULL;
    char *info = NULL;
    for (int i = 0; i < len; i++){
        key = myfilereadline_t(file_t);
        if (key[0] == '\0' || key == NULL) {
            printf("End of the open file. %d values have been read\n", read);
            free(filename_input);
            fclose(file_t);
            return 0;
        }
        par = myfilereadline_t(file_t);
        if (par == NULL) {
            printf("End of the open file. %d values have been read\n", read);
            free(key);
            free(filename_input);
            fclose(file_t);
            return 0;
        }
        info = myfilereadline_t(file_t);
        if (info[0] == '\0' || info == NULL) {
            printf("End of the open file. %d values have been read\n", read);
            free(key);
            free(par);
            free(filename_input);
            fclose(file_t);
            return 0;
        }
        if (par[0] == '\0') {
            free(par);
            par = NULL;
        }
        if (table_insert(table, key, par, info)) {
            read--;
        }
        read++;
        free(key); free(par); free(info);
    }
    free(filename_input);
    fclose(file_t);
    printf("%d values have been read\n", read);
    return 0;
}
///////////////////////////////////////////////////////////
int compare(const void *a, const void *b) {
    if (((Keyspace*) a)->par) {
        if (((Keyspace*) b)->par) {
            return strcmp(((Keyspace*) a)->par, ((Keyspace*) b)->par);
        }
        else {
            return 1;
        }
    }
    else {
        if (((Keyspace*) b)->par) {
            return -1;
        }
        else {
            return 0;
        }
    }
}

void table_sort(Table *table) {
    qsort(table->ks, table->csize, sizeof(Keyspace), compare);
}
