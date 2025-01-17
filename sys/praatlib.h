//
//  praatlib.h
//  praat64
//

#ifndef _praatlib_h
#define _praatlib_h

#ifndef PRAAT_LIB
#define PRAAT_LIB_EXPORT
#else
#ifdef WIN32
#ifdef __cplusplus
#define PRAAT_LIB_EXPORT extern "C" __declspec( dllexport )
#else
#define PRAAT_LIB_EXPORT __declspec( dllexport )
#endif
#else
#ifdef __cplusplus
#define PRAAT_LIB_EXPORT extern "C"
#else
#define PRAAT_LIB_EXPORT
#endif
#endif
#endif

PRAAT_LIB_EXPORT void praat_lib_init();

#endif
