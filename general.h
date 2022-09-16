#ifndef _GENERAL_H
#define _GENERAL_H


enum ErrCodes {
    ERR_NULL_PTR    = 1,        ///< NULL pointer
    ERR_ARG_INVAL   = 2,        ///< invaluable arg
    ERR_INCRR_TESTS = 3,        ///< incorrect tests
    ERR_DVSN_ZERO   = 4         ///< devision on zero
};


int ArgsProcess    (int argc, const char *argv[], int num, const char *possible_args[], int *args[]);
void swap          (void *param1, void *param2, int size);
int ClearStdinBuf  ();
int WantContinue   ();


#endif // _GENERAL
