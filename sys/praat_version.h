#ifndef PRAAT_VERSION_H
#define PRAAT_VERSION_H

#define PRAAT_VERSION_STR 6.1.55
#define PRAAT_VERSION_CSTR "6.1.55"
#define PRAAT_VERSION_NUM 6155
#define PRAAT_YEAR 2021
#define PRAAT_MONTH October
#define PRAAT_MONTH_CSTR "October"
#define PRAAT_DAY 25

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
