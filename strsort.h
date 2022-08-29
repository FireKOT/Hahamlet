#ifndef _STRSORT
#define _STRSORT


char **GetText      (const char *file_name);
int ReadFile        (FILE *input, char *file);
void SepLines       (char **text, char *file);
int LinesCount      (char **text);
int WriteTextinFile (char **text, const char *file);
char **ReverseText  (char **text, int lines_count);
char *ReverseLine   (char *str, int len);
void qStrSort       (char **text, int low, int hight);
int sort_partition  (char **text, int low, int hight);





//===================== version with realloc (dynamic memory allocation)


char *ReadLine    (FILE *input);
char **ReadText   (FILE *input);
void DelLeadSpace (char **str);

#endif // _STRSORT
