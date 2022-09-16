#ifndef _STRSORT_H
#define _STRSORT_H


typedef int comp_t (const void *param1, const void *param2);


struct line {
    
    char *start = 0;
    char *end   = 0;
};


struct lyrics {

    char *source = 0;
    line *text = 0;

    int lines_count = 0;
};


int GetText         (const char *file_name, lyrics *text);
int ReadFile        (FILE *input, char *buf);
int SepLines        (line *text, char *file);
void MyqSort        (void *start, int count, int size, comp_t *comp);
int sort_partition  (void *start, int hight, int size, int (*comp)(const void*, const void*));
int linecmp         (const void *param1, const void *param2);
int linercmp        (const void *param1, const void *param2);
int WriteTextinFile (line *text, const char *file);


#endif // _STRSORT
