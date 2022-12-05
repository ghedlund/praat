#ifndef PRAAT_VERSION_H
#define PRAAT_VERSION_H

#define PRAAT_VERSION_STR 6.3.02
#define PRAAT_VERSION_CSTR "6.3.02"
#define PRAAT_VERSION_NUM 6302
#define PRAAT_YEAR 2022
#define PRAAT_MONTH November
#define PRAAT_MONTH_CSTR "November"
#define PRAAT_DAY 29

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

