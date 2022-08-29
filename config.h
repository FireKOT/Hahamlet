#ifndef _CONFIG_H
#define _CONFIG_H

#define ERR_MSG_ON
//#define TEST


#ifdef ERR_MSG_ON

#define ERR_MSG(err_code) printf("Error code:%s in file: %s in function %s in line %d\n",\
                                      #err_code, __FILE__, __PRETTY_FUNCTION__, __LINE__)
#else

    #define ERR_MSG(err_code)

#endif



#endif
