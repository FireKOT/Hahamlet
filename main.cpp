#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strsort.h"
#include "general.h"


int str_comparator (const void *param1, const void *param2);
int args_processing (int argc, const char *argv[]);

int main (int argc, const char *argv[]) {

//===================== version with realloc (dynamic memory allocation)
//    FILE *input_file = fopen("hamlet.txt", "r");
//    char **text = ReadText(input_file);
//    fclose(input_file);
//
//    qsort(text, LineCount(text), sizeof(char*), comp);
//
//    FILE *output_file = fopen("hamlet_sorted.txt", "w");
//    for(int i = 0; text[i] != NULL; i++){
//        fprintf(output_file, "%s\n", text[i]);
//    }
//    fclose(output_file);
//======================================================================

    char **text = GetText("hamlet.txt");
    int lines_count = LinesCount(text);
    char **rtext = ReverseText(text, lines_count);

    if(args_processing(argc, argv)){
        qStrSort(text, 0, lines_count-1);
        qStrSort(rtext, 0, lines_count-1);

        printf("File sorted by qStrSort\n");
    }
    else{
        qsort(text, LinesCount(text), sizeof(char*), str_comparator);
        qsort(rtext, LinesCount(text), sizeof(char*), str_comparator);

        printf("File sorted by qsort\n");
    }

    WriteTextinFile(text, "hamlet_sorted.txt");
    WriteTextinFile(rtext, "hamlet_sorted_reversed.txt");

    return 0;
}


int str_comparator (const void *param1, const void *param2) {

    return strcmp(*(char*const*) param1, *(char*const*) param2);
}

int args_processing (int argc, const char *argv[]) {

    int ismysort = false;
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i], "-mysort")){
            ismysort = true;
        }
    }

    return ismysort;
}
