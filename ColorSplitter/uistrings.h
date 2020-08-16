#ifndef UISTRINGS_H
#define UISTRINGS_H

#include <QString>

//#define LANG_RU

/******************************************************************************
*
*   UI captions in different languages
*
******************************************************************************/
#ifdef LANG_RU
    #include "uistrings/uistringsru.h"
#else
    #include "uistrings/uistringseng.h"
#endif

#endif // UISTRINGS_H
