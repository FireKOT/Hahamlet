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

    lyrics file;

    ArgsProcess(argc, argv, ArgsNum, possible_args, args);

    int err = GetText("hamlet.txt", &file);
    if (err == -1) {
        ERR_MSG(ERR_NULL_PTR);
        return ERR_NULL_PTR;
    }

    if (mysort) {
        MyqSort(file.text, file.lines_count, sizeof(line), linecmp);
        WriteTextinFile(file.text, "hamlet_sorted.txt");

        MyqSort(file.text, file.lines_count, sizeof(line), linercmp);
        WriteTextinFile(file.text, "hamlet_sorted.txt");

        printf("File sorted by qStrSort\n");
    }
    else {
        qsort(file.text, file.lines_count, sizeof(line), linecmp);
        WriteTextinFile(file.text, "hamlet_sorted.txt");

        qsort(file.text, file.lines_count, sizeof(line), linercmp);
        WriteTextinFile(file.text, "hamlet_sorted_reversed.txt");

        printf("File sorted by qsort\n");
    }

    return 0;
}
