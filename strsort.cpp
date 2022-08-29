#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include "config.h"
#include "general.h"
#include "strsort.h"

#define BUFF 10

char **GetText (const char *file_name) {

    if(!file_name){
        ERR_MSG(ERR_NULL_PTR);

        return NULL;
    }

    FILE *input = fopen(file_name, "r");
    if(!input){
        ERR_MSG(ERR_NULL_PTR);

        return NULL;
    }

    struct stat file_stats;
    stat(file_name, &file_stats);

    char *file = (char*) calloc(file_stats.st_size / sizeof(char) + BUFF, sizeof(char));
    int lines_count = ReadFile(input, file);

    char **text = (char**) calloc(lines_count + BUFF, sizeof(char*));
    SepLines(text, file);

    fclose(input);
    return text;
}

int ReadFile (FILE *input, char *file) {

    if(!input || !file){
        ERR_MSG(ERR_NULL_PTR);

        return EOF;
    }

    int c = 0, lines_count = 0;
    int i = 0;
    while((c = getc(input)) != EOF){
        if(c != '\n'){
            file[i] = (char) c;
        }
        else{
            file[i] = '\0';
            lines_count++;
        }

        i++;
    }
    file[++i] = '\0';
    file[i] = EOF;

    return lines_count;
}

void SepLines (char **text, char *file) {

    if(!text || !file){
        ERR_MSG(ERR_NULL_PTR);

        return;
    }

    int i = 0;
    for(i = 0; *file != EOF; i++, file++){
        while(*file == ' ' || *file == '\t'){
            file++;
        }

        if(*file != '\0'){
            text[i] = file;
        }
        else{
            i--;
        }

        char *end_of_line = 0;
        while(*file != '\0'){
            if(isalnum(*file)){
                end_of_line = file;
            }
            file++;
        }

        if(end_of_line){
            *(++end_of_line) = '\0';
        }
    }
    text[i] = NULL;
}

int LinesCount (char **text) {

    if(!text){
        ERR_MSG(ERR_NULL_PTR);

        return EOF;
    }

    int i = 0;
    while(text[i++] != NULL) ;

    return i-1;
}

int WriteTextinFile (char **text, const char *file) {

    if(!text || !file){
        ERR_MSG(ERR_NULL_PTR);

        return EOF;
    }

    FILE *output = fopen(file, "w");
    if(!output){
        ERR_MSG(ERR_NULL_PTR);

        return EOF;
    }

    for(int i = 0; text[i] != NULL; i++){
        fprintf(output, "%s\n", text[i]);
    }
    fclose(output);

    return true;
}

char **ReverseText (char **text, int lines_count) {

    if(!text){
        ERR_MSG(ERR_NULL_PTR);

        return NULL;
    }

    char **rtext = (char**) calloc(lines_count + BUFF, sizeof(char*));
    int i = 0;
    for(i = 0; text[i] != NULL; i++){
        rtext[i] = ReverseLine(text[i], strlen(text[i]));
    }
    rtext[i] = NULL;

    return rtext;
}

char *ReverseLine (char *str, int len) {

    if(!str){
        ERR_MSG(ERR_NULL_PTR);

        return NULL;
    }

    char *rstr = (char*) calloc(len + BUFF, sizeof(char));
    int i = 0;
    for(int j = len-1; i < len; i++, j--){
        rstr[i] = str[j];
    }
    rstr[i] = '\0';

    return rstr;
}

void qStrSort (char **text, int low, int hight) {

    if(!text){
        ERR_MSG(ERR_NULL_PTR);

        return;
    }

    if(low < hight){
        int p = sort_partition(text, low, hight);
        qStrSort(text, low, p-1);
        qStrSort(text, p+1, hight);
    }
}

int sort_partition (char **text, int low, int hight) {

    if(!text){
        ERR_MSG(ERR_NULL_PTR);

        return EOF;
    }

    int i = low;
    for(int j = low; j < hight; j++){
        if(strcmp(text[j], text[hight]) <= 0){
            strswap(&text[i], &text[j]);
            i++;
        }
    }
    strswap(&text[i], &text[hight]);

    return i;
}






//===================== version with realloc (dynamic memory allocation)


char *ReadLine (FILE *input) {

    if(!input){
        ERR_MSG(ERR_NULL_PTR);

        return NULL;
    }

    int line_size = 1024;
    char *str = (char*) calloc(line_size, sizeof(char));

    int i = 0, c = 0;
    for(i = 0; (c = getc(input)) != '\n' && c != EOF; i++){
        if(i+1 == line_size){
            line_size *= 2;
            str = (char*) realloc(str, line_size * sizeof(char));
        }

        str[i] = (char) c;
    }
    if(c == EOF){
        return NULL;
    }
    str[i] = '\0';

    return str;
}

char **ReadText (FILE *input) {

    if(!input){
        ERR_MSG(ERR_NULL_PTR);

        return NULL;
    }

    int str_count = 1024;
    char **lines = (char**) calloc(str_count, sizeof(char*));

    char *str = 0;
    int i = 0;
    for(i = 0; (str = ReadLine(input)) != NULL; i++){
        if(i+1 == str_count){
            str_count *= 2;
            lines = (char**) realloc(lines, str_count * sizeof(char*));
        }

        DelLeadSpace(&str);

        if(*str != '\0'){
            lines[i] = str;
        }
        else{
            i--;
        }
    }
    lines[i] = NULL;

    return lines;
}

void DelLeadSpace (char **str){

    if(!str){
        ERR_MSG(ERR_NULL_PTR);

        return;
    }

    while(**str == ' ' || **str == '\t') {
        (*str)++;
    }
}

