#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include "config.h"
#include "general.h"
#include "strsort.h"

#define BUF_SIZE 10

int GetText (const char *file_name, lyrics *file) {

    if (!file_name) {
        ERR_MSG(ERR_NULL_PTR);
        return -1;
    }

    FILE *input = fopen(file_name, "r");
    if (!input) {
        ERR_MSG(ERR_NULL_PTR);
        return -1;
    }

    struct stat file_stats;                         //why i need to write "struct"
    int status = stat(file_name, &file_stats);
    if (status == -1) {
        ERR_MSG(ERR_NULL_PTR);
        return -1;
    }

    file->source = (char*) calloc(file_stats.st_size / sizeof(char) + BUF_SIZE, sizeof(char));
    if (!file->source) {
        ERR_MSG(ERR_NULL_PTR);
        return -1;
    }

    int lines_count = ReadFile(input, file->source);

    file->text = (line*) calloc(lines_count + BUF_SIZE, sizeof(line));
    if (!file->text) {
        ERR_MSG(ERR_NULL_PTR);
        return -1;
    }

    file->lines_count = SepLines(file->text, file->source);

    fclose(input);
    return 0;
}

int ReadFile (FILE *input, char *buf) {

    if (!input || !buf) {
        ERR_MSG(ERR_NULL_PTR);
        return EOF;
    }

    int c = 0, lines_count = 0;
    int i = 0;
    buf[++i] = '\0';
    while ((c = getc(input)) != EOF) {
        if (c != '\r') {
            if (c != '\n') {
                buf[i] = (char) c;
            }
            else {
                buf[i] = '\0';
                lines_count++;
            }

            i++;
        }
    }
    buf[i++] = '\0';
    buf[i] = EOF;

    return lines_count;
}

int SepLines (line *text, char *file) {

    if (!text || !file) {
        ERR_MSG(ERR_NULL_PTR);
        return -1;
    }

    int lines_count = 0;
    int i = 0;
    for (i = 0; *file != EOF; i++, file++) {
        if (*file != '\0') {
            text[i].start = file;
            lines_count++;
            file++;
        }
        else {
            i--;
            continue;
        }

        while (*file != '\0') {
            text[i].end = file;
            file++;
        } 
        //text[i].end = --file;
        //file++;
    }
    text[i].start = NULL;
    text[i].end = NULL;

    return lines_count;
}

void MyqSort (void *start, int count, int size, int (*comp)(const void *param1, const void *param2)) {

    char *mas = (char*) start;

    if (count > 1) {
        int p = sort_partition(mas, count-1, size, comp);
        MyqSort(mas, p-1, size, comp);
        MyqSort(mas + (p+1)*size, count - (p+1), size, comp);
    }
}

int sort_partition (void *start, int hight, int size, comp_t *comp) {

    char *mas = (char*) start;

    int i = 0;
    for (int j = 0; j < hight; j++) {
        if (comp(mas + j*size, mas + hight*size) <= 0) {
            swap(mas + i*size, mas + j*size, size);
            i++;
        }
    }
    swap(mas + i*size, mas + hight*size, size);

    return i;
}

int linecmp (const void *param1, const void *param2) {

    char *a_start = ((const line*) param1)->start;
    char *b_start = ((const line*) param2)->start;
    char *a_end   = ((const line*) param1)->end;
    char *b_end   = ((const line*) param2)->end;

    while (!isalnum(*a_start) && a_start != a_end + 1) {
        a_start++;
    }
    while (!isalnum(*b_start) && b_start != b_end + 1) {
        b_start++;
    }
    
    for ( ;tolower(*a_start) == tolower(*b_start); a_start++, b_start++) {
        if (a_start == a_end + 1) {
            return 0;
        }
    }
    
    return tolower(*a_start) - tolower(*b_start);
}

int linercmp (const void *param1, const void *param2) {

    char *a_start = ((const line*) param1)->start;
    char *b_start = ((const line*) param2)->start;
    char *a_end   = ((const line*) param1)->end;
    char *b_end   = ((const line*) param2)->end;

    while (!isalnum(*a_end) && a_end != a_start - 1) {
        a_end--;
    }
    while (!isalnum(*b_end) && b_end != b_start - 1) {
        b_end--;
    }

    for ( ; tolower(*a_end) == tolower(*b_end); a_end--, b_end--) {
        if (a_end == a_start - 1) {
            return 0; 
        }
    }

    return tolower(*a_end) - tolower(*b_end);
}

int WriteTextinFile (line *text, const char *file) {

    if (!text || !file) {
        ERR_MSG(ERR_NULL_PTR);
        return EOF;
    }

    FILE *output = fopen(file, "w");
    if (!output) {
        ERR_MSG(ERR_NULL_PTR);
        return EOF;
    }

    for (int i = 0; text[i].start != NULL; i++) {
        char *str = text[i].start;
        while (!isalnum(*str) && *str != '\0') {
            str++;
        }

        if (*str != '\0') {
            fprintf(output, "%s\n", str);
        }
    }
    fclose(output);

    return true;
}