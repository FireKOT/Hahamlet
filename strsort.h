#ifndef _STRSORT_H
#define _STRSORT_H


typedef int comp_t (const void *param1, const void *param2);


struct line {
    
    char *start = nullptr;
    size_t len = 0;
};


struct text {

    char *source = nullptr;
    line *content = nullptr;

    size_t lines_count = 0;
};


/// param [in]  file_name file name to open
/// param [out] file      struct for writing a file
int GetText         (const char *file_name, text *file);

/// param [in] file_name file name to open
size_t GetFileSize  (const char *file_name);

/// param [out] file      struct for writing a file
/// param [in]  file_size size of file in bytes
/// param [in]  input     input stream
int ReadFile        (text *file, size_t file_size, FILE *input);

/// param [out] struct     for writing a file
/// param [in]  char_count count of chars in file
int UpdateFile      (text *file, size_t char_count);

/// param [out] file 
int SepLines        (text *file);
void MyqSort        (void *start, int count, int size, comp_t *comp);
int sort_partition  (void *start, int hight, int size, int (*comp)(const void*, const void*));
int GlobalCmp       (const char *pr1, const char *pr2, size_t len1, size_t len2, int mod);
int LineCmp         (const void *param1, const void *param2);
int LineReverceCmp  (const void *param1, const void *param2);
int WriteTextinFile (text *file, const char *out_file);
int FreeText        (text *file);


#endif // _STRSORT
