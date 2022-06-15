#ifndef PRAAT_VERSION_H
#define PRAAT_VERSION_H

#define PRAAT_VERSION_STR 6.2.14
#define PRAAT_VERSION_CSTR "6.2.14"
#define PRAAT_VERSION_NUM 6214
#define PRAAT_YEAR 2022
#define PRAAT_MONTH May
#define PRAAT_MONTH_CSTR "May"
#define PRAAT_DAY 24

#ifdef PRAAT_LIB
// create a struct for version information
#include "praatlib.h"

struct structPraatVersion {
        const char* versionStr;
        const int version;
        const int year;
        const char* month;
        const int day;
};
typedef struct structPraatVersion* PraatVersion;

PRAAT_LIB_EXPORT PraatVersion praat_version();
#endif

#endif