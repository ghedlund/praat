#define PRAAT_VERSION_STR 6.0.19
#define PRAAT_VERSION_CSTR "6.0.19"
#define PRAAT_VERSION_NUM 6019
#define PRAAT_YEAR 2016
#define PRAAT_MONTH June
#define PRAAT_MONTH_CSTR "June"
#define PRAAT_DAY 13

#ifndef PRAAT_VERSION_H
#define PRAAT_VERSION_H

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
