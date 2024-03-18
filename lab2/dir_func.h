#ifndef DIR_FUNC_H
#define DIR_FUNC_H

void dir_print(DIR *dr);
int dir_open(DIR **dr, char *s);
int iden_com (char *s);
void com_ls(DIR *dr);
int com_cd(DIR **dr, char *s);
int str_to_unsint(char *s);

#endif
