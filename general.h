#ifndef _GENERAL_H
#define _GENERAL_H


enum ErrCodes{
    ERR_NULL_PTR,                   ///< NULL pointer
    ERR_ARG_INVAL,                  ///< invaluable arg
    ERR_INCRR_TESTS,                ///< incorrect tests
    ERR_DVSN_ZERO                   ///< devision on zero
};


//! @brief compare numbers of double type with EPS accuracy
//!
//! @param [in] n first double number
//! @param [in] m second double number
//!
//! @return [int] result of compare
//!
//! @retval true  if numbers are equal
//! @retval false otherwise
int  IsEqNum     (double n, double m);


//! @brief clear current line in console
//!
//! @return [int] result of cleaning
//!
//! @retval true  if there were trash in line
//! @retval false otherwise
int  ClearBuf    ();


//! @brief swap two numbers of double type
//!
//! @param [in] a first number
//! @param [in] b second number
void fswap    (double *a, double *b);


void strswap (char **str1, char **str2);


//! @brief request permission to continue
int WantContinue ();


#endif
