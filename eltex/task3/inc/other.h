#ifndef OTHER_H
#define OTHER_H

#include "editor.h"

#define FNAME_MAX_SIZE 128

void change_theme(WINDOW **win, int h, int w);
void get_help(int h, int w);
void open_file(char *buf, int *sz, int h, int w);
void save_file(char *buf, int sz, int h, int w);

char change_theme_popup(int h, int w);
void help_popup(int h, int w);
char *open_file_popup(int h, int w);
char *save_file_popup(int h, int w);

#endif
