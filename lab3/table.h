#ifndef TABLE_H
#define TABLE_H

typedef struct {
    char *key;
    char *par;
    char *info;
} Keyspace;

typedef struct {
    Keyspace *ks;
    int msize; // размер области пространства ключей  !!МАКСИМУМ!!
    int csize; // количество элементов в области пространства ключей !!СКОЛЬКО СЕЙЧАС!!
} Table;

int table_init(Table *table, int msize);
void table_print(Table *table);
void table_free(Table *table);
int table_insert(Table *table, char *key, char *par, char *info);
int table_delete(Table *table, char *key);
Table table_find(Table *table, char *key);
int table_delete_task(Table *table, char *key);
Table table_find_task(Table *table, char *par);

char *myfilereadline_t(FILE *file);
int inputfromfile_t(Table *table);

int compare(const void *a, const void *b);
void table_sort(Table *table);

#endif