#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strsort.h"
#include "general.h"
#include "config.h"


int main (int argc, const char *argv[]) {

    int ArgsNum = 1;
    int mysort = 0;
    int *args[] =                  {&mysort};
    const char *possible_args[] = {"-mysort"};

    ArgsProcess(argc, argv, ArgsNum, possible_args, args);

    text file = {};

    int err = GetText("hamlet.txt", &file);

    RET_ON_VAL(err == -1, ERR_NULL_PTR, ERR_NULL_PTR);

    if (mysort) {

        int w_err = 0;

        MyqSort(file.content, file.lines_count, sizeof(line), LineCmp);
        w_err = WriteTextinFile(&file, "hamlet_sorted.txt");
        RET_ON_VAL(w_err == -1, ERR_NULL_PTR, ERR_NULL_PTR);

        MyqSort(file.content, file.lines_count, sizeof(line), LineReverceCmp);
        w_err = WriteTextinFile(&file, "hamlet_sorted_reversed.txt");
        RET_ON_VAL(w_err == -1, ERR_NULL_PTR, ERR_NULL_PTR);

        printf("File sorted by qStrSort\n");
    }
    else {

        int w_err = 0;

        qsort(file.content, file.lines_count, sizeof(line), LineCmp);
        w_err = WriteTextinFile(&file, "hamlet_sorted.txt");
        RET_ON_VAL(w_err == -1, ERR_NULL_PTR, ERR_NULL_PTR);

        qsort(file.content, file.lines_count, sizeof(line), LineReverceCmp);
        w_err = WriteTextinFile(&file, "hamlet_sorted_reversed.txt");
        RET_ON_VAL(w_err == -1, ERR_NULL_PTR, ERR_NULL_PTR);

        printf("File sorted by qsort\n");
    }

    RET_ON_VAL(FreeText(&file) == -1, ERR_NULL_PTR, ERR_NULL_PTR);
    
    return 0;
}
