#include "../sys/praatlib.h"
#include "../sys/Thing.h"
#include "../sys/Data.h"
#include "../sys/Simple.h"
#include "../melder/MelderFile.h"
#include "../melder/melder_files.h"
#include "../fon/LongSound.h"
#include "../fon/Intensity.h"
#include "../fon/Sound_to_Intensity.h"
#include "../fon/Sampled.h"
#include "../fon/Matrix.h"
#include "../fon/Pitch.h"
#include "../fon/Pitch_to_PointProcess.h"
#include "../fon/Sound.h"
#include "../fon/Spectrogram.h"
#include "../fon/Sound_and_Spectrogram.h"
#include "../fon/Sound_to_Pitch.h"
#include "../fon/Spectrum.h"
#include "../fon/Sound_and_Spectrum.h"
#include "../fon/Spectrum_and_Spectrogram.h"
#include "../fon/Formant.h"
#include "../fon/Sound_to_Formant.h"
#include "../stat/Table.h"
#include "../stat/TableOfReal.h"
#include "../sys/Strings_.h"
#include "../fon/PointProcess.h"
#include "../fon/TextGrid.h"
#include "../dwtools/TextGrid_extensions.h"
#include "../fon/Ltas.h"
#include "../sys/Interpreter.h"

#include <pthread.h>
#include <string.h>
#include <stdlib.h>
static char _lastError[256] = {'\0'};
static pthread_mutex_t jpraat_mut = PTHREAD_MUTEX_INITIALIZER;

PRAAT_LIB_EXPORT const char* jpraat_last_error() {
	static char retVal[256] = {'\0'};
	pthread_mutex_lock(&jpraat_mut);
	strncpy(retVal, _lastError, 255);
	pthread_mutex_unlock(&jpraat_mut);
	return retVal;
}

PRAAT_LIB_EXPORT void jpraat_clear_error() {
	pthread_mutex_lock(&jpraat_mut);
	_lastError[0] = '\0';
	pthread_mutex_unlock(&jpraat_mut);
}

PRAAT_LIB_EXPORT void jpraat_set_error(const char* err) {
	pthread_mutex_lock(&jpraat_mut);
	strncpy(_lastError, err, 255);
	pthread_mutex_unlock(&jpraat_mut);
}

PRAAT_LIB_EXPORT void jpraat_set_melder_error() {
	conststring32 melderErr = Melder_getError();
	if(melderErr != NULL) {
		jpraat_set_error(Melder_peek32to8(melderErr));
	}
}

// _Thing_forget_wrapped -> _Thing_forget
PRAAT_LIB_EXPORT void _Thing_forget_wrapped(Thing arg0) {
	try {
		_Thing_forget(arg0);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// _Thing_forget_nozero_wrapped -> _Thing_forget_nozero
PRAAT_LIB_EXPORT void _Thing_forget_nozero_wrapped(Thing arg0) {
	try {
		_Thing_forget_nozero(arg0);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Thing_newFromClassName_wrapped -> Thing_newFromClassName
PRAAT_LIB_EXPORT Thing Thing_newFromClassName_wrapped(conststring32 arg0,int* arg1) {
	try {
		return Thing_newFromClassName(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Data_createTextFile_wrapped -> Data_createTextFile
PRAAT_LIB_EXPORT MelderFile Data_createTextFile_wrapped(Daata arg0,MelderFile arg1,bool arg2) {
	try {
		return Data_createTextFile(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Data_writeText_wrapped -> Data_writeText
PRAAT_LIB_EXPORT void Data_writeText_wrapped(Daata arg0,MelderFile arg1) {
	try {
		Data_writeText(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Data_writeToTextFile_wrapped -> Data_writeToTextFile
PRAAT_LIB_EXPORT void Data_writeToTextFile_wrapped(Daata arg0,MelderFile arg1) {
	try {
		Data_writeToTextFile(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Data_writeToShortTextFile_wrapped -> Data_writeToShortTextFile
PRAAT_LIB_EXPORT void Data_writeToShortTextFile_wrapped(Daata arg0,MelderFile arg1) {
	try {
		Data_writeToShortTextFile(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Data_writeToBinaryFile_wrapped -> Data_writeToBinaryFile
PRAAT_LIB_EXPORT void Data_writeToBinaryFile_wrapped(Daata arg0,MelderFile arg1) {
	try {
		Data_writeToBinaryFile(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Data_readFromTextFile_wrapped -> Data_readFromTextFile
PRAAT_LIB_EXPORT Thing Data_readFromTextFile_wrapped(MelderFile arg0) {
	try {
		return Data_readFromTextFile(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Data_readFromBinaryFile_wrapped -> Data_readFromBinaryFile
PRAAT_LIB_EXPORT Thing Data_readFromBinaryFile_wrapped(MelderFile arg0) {
	try {
		return Data_readFromBinaryFile(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Data_readFromFile_wrapped -> Data_readFromFile
PRAAT_LIB_EXPORT Thing Data_readFromFile_wrapped(MelderFile arg0) {
	try {
		return Data_readFromFile(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// SimpleInteger_create_wrapped -> SimpleInteger_create
PRAAT_LIB_EXPORT SimpleInteger SimpleInteger_create_wrapped(integer arg0) {
	try {
		return SimpleInteger_create(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// SimpleDouble_create_wrapped -> SimpleDouble_create
PRAAT_LIB_EXPORT SimpleDouble SimpleDouble_create_wrapped(double arg0) {
	try {
		return SimpleDouble_create(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// SimpleString_create_wrapped -> SimpleString_create
PRAAT_LIB_EXPORT SimpleString SimpleString_create_wrapped(conststring32 arg0) {
	try {
		return SimpleString_create(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// MelderFile_create_wrapped -> MelderFile_create
PRAAT_LIB_EXPORT MelderFile MelderFile_create_wrapped(MelderFile arg0) {
	try {
		return MelderFile_create(arg0);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// MelderFile_open_wrapped -> MelderFile_open
PRAAT_LIB_EXPORT MelderFile MelderFile_open_wrapped(MelderFile arg0) {
	try {
		return MelderFile_open(arg0);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Melder_pathToFile_wrapped -> Melder_pathToFile
PRAAT_LIB_EXPORT void Melder_pathToFile_wrapped(conststring32 arg0,MelderFile arg1) {
	try {
		Melder_pathToFile(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// LongSound_open_wrapped -> LongSound_open
PRAAT_LIB_EXPORT LongSound LongSound_open_wrapped(MelderFile arg0) {
	try {
		return LongSound_open(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// LongSound_extractPart_wrapped -> LongSound_extractPart
PRAAT_LIB_EXPORT Sound LongSound_extractPart_wrapped(LongSound arg0,double arg1,double arg2,bool arg3) {
	try {
		return LongSound_extractPart(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// LongSound_haveWindow_wrapped -> LongSound_haveWindow
PRAAT_LIB_EXPORT bool LongSound_haveWindow_wrapped(LongSound arg0,double arg1,double arg2) {
	try {
		return LongSound_haveWindow(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// LongSound_getWindowExtrema_wrapped -> LongSound_getWindowExtrema
PRAAT_LIB_EXPORT void LongSound_getWindowExtrema_wrapped(LongSound arg0,double arg1,double arg2,integer arg3,double* arg4,double* arg5) {
	try {
		LongSound_getWindowExtrema(arg0,arg1,arg2,arg3,arg4,arg5);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// LongSound_savePartAsAudioFile_wrapped -> LongSound_savePartAsAudioFile
PRAAT_LIB_EXPORT void LongSound_savePartAsAudioFile_wrapped(LongSound arg0,int arg1,double arg2,double arg3,MelderFile arg4,int arg5) {
	try {
		LongSound_savePartAsAudioFile(arg0,arg1,arg2,arg3,arg4,arg5);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// LongSound_saveChannelAsAudioFile_wrapped -> LongSound_saveChannelAsAudioFile
PRAAT_LIB_EXPORT void LongSound_saveChannelAsAudioFile_wrapped(LongSound arg0,int arg1,integer arg2,MelderFile arg3) {
	try {
		LongSound_saveChannelAsAudioFile(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Intensity_create_wrapped -> Intensity_create
PRAAT_LIB_EXPORT Intensity Intensity_create_wrapped(double arg0,double arg1,integer arg2,double arg3,double arg4) {
	try {
		return Intensity_create(arg0,arg1,arg2,arg3,arg4).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Intensity_to_Matrix_wrapped -> Intensity_to_Matrix
PRAAT_LIB_EXPORT Matrix Intensity_to_Matrix_wrapped(Intensity arg0) {
	try {
		return Intensity_to_Matrix(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Matrix_to_Intensity_wrapped -> Matrix_to_Intensity
PRAAT_LIB_EXPORT Intensity Matrix_to_Intensity_wrapped(Matrix arg0) {
	try {
		return Matrix_to_Intensity(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Intensity_getQuantile_wrapped -> Intensity_getQuantile
PRAAT_LIB_EXPORT double Intensity_getQuantile_wrapped(Intensity arg0,double arg1,double arg2,double arg3) {
	try {
		return Intensity_getQuantile(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Intensity_getAverage_wrapped -> Intensity_getAverage
PRAAT_LIB_EXPORT double Intensity_getAverage_wrapped(Intensity arg0,double arg1,double arg2,int arg3) {
	try {
		return Intensity_getAverage(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Sound_to_Intensity_wrapped -> Sound_to_Intensity
PRAAT_LIB_EXPORT Intensity Sound_to_Intensity_wrapped(Sound arg0,double arg1,double arg2,bool arg3) {
	try {
		return Sound_to_Intensity(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sampled_shortTermAnalysis_wrapped -> Sampled_shortTermAnalysis
PRAAT_LIB_EXPORT void Sampled_shortTermAnalysis_wrapped(Sampled arg0,double arg1,double arg2,intptr_t* arg3,double* arg4) {
	try {
		Sampled_shortTermAnalysis(arg0,arg1,arg2,arg3,arg4);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Sampled_getQuantile_wrapped -> Sampled_getQuantile
PRAAT_LIB_EXPORT double Sampled_getQuantile_wrapped(Sampled arg0,double arg1,double arg2,double arg3,integer arg4,int arg5) {
	try {
		return Sampled_getQuantile(arg0,arg1,arg2,arg3,arg4,arg5);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Matrix_create_wrapped -> Matrix_create
PRAAT_LIB_EXPORT Matrix Matrix_create_wrapped(double arg0,double arg1,integer arg2,double arg3,double arg4,double arg5,double arg6,integer arg7,double arg8,double arg9) {
	try {
		return Matrix_create(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Matrix_createSimple_wrapped -> Matrix_createSimple
PRAAT_LIB_EXPORT Matrix Matrix_createSimple_wrapped(integer arg0,integer arg1) {
	try {
		return Matrix_createSimple(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Matrix_readFromRawTextFile_wrapped -> Matrix_readFromRawTextFile
PRAAT_LIB_EXPORT Matrix Matrix_readFromRawTextFile_wrapped(MelderFile arg0) {
	try {
		return Matrix_readFromRawTextFile(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Matrix_readAP_wrapped -> Matrix_readAP
PRAAT_LIB_EXPORT Matrix Matrix_readAP_wrapped(MelderFile arg0) {
	try {
		return Matrix_readAP(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Matrix_power_wrapped -> Matrix_power
PRAAT_LIB_EXPORT Matrix Matrix_power_wrapped(Matrix arg0,integer arg1) {
	try {
		return Matrix_power(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Matrix_scaleAbsoluteExtremum_wrapped -> Matrix_scaleAbsoluteExtremum
PRAAT_LIB_EXPORT void Matrix_scaleAbsoluteExtremum_wrapped(Matrix arg0,double arg1) {
	try {
		Matrix_scaleAbsoluteExtremum(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Matrix_writeToMatrixTextFile_wrapped -> Matrix_writeToMatrixTextFile
PRAAT_LIB_EXPORT void Matrix_writeToMatrixTextFile_wrapped(Matrix arg0,MelderFile arg1) {
	try {
		Matrix_writeToMatrixTextFile(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Matrix_writeToHeaderlessSpreadsheetFile_wrapped -> Matrix_writeToHeaderlessSpreadsheetFile
PRAAT_LIB_EXPORT void Matrix_writeToHeaderlessSpreadsheetFile_wrapped(Matrix arg0,MelderFile arg1) {
	try {
		Matrix_writeToHeaderlessSpreadsheetFile(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Matrix_formula_wrapped -> Matrix_formula
PRAAT_LIB_EXPORT void Matrix_formula_wrapped(Matrix arg0,conststring32 arg1,Interpreter arg2,Matrix arg3) {
	try {
		Matrix_formula(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Matrix_formula_part_wrapped -> Matrix_formula_part
PRAAT_LIB_EXPORT void Matrix_formula_part_wrapped(Matrix arg0,double arg1,double arg2,double arg3,double arg4,conststring32 arg5,Interpreter arg6,Matrix arg7) {
	try {
		Matrix_formula_part(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Pitch_create_wrapped -> Pitch_create
PRAAT_LIB_EXPORT Pitch Pitch_create_wrapped(double arg0,double arg1,integer arg2,double arg3,double arg4,double arg5,integer arg6) {
	try {
		return Pitch_create(arg0,arg1,arg2,arg3,arg4,arg5,arg6).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Pitch_pathFinder_wrapped -> Pitch_pathFinder
PRAAT_LIB_EXPORT void Pitch_pathFinder_wrapped(Pitch arg0,double arg1,double arg2,double arg3,double arg4,double arg5,double arg6,int arg7) {
	try {
		Pitch_pathFinder(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Pitch_killOctaveJumps_wrapped -> Pitch_killOctaveJumps
PRAAT_LIB_EXPORT Pitch Pitch_killOctaveJumps_wrapped(Pitch arg0) {
	try {
		return Pitch_killOctaveJumps(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Pitch_interpolate_wrapped -> Pitch_interpolate
PRAAT_LIB_EXPORT Pitch Pitch_interpolate_wrapped(Pitch arg0) {
	try {
		return Pitch_interpolate(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Pitch_subtractLinearFit_wrapped -> Pitch_subtractLinearFit
PRAAT_LIB_EXPORT Pitch Pitch_subtractLinearFit_wrapped(Pitch arg0,enum kPitch_unit arg1) {
	try {
		return Pitch_subtractLinearFit(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Pitch_smooth_wrapped -> Pitch_smooth
PRAAT_LIB_EXPORT Pitch Pitch_smooth_wrapped(Pitch arg0,double arg1) {
	try {
		return Pitch_smooth(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Pitch_formula_wrapped -> Pitch_formula
PRAAT_LIB_EXPORT void Pitch_formula_wrapped(Pitch arg0,conststring32 arg1,Interpreter arg2) {
	try {
		Pitch_formula(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Pitch_to_PointProcess_wrapped -> Pitch_to_PointProcess
PRAAT_LIB_EXPORT PointProcess Pitch_to_PointProcess_wrapped(Pitch arg0) {
	try {
		return Pitch_to_PointProcess(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_Pitch_to_PointProcess_cc_wrapped -> Sound_Pitch_to_PointProcess_cc
PRAAT_LIB_EXPORT PointProcess Sound_Pitch_to_PointProcess_cc_wrapped(Sound arg0,Pitch arg1) {
	try {
		return Sound_Pitch_to_PointProcess_cc(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_Pitch_to_PointProcess_peaks_wrapped -> Sound_Pitch_to_PointProcess_peaks
PRAAT_LIB_EXPORT PointProcess Sound_Pitch_to_PointProcess_peaks_wrapped(Sound arg0,Pitch arg1,int arg2,int arg3) {
	try {
		return Sound_Pitch_to_PointProcess_peaks(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_readFromSoundFile_wrapped -> Sound_readFromSoundFile
PRAAT_LIB_EXPORT Sound Sound_readFromSoundFile_wrapped(MelderFile arg0) {
	try {
		return Sound_readFromSoundFile(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_saveAsAudioFile_wrapped -> Sound_saveAsAudioFile
PRAAT_LIB_EXPORT void Sound_saveAsAudioFile_wrapped(Sound arg0,MelderFile arg1,int arg2,int arg3) {
	try {
		Sound_saveAsAudioFile(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Sound_saveAsRawSoundFile_wrapped -> Sound_saveAsRawSoundFile
PRAAT_LIB_EXPORT void Sound_saveAsRawSoundFile_wrapped(Sound arg0,MelderFile arg1,int arg2) {
	try {
		Sound_saveAsRawSoundFile(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Sound_create_wrapped -> Sound_create
PRAAT_LIB_EXPORT Sound Sound_create_wrapped(integer arg0,double arg1,double arg2,integer arg3,double arg4,double arg5) {
	try {
		return Sound_create(arg0,arg1,arg2,arg3,arg4,arg5).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_createAsPureTone_wrapped -> Sound_createAsPureTone
PRAAT_LIB_EXPORT Sound Sound_createAsPureTone_wrapped(integer arg0,double arg1,double arg2,double arg3,double arg4,double arg5,double arg6,double arg7) {
	try {
		return Sound_createAsPureTone(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_createAsToneComplex_wrapped -> Sound_createAsToneComplex
PRAAT_LIB_EXPORT Sound Sound_createAsToneComplex_wrapped(double arg0,double arg1,double arg2,int arg3,double arg4,double arg5,double arg6,long arg7) {
	try {
		return Sound_createAsToneComplex(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_createSimple_wrapped -> Sound_createSimple
PRAAT_LIB_EXPORT Sound Sound_createSimple_wrapped(integer arg0,double arg1,double arg2) {
	try {
		return Sound_createSimple(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_convertToMono_wrapped -> Sound_convertToMono
PRAAT_LIB_EXPORT Sound Sound_convertToMono_wrapped(Sound arg0) {
	try {
		return Sound_convertToMono(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_convertToStereo_wrapped -> Sound_convertToStereo
PRAAT_LIB_EXPORT Sound Sound_convertToStereo_wrapped(Sound arg0) {
	try {
		return Sound_convertToStereo(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_extractChannel_wrapped -> Sound_extractChannel
PRAAT_LIB_EXPORT Sound Sound_extractChannel_wrapped(Sound arg0,integer arg1) {
	try {
		return Sound_extractChannel(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_upsample_wrapped -> Sound_upsample
PRAAT_LIB_EXPORT Sound Sound_upsample_wrapped(Sound arg0) {
	try {
		return Sound_upsample(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_resample_wrapped -> Sound_resample
PRAAT_LIB_EXPORT Sound Sound_resample_wrapped(Sound arg0,double arg1,integer arg2) {
	try {
		return Sound_resample(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sounds_append_wrapped -> Sounds_append
PRAAT_LIB_EXPORT Sound Sounds_append_wrapped(Sound arg0,double arg1,Sound arg2) {
	try {
		return Sounds_append(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sounds_convolve_wrapped -> Sounds_convolve
PRAAT_LIB_EXPORT Sound Sounds_convolve_wrapped(Sound arg0,Sound arg1,enum kSounds_convolve_scaling arg2,enum kSounds_convolve_signalOutsideTimeDomain arg3) {
	try {
		return Sounds_convolve(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sounds_crossCorrelate_wrapped -> Sounds_crossCorrelate
PRAAT_LIB_EXPORT Sound Sounds_crossCorrelate_wrapped(Sound arg0,Sound arg1,enum kSounds_convolve_scaling arg2,enum kSounds_convolve_signalOutsideTimeDomain arg3) {
	try {
		return Sounds_crossCorrelate(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sounds_crossCorrelate_short_wrapped -> Sounds_crossCorrelate_short
PRAAT_LIB_EXPORT Sound Sounds_crossCorrelate_short_wrapped(Sound arg0,Sound arg1,double arg2,double arg3,int arg4) {
	try {
		return Sounds_crossCorrelate_short(arg0,arg1,arg2,arg3,arg4).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_autoCorrelate_wrapped -> Sound_autoCorrelate
PRAAT_LIB_EXPORT Sound Sound_autoCorrelate_wrapped(Sound arg0,enum kSounds_convolve_scaling arg1,enum kSounds_convolve_signalOutsideTimeDomain arg2) {
	try {
		return Sound_autoCorrelate(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_extractPart_wrapped -> Sound_extractPart
PRAAT_LIB_EXPORT Sound Sound_extractPart_wrapped(Sound arg0,double arg1,double arg2,enum kSound_windowShape arg3,double arg4,bool arg5) {
	try {
		return Sound_extractPart(arg0,arg1,arg2,arg3,arg4,arg5).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_extractPartForOverlap_wrapped -> Sound_extractPartForOverlap
PRAAT_LIB_EXPORT Sound Sound_extractPartForOverlap_wrapped(Sound arg0,double arg1,double arg2,double arg3) {
	try {
		return Sound_extractPartForOverlap(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_filterWithFormants_wrapped -> Sound_filterWithFormants
PRAAT_LIB_EXPORT void Sound_filterWithFormants_wrapped(Sound arg0,double arg1,double arg2,int arg3,double arg4[],double arg5[]) {
	try {
		Sound_filterWithFormants(arg0,arg1,arg2,arg3,arg4,arg5);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Sound_filter_oneFormant_wrapped -> Sound_filter_oneFormant
PRAAT_LIB_EXPORT Sound Sound_filter_oneFormant_wrapped(Sound arg0,double arg1,double arg2) {
	try {
		return Sound_filter_oneFormant(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_filterWithOneFormantInplace_wrapped -> Sound_filterWithOneFormantInplace
PRAAT_LIB_EXPORT void Sound_filterWithOneFormantInplace_wrapped(Sound arg0,double arg1,double arg2) {
	try {
		Sound_filterWithOneFormantInplace(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Sound_filter_preemphasis_wrapped -> Sound_filter_preemphasis
PRAAT_LIB_EXPORT Sound Sound_filter_preemphasis_wrapped(Sound arg0,double arg1) {
	try {
		return Sound_filter_preemphasis(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_filter_deemphasis_wrapped -> Sound_filter_deemphasis
PRAAT_LIB_EXPORT Sound Sound_filter_deemphasis_wrapped(Sound arg0,double arg1) {
	try {
		return Sound_filter_deemphasis(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_reverse_wrapped -> Sound_reverse
PRAAT_LIB_EXPORT void Sound_reverse_wrapped(Sound arg0,double arg1,double arg2) {
	try {
		Sound_reverse(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Matrix_to_Sound_wrapped -> Matrix_to_Sound
PRAAT_LIB_EXPORT Sound Matrix_to_Sound_wrapped(Matrix arg0) {
	try {
		return Matrix_to_Sound(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Matrix_to_Sound_mono_wrapped -> Matrix_to_Sound_mono
PRAAT_LIB_EXPORT Sound Matrix_to_Sound_mono_wrapped(Matrix arg0,integer arg1) {
	try {
		return Matrix_to_Sound_mono(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrogram_create_wrapped -> Spectrogram_create
PRAAT_LIB_EXPORT Spectrogram Spectrogram_create_wrapped(double arg0,double arg1,integer arg2,double arg3,double arg4,double arg5,double arg6,integer arg7,double arg8,double arg9) {
	try {
		return Spectrogram_create(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Matrix_to_Spectrogram_wrapped -> Matrix_to_Spectrogram
PRAAT_LIB_EXPORT Spectrogram Matrix_to_Spectrogram_wrapped(Matrix arg0) {
	try {
		return Matrix_to_Spectrogram(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrogram_to_Matrix_wrapped -> Spectrogram_to_Matrix
PRAAT_LIB_EXPORT Matrix Spectrogram_to_Matrix_wrapped(Spectrogram arg0) {
	try {
		return Spectrogram_to_Matrix(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Spectrogram_wrapped -> Sound_to_Spectrogram
PRAAT_LIB_EXPORT Spectrogram Sound_to_Spectrogram_wrapped(Sound arg0,double arg1,double arg2,double arg3,double arg4,enum kSound_to_Spectrogram_windowShape arg5,double arg6,double arg7) {
	try {
		return Sound_to_Spectrogram(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Pitch_wrapped -> Sound_to_Pitch
PRAAT_LIB_EXPORT Pitch Sound_to_Pitch_wrapped(Sound arg0,double arg1,double arg2,double arg3) {
	try {
		return Sound_to_Pitch(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Pitch_ac_wrapped -> Sound_to_Pitch_ac
PRAAT_LIB_EXPORT Pitch Sound_to_Pitch_ac_wrapped(Sound arg0,double arg1,double arg2,double arg3,integer arg4,int arg5,double arg6,double arg7,double arg8,double arg9,double arg10,double arg11) {
	try {
		return Sound_to_Pitch_ac(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Pitch_cc_wrapped -> Sound_to_Pitch_cc
PRAAT_LIB_EXPORT Pitch Sound_to_Pitch_cc_wrapped(Sound arg0,double arg1,double arg2,double arg3,integer arg4,int arg5,double arg6,double arg7,double arg8,double arg9,double arg10,double arg11) {
	try {
		return Sound_to_Pitch_cc(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Pitch_any_wrapped -> Sound_to_Pitch_any
PRAAT_LIB_EXPORT Pitch Sound_to_Pitch_any_wrapped(Sound arg0,double arg1,double arg2,double arg3,int arg4,int arg5,double arg6,double arg7,double arg8,double arg9,double arg10,double arg11) {
	try {
		return Sound_to_Pitch_any(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrum_create_wrapped -> Spectrum_create
PRAAT_LIB_EXPORT Spectrum Spectrum_create_wrapped(double arg0,integer arg1) {
	try {
		return Spectrum_create(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrum_tabulate_wrapped -> Spectrum_tabulate
PRAAT_LIB_EXPORT Table Spectrum_tabulate_wrapped(Spectrum arg0,bool arg1,bool arg2,bool arg3,bool arg4,bool arg5,bool arg6) {
	try {
		return Spectrum_tabulate(arg0,arg1,arg2,arg3,arg4,arg5,arg6).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrum_tabulate_verbose_wrapped -> Spectrum_tabulate_verbose
PRAAT_LIB_EXPORT Table Spectrum_tabulate_verbose_wrapped(Spectrum arg0) {
	try {
		return Spectrum_tabulate_verbose(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Matrix_to_Spectrum_wrapped -> Matrix_to_Spectrum
PRAAT_LIB_EXPORT Spectrum Matrix_to_Spectrum_wrapped(Matrix arg0) {
	try {
		return Matrix_to_Spectrum(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrum_to_Matrix_wrapped -> Spectrum_to_Matrix
PRAAT_LIB_EXPORT Matrix Spectrum_to_Matrix_wrapped(Spectrum arg0) {
	try {
		return Spectrum_to_Matrix(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrum_cepstralSmoothing_wrapped -> Spectrum_cepstralSmoothing
PRAAT_LIB_EXPORT Spectrum Spectrum_cepstralSmoothing_wrapped(Spectrum arg0,double arg1) {
	try {
		return Spectrum_cepstralSmoothing(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Spectrum_wrapped -> Sound_to_Spectrum
PRAAT_LIB_EXPORT Spectrum Sound_to_Spectrum_wrapped(Sound arg0,bool arg1) {
	try {
		return Sound_to_Spectrum(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrum_to_Sound_wrapped -> Spectrum_to_Sound
PRAAT_LIB_EXPORT Sound Spectrum_to_Sound_wrapped(Spectrum arg0) {
	try {
		return Spectrum_to_Sound(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrum_lpcSmoothing_wrapped -> Spectrum_lpcSmoothing
PRAAT_LIB_EXPORT Spectrum Spectrum_lpcSmoothing_wrapped(Spectrum arg0,int arg1,double arg2) {
	try {
		return Spectrum_lpcSmoothing(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_filter_passHannBand_wrapped -> Sound_filter_passHannBand
PRAAT_LIB_EXPORT Sound Sound_filter_passHannBand_wrapped(Sound arg0,double arg1,double arg2,double arg3) {
	try {
		return Sound_filter_passHannBand(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_filter_stopHannBand_wrapped -> Sound_filter_stopHannBand
PRAAT_LIB_EXPORT Sound Sound_filter_stopHannBand_wrapped(Sound arg0,double arg1,double arg2,double arg3) {
	try {
		return Sound_filter_stopHannBand(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrogram_to_Spectrum_wrapped -> Spectrogram_to_Spectrum
PRAAT_LIB_EXPORT Spectrum Spectrogram_to_Spectrum_wrapped(Spectrogram arg0,double arg1) {
	try {
		return Spectrogram_to_Spectrum(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrum_to_Spectrogram_wrapped -> Spectrum_to_Spectrogram
PRAAT_LIB_EXPORT Spectrogram Spectrum_to_Spectrogram_wrapped(Spectrum arg0) {
	try {
		return Spectrum_to_Spectrogram(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Formant_create_wrapped -> Formant_create
PRAAT_LIB_EXPORT Formant Formant_create_wrapped(double arg0,double arg1,integer arg2,double arg3,double arg4,int arg5) {
	try {
		return Formant_create(arg0,arg1,arg2,arg3,arg4,arg5).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Formant_to_Matrix_wrapped -> Formant_to_Matrix
PRAAT_LIB_EXPORT Matrix Formant_to_Matrix_wrapped(Formant arg0,integer arg1) {
	try {
		return Formant_to_Matrix(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Formant_to_Matrix_bandwidths_wrapped -> Formant_to_Matrix_bandwidths
PRAAT_LIB_EXPORT Matrix Formant_to_Matrix_bandwidths_wrapped(Formant arg0,integer arg1) {
	try {
		return Formant_to_Matrix_bandwidths(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Formant_formula_frequencies_wrapped -> Formant_formula_frequencies
PRAAT_LIB_EXPORT void Formant_formula_frequencies_wrapped(Formant arg0,conststring32 arg1,Interpreter arg2) {
	try {
		Formant_formula_frequencies(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Formant_tracker_wrapped -> Formant_tracker
PRAAT_LIB_EXPORT Formant Formant_tracker_wrapped(Formant arg0,integer arg1,double arg2,double arg3,double arg4,double arg5,double arg6,double arg7,double arg8,double arg9) {
	try {
		return Formant_tracker(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Formant_downto_Table_wrapped -> Formant_downto_Table
PRAAT_LIB_EXPORT Table Formant_downto_Table_wrapped(Formant arg0,bool arg1,bool arg2,integer arg3,bool arg4,integer arg5,bool arg6,integer arg7,bool arg8) {
	try {
		return Formant_downto_Table(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Formant_any_wrapped -> Sound_to_Formant_any
PRAAT_LIB_EXPORT Formant Sound_to_Formant_any_wrapped(Sound arg0,double arg1,integer arg2,double arg3,double arg4,int arg5,double arg6,double arg7) {
	try {
		return Sound_to_Formant_any(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Formant_burg_wrapped -> Sound_to_Formant_burg
PRAAT_LIB_EXPORT Formant Sound_to_Formant_burg_wrapped(Sound arg0,double arg1,double arg2,double arg3,double arg4,double arg5) {
	try {
		return Sound_to_Formant_burg(arg0,arg1,arg2,arg3,arg4,arg5).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Formant_keepAll_wrapped -> Sound_to_Formant_keepAll
PRAAT_LIB_EXPORT Formant Sound_to_Formant_keepAll_wrapped(Sound arg0,double arg1,double arg2,double arg3,double arg4,double arg5) {
	try {
		return Sound_to_Formant_keepAll(arg0,arg1,arg2,arg3,arg4,arg5).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Formant_willems_wrapped -> Sound_to_Formant_willems
PRAAT_LIB_EXPORT Formant Sound_to_Formant_willems_wrapped(Sound arg0,double arg1,double arg2,double arg3,double arg4,double arg5) {
	try {
		return Sound_to_Formant_willems(arg0,arg1,arg2,arg3,arg4,arg5).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Table_createWithoutColumnNames_wrapped -> Table_createWithoutColumnNames
PRAAT_LIB_EXPORT Table Table_createWithoutColumnNames_wrapped(integer arg0,integer arg1) {
	try {
		return Table_createWithoutColumnNames(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Table_appendRow_wrapped -> Table_appendRow
PRAAT_LIB_EXPORT void Table_appendRow_wrapped(Table arg0) {
	try {
		Table_appendRow(arg0);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_appendColumn_wrapped -> Table_appendColumn
PRAAT_LIB_EXPORT void Table_appendColumn_wrapped(Table arg0,conststring32 arg1) {
	try {
		Table_appendColumn(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_appendSumColumn_wrapped -> Table_appendSumColumn
PRAAT_LIB_EXPORT void Table_appendSumColumn_wrapped(Table arg0,integer arg1,integer arg2,conststring32 arg3) {
	try {
		Table_appendSumColumn(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_appendDifferenceColumn_wrapped -> Table_appendDifferenceColumn
PRAAT_LIB_EXPORT void Table_appendDifferenceColumn_wrapped(Table arg0,integer arg1,integer arg2,conststring32 arg3) {
	try {
		Table_appendDifferenceColumn(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_appendProductColumn_wrapped -> Table_appendProductColumn
PRAAT_LIB_EXPORT void Table_appendProductColumn_wrapped(Table arg0,integer arg1,integer arg2,conststring32 arg3) {
	try {
		Table_appendProductColumn(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_appendQuotientColumn_wrapped -> Table_appendQuotientColumn
PRAAT_LIB_EXPORT void Table_appendQuotientColumn_wrapped(Table arg0,integer arg1,integer arg2,conststring32 arg3) {
	try {
		Table_appendQuotientColumn(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_removeRow_wrapped -> Table_removeRow
PRAAT_LIB_EXPORT void Table_removeRow_wrapped(Table arg0,integer arg1) {
	try {
		Table_removeRow(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_removeColumn_wrapped -> Table_removeColumn
PRAAT_LIB_EXPORT void Table_removeColumn_wrapped(Table arg0,integer arg1) {
	try {
		Table_removeColumn(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_insertRow_wrapped -> Table_insertRow
PRAAT_LIB_EXPORT void Table_insertRow_wrapped(Table arg0,integer arg1) {
	try {
		Table_insertRow(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_insertColumn_wrapped -> Table_insertColumn
PRAAT_LIB_EXPORT void Table_insertColumn_wrapped(Table arg0,integer arg1,conststring32 arg2) {
	try {
		Table_insertColumn(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_setColumnLabel_wrapped -> Table_setColumnLabel
PRAAT_LIB_EXPORT void Table_setColumnLabel_wrapped(Table arg0,integer arg1,conststring32 arg2) {
	try {
		Table_setColumnLabel(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_getColumnIndexFromColumnLabel_wrapped -> Table_getColumnIndexFromColumnLabel
PRAAT_LIB_EXPORT integer Table_getColumnIndexFromColumnLabel_wrapped(Table arg0,conststring32 arg1) {
	try {
		return Table_getColumnIndexFromColumnLabel(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Table_setStringValue_wrapped -> Table_setStringValue
PRAAT_LIB_EXPORT void Table_setStringValue_wrapped(Table arg0,integer arg1,integer arg2,conststring32 arg3) {
	try {
		Table_setStringValue(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_setNumericValue_wrapped -> Table_setNumericValue
PRAAT_LIB_EXPORT void Table_setNumericValue_wrapped(Table arg0,integer arg1,integer arg2,double arg3) {
	try {
		Table_setNumericValue(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_getStringValue_Assert_wrapped -> Table_getStringValue_Assert
PRAAT_LIB_EXPORT conststring32 Table_getStringValue_Assert_wrapped(Table arg0,integer arg1,integer arg2) {
	try {
		return Table_getStringValue_Assert(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Table_getNumericValue_Assert_wrapped -> Table_getNumericValue_Assert
PRAAT_LIB_EXPORT double Table_getNumericValue_Assert_wrapped(Table arg0,integer arg1,integer arg2) {
	try {
		return Table_getNumericValue_Assert(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getQuantile_wrapped -> Table_getQuantile
PRAAT_LIB_EXPORT double Table_getQuantile_wrapped(Table arg0,integer arg1,double arg2) {
	try {
		return Table_getQuantile(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getMean_wrapped -> Table_getMean
PRAAT_LIB_EXPORT double Table_getMean_wrapped(Table arg0,integer arg1) {
	try {
		return Table_getMean(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getMaximum_wrapped -> Table_getMaximum
PRAAT_LIB_EXPORT double Table_getMaximum_wrapped(Table arg0,integer arg1) {
	try {
		return Table_getMaximum(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getMinimum_wrapped -> Table_getMinimum
PRAAT_LIB_EXPORT double Table_getMinimum_wrapped(Table arg0,integer arg1) {
	try {
		return Table_getMinimum(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getGroupMean_wrapped -> Table_getGroupMean
PRAAT_LIB_EXPORT double Table_getGroupMean_wrapped(Table arg0,integer arg1,integer arg2,conststring32 arg3) {
	try {
		return Table_getGroupMean(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getStdev_wrapped -> Table_getStdev
PRAAT_LIB_EXPORT double Table_getStdev_wrapped(Table arg0,integer arg1) {
	try {
		return Table_getStdev(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_drawRowFromDistribution_wrapped -> Table_drawRowFromDistribution
PRAAT_LIB_EXPORT integer Table_drawRowFromDistribution_wrapped(Table arg0,integer arg1) {
	try {
		return Table_drawRowFromDistribution(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Table_getCorrelation_pearsonR_wrapped -> Table_getCorrelation_pearsonR
PRAAT_LIB_EXPORT double Table_getCorrelation_pearsonR_wrapped(Table arg0,integer arg1,integer arg2,double arg3,double* arg4,double* arg5,double* arg6) {
	try {
		return Table_getCorrelation_pearsonR(arg0,arg1,arg2,arg3,arg4,arg5,arg6);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getCorrelation_kendallTau_wrapped -> Table_getCorrelation_kendallTau
PRAAT_LIB_EXPORT double Table_getCorrelation_kendallTau_wrapped(Table arg0,integer arg1,integer arg2,double arg3,double* arg4,double* arg5,double* arg6) {
	try {
		return Table_getCorrelation_kendallTau(arg0,arg1,arg2,arg3,arg4,arg5,arg6);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getMean_studentT_wrapped -> Table_getMean_studentT
PRAAT_LIB_EXPORT double Table_getMean_studentT_wrapped(Table arg0,integer arg1,double arg2,double* arg3,double* arg4,double* arg5,double* arg6,double* arg7) {
	try {
		return Table_getMean_studentT(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getDifference_studentT_wrapped -> Table_getDifference_studentT
PRAAT_LIB_EXPORT double Table_getDifference_studentT_wrapped(Table arg0,integer arg1,integer arg2,double arg3,double* arg4,double* arg5,double* arg6,double* arg7,double* arg8) {
	try {
		return Table_getDifference_studentT(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getGroupMean_studentT_wrapped -> Table_getGroupMean_studentT
PRAAT_LIB_EXPORT double Table_getGroupMean_studentT_wrapped(Table arg0,integer arg1,integer arg2,conststring32 arg3,double arg4,double* arg5,double* arg6,double* arg7,double* arg8,double* arg9) {
	try {
		return Table_getGroupMean_studentT(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getGroupDifference_studentT_wrapped -> Table_getGroupDifference_studentT
PRAAT_LIB_EXPORT double Table_getGroupDifference_studentT_wrapped(Table arg0,integer arg1,integer arg2,conststring32 arg3,conststring32 arg4,double arg5,double* arg6,double* arg7,double* arg8,double* arg9,double* arg10) {
	try {
		return Table_getGroupDifference_studentT(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getGroupDifference_wilcoxonRankSum_wrapped -> Table_getGroupDifference_wilcoxonRankSum
PRAAT_LIB_EXPORT double Table_getGroupDifference_wilcoxonRankSum_wrapped(Table arg0,integer arg1,integer arg2,conststring32 arg3,conststring32 arg4,double* arg5,double* arg6) {
	try {
		return Table_getGroupDifference_wilcoxonRankSum(arg0,arg1,arg2,arg3,arg4,arg5,arg6);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_getExtrema_wrapped -> Table_getExtrema
PRAAT_LIB_EXPORT bool Table_getExtrema_wrapped(Table arg0,integer arg1,double* arg2,double* arg3) {
	try {
		return Table_getExtrema(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_randomizeRows_wrapped -> Table_randomizeRows
PRAAT_LIB_EXPORT void Table_randomizeRows_wrapped(Table arg0) {
	try {
		Table_randomizeRows(arg0);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_reflectRows_wrapped -> Table_reflectRows
PRAAT_LIB_EXPORT void Table_reflectRows_wrapped(Table arg0) {
	try {
		Table_reflectRows(arg0);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_writeToTabSeparatedFile_wrapped -> Table_writeToTabSeparatedFile
PRAAT_LIB_EXPORT void Table_writeToTabSeparatedFile_wrapped(Table arg0,MelderFile arg1) {
	try {
		Table_writeToTabSeparatedFile(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_writeToCommaSeparatedFile_wrapped -> Table_writeToCommaSeparatedFile
PRAAT_LIB_EXPORT void Table_writeToCommaSeparatedFile_wrapped(Table arg0,MelderFile arg1) {
	try {
		Table_writeToCommaSeparatedFile(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_readFromTableFile_wrapped -> Table_readFromTableFile
PRAAT_LIB_EXPORT Table Table_readFromTableFile_wrapped(MelderFile arg0) {
	try {
		return Table_readFromTableFile(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Table_readFromCharacterSeparatedTextFile_wrapped -> Table_readFromCharacterSeparatedTextFile
PRAAT_LIB_EXPORT Table Table_readFromCharacterSeparatedTextFile_wrapped(MelderFile arg0,char arg1,bool arg2) {
	try {
		return Table_readFromCharacterSeparatedTextFile(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Table_extractRowsWhereColumn_number_wrapped -> Table_extractRowsWhereColumn_number
PRAAT_LIB_EXPORT Table Table_extractRowsWhereColumn_number_wrapped(Table arg0,integer arg1,enum kMelder_number arg2,double arg3) {
	try {
		return Table_extractRowsWhereColumn_number(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Table_extractRowsWhereColumn_string_wrapped -> Table_extractRowsWhereColumn_string
PRAAT_LIB_EXPORT Table Table_extractRowsWhereColumn_string_wrapped(Table arg0,integer arg1,enum kMelder_string arg2,conststring32 arg3) {
	try {
		return Table_extractRowsWhereColumn_string(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Table_transpose_wrapped -> Table_transpose
PRAAT_LIB_EXPORT Table Table_transpose_wrapped(Table arg0) {
	try {
		return Table_transpose(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Table_checkSpecifiedRowNumberWithinRange_wrapped -> Table_checkSpecifiedRowNumberWithinRange
PRAAT_LIB_EXPORT void Table_checkSpecifiedRowNumberWithinRange_wrapped(Table arg0,integer arg1) {
	try {
		Table_checkSpecifiedRowNumberWithinRange(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Table_checkSpecifiedColumnNumberWithinRange_wrapped -> Table_checkSpecifiedColumnNumberWithinRange
PRAAT_LIB_EXPORT void Table_checkSpecifiedColumnNumberWithinRange_wrapped(Table arg0,integer arg1) {
	try {
		Table_checkSpecifiedColumnNumberWithinRange(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TableOfReal_init_wrapped -> TableOfReal_init
PRAAT_LIB_EXPORT void TableOfReal_init_wrapped(TableOfReal arg0,integer arg1,integer arg2) {
	try {
		TableOfReal_init(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TableOfReal_create_wrapped -> TableOfReal_create
PRAAT_LIB_EXPORT TableOfReal TableOfReal_create_wrapped(integer arg0,integer arg1) {
	try {
		return TableOfReal_create(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_removeRow_wrapped -> TableOfReal_removeRow
PRAAT_LIB_EXPORT void TableOfReal_removeRow_wrapped(TableOfReal arg0,integer arg1) {
	try {
		TableOfReal_removeRow(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TableOfReal_removeColumn_wrapped -> TableOfReal_removeColumn
PRAAT_LIB_EXPORT void TableOfReal_removeColumn_wrapped(TableOfReal arg0,integer arg1) {
	try {
		TableOfReal_removeColumn(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TableOfReal_insertRow_wrapped -> TableOfReal_insertRow
PRAAT_LIB_EXPORT void TableOfReal_insertRow_wrapped(TableOfReal arg0,integer arg1) {
	try {
		TableOfReal_insertRow(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TableOfReal_insertColumn_wrapped -> TableOfReal_insertColumn
PRAAT_LIB_EXPORT void TableOfReal_insertColumn_wrapped(TableOfReal arg0,integer arg1) {
	try {
		TableOfReal_insertColumn(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TableOfReal_setRowLabel_wrapped -> TableOfReal_setRowLabel
PRAAT_LIB_EXPORT void TableOfReal_setRowLabel_wrapped(TableOfReal arg0,integer arg1,conststring32 arg2) {
	try {
		TableOfReal_setRowLabel(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TableOfReal_setColumnLabel_wrapped -> TableOfReal_setColumnLabel
PRAAT_LIB_EXPORT void TableOfReal_setColumnLabel_wrapped(TableOfReal arg0,integer arg1,conststring32 arg2) {
	try {
		TableOfReal_setColumnLabel(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TableOfReal_rowLabelToIndex_wrapped -> TableOfReal_rowLabelToIndex
PRAAT_LIB_EXPORT integer TableOfReal_rowLabelToIndex_wrapped(TableOfReal arg0,conststring32 arg1) {
	try {
		return TableOfReal_rowLabelToIndex(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_columnLabelToIndex_wrapped -> TableOfReal_columnLabelToIndex
PRAAT_LIB_EXPORT integer TableOfReal_columnLabelToIndex_wrapped(TableOfReal arg0,conststring32 arg1) {
	try {
		return TableOfReal_columnLabelToIndex(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_getColumnMean_wrapped -> TableOfReal_getColumnMean
PRAAT_LIB_EXPORT double TableOfReal_getColumnMean_wrapped(TableOfReal arg0,integer arg1) {
	try {
		return TableOfReal_getColumnMean(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// TableOfReal_getColumnStdev_wrapped -> TableOfReal_getColumnStdev
PRAAT_LIB_EXPORT double TableOfReal_getColumnStdev_wrapped(TableOfReal arg0,integer arg1) {
	try {
		return TableOfReal_getColumnStdev(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
return 0;
}

// Table_to_TableOfReal_wrapped -> Table_to_TableOfReal
PRAAT_LIB_EXPORT TableOfReal Table_to_TableOfReal_wrapped(Table arg0,integer arg1) {
	try {
		return Table_to_TableOfReal(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_to_Table_wrapped -> TableOfReal_to_Table
PRAAT_LIB_EXPORT Table TableOfReal_to_Table_wrapped(TableOfReal arg0,conststring32 arg1) {
	try {
		return TableOfReal_to_Table(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_sortByLabel_wrapped -> TableOfReal_sortByLabel
PRAAT_LIB_EXPORT void TableOfReal_sortByLabel_wrapped(TableOfReal arg0,integer arg1,integer arg2) {
	try {
		TableOfReal_sortByLabel(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TableOfReal_sortByColumn_wrapped -> TableOfReal_sortByColumn
PRAAT_LIB_EXPORT void TableOfReal_sortByColumn_wrapped(TableOfReal arg0,integer arg1,integer arg2) {
	try {
		TableOfReal_sortByColumn(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TableOfReal_writeToHeaderlessSpreadsheetFile_wrapped -> TableOfReal_writeToHeaderlessSpreadsheetFile
PRAAT_LIB_EXPORT void TableOfReal_writeToHeaderlessSpreadsheetFile_wrapped(TableOfReal arg0,MelderFile arg1) {
	try {
		TableOfReal_writeToHeaderlessSpreadsheetFile(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TableOfReal_readFromHeaderlessSpreadsheetFile_wrapped -> TableOfReal_readFromHeaderlessSpreadsheetFile
PRAAT_LIB_EXPORT TableOfReal TableOfReal_readFromHeaderlessSpreadsheetFile_wrapped(MelderFile arg0) {
	try {
		return TableOfReal_readFromHeaderlessSpreadsheetFile(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_extractRowsWhereColumn_wrapped -> TableOfReal_extractRowsWhereColumn
PRAAT_LIB_EXPORT TableOfReal TableOfReal_extractRowsWhereColumn_wrapped(TableOfReal arg0,integer arg1,enum kMelder_number arg2,double arg3) {
	try {
		return TableOfReal_extractRowsWhereColumn(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_extractColumnsWhereRow_wrapped -> TableOfReal_extractColumnsWhereRow
PRAAT_LIB_EXPORT TableOfReal TableOfReal_extractColumnsWhereRow_wrapped(TableOfReal arg0,integer arg1,enum kMelder_number arg2,double arg3) {
	try {
		return TableOfReal_extractColumnsWhereRow(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_extractRowsWhoseLabel_wrapped -> TableOfReal_extractRowsWhoseLabel
PRAAT_LIB_EXPORT TableOfReal TableOfReal_extractRowsWhoseLabel_wrapped(TableOfReal arg0,enum kMelder_string arg1,conststring32 arg2) {
	try {
		return TableOfReal_extractRowsWhoseLabel(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_extractColumnsWhoseLabel_wrapped -> TableOfReal_extractColumnsWhoseLabel
PRAAT_LIB_EXPORT TableOfReal TableOfReal_extractColumnsWhoseLabel_wrapped(TableOfReal arg0,enum kMelder_string arg1,conststring32 arg2) {
	try {
		return TableOfReal_extractColumnsWhoseLabel(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_extractRowsWhere_wrapped -> TableOfReal_extractRowsWhere
PRAAT_LIB_EXPORT TableOfReal TableOfReal_extractRowsWhere_wrapped(TableOfReal arg0,conststring32 arg1,Interpreter arg2) {
	try {
		return TableOfReal_extractRowsWhere(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_extractColumnsWhere_wrapped -> TableOfReal_extractColumnsWhere
PRAAT_LIB_EXPORT TableOfReal TableOfReal_extractColumnsWhere_wrapped(TableOfReal arg0,conststring32 arg1,Interpreter arg2) {
	try {
		return TableOfReal_extractColumnsWhere(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_extractRowLabelsAsStrings_wrapped -> TableOfReal_extractRowLabelsAsStrings
PRAAT_LIB_EXPORT Strings TableOfReal_extractRowLabelsAsStrings_wrapped(TableOfReal arg0) {
	try {
		return TableOfReal_extractRowLabelsAsStrings(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TableOfReal_extractColumnLabelsAsStrings_wrapped -> TableOfReal_extractColumnLabelsAsStrings
PRAAT_LIB_EXPORT Strings TableOfReal_extractColumnLabelsAsStrings_wrapped(TableOfReal arg0) {
	try {
		return TableOfReal_extractColumnLabelsAsStrings(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Strings_createAsFileList_wrapped -> Strings_createAsFileList
PRAAT_LIB_EXPORT Strings Strings_createAsFileList_wrapped(conststring32 arg0) {
	try {
		return Strings_createAsFileList(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Strings_createAsFolderList_wrapped -> Strings_createAsFolderList
PRAAT_LIB_EXPORT Strings Strings_createAsFolderList_wrapped(conststring32 arg0) {
	try {
		return Strings_createAsFolderList(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Strings_readFromRawTextFile_wrapped -> Strings_readFromRawTextFile
PRAAT_LIB_EXPORT Strings Strings_readFromRawTextFile_wrapped(MelderFile arg0) {
	try {
		return Strings_readFromRawTextFile(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Strings_writeToRawTextFile_wrapped -> Strings_writeToRawTextFile
PRAAT_LIB_EXPORT void Strings_writeToRawTextFile_wrapped(Strings arg0,MelderFile arg1) {
	try {
		Strings_writeToRawTextFile(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Strings_remove_wrapped -> Strings_remove
PRAAT_LIB_EXPORT void Strings_remove_wrapped(Strings arg0,integer arg1) {
	try {
		Strings_remove(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Strings_replace_wrapped -> Strings_replace
PRAAT_LIB_EXPORT void Strings_replace_wrapped(Strings arg0,integer arg1,conststring32 arg2) {
	try {
		Strings_replace(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// Strings_insert_wrapped -> Strings_insert
PRAAT_LIB_EXPORT void Strings_insert_wrapped(Strings arg0,integer arg1,conststring32 arg2) {
	try {
		Strings_insert(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// PointProcess_create_wrapped -> PointProcess_create
PRAAT_LIB_EXPORT PointProcess PointProcess_create_wrapped(double arg0,double arg1,integer arg2) {
	try {
		return PointProcess_create(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// PointProcess_createPoissonProcess_wrapped -> PointProcess_createPoissonProcess
PRAAT_LIB_EXPORT PointProcess PointProcess_createPoissonProcess_wrapped(double arg0,double arg1,double arg2) {
	try {
		return PointProcess_createPoissonProcess(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// PointProcess_addPoint_wrapped -> PointProcess_addPoint
PRAAT_LIB_EXPORT void PointProcess_addPoint_wrapped(PointProcess arg0,double arg1) {
	try {
		PointProcess_addPoint(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// PointProcesses_union_wrapped -> PointProcesses_union
PRAAT_LIB_EXPORT PointProcess PointProcesses_union_wrapped(PointProcess arg0,PointProcess arg1) {
	try {
		return PointProcesses_union(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// PointProcesses_intersection_wrapped -> PointProcesses_intersection
PRAAT_LIB_EXPORT PointProcess PointProcesses_intersection_wrapped(PointProcess arg0,PointProcess arg1) {
	try {
		return PointProcesses_intersection(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// PointProcesses_difference_wrapped -> PointProcesses_difference
PRAAT_LIB_EXPORT PointProcess PointProcesses_difference_wrapped(PointProcess arg0,PointProcess arg1) {
	try {
		return PointProcesses_difference(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// PointProcess_fill_wrapped -> PointProcess_fill
PRAAT_LIB_EXPORT void PointProcess_fill_wrapped(PointProcess arg0,double arg1,double arg2,double arg3) {
	try {
		PointProcess_fill(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// PointProcess_voice_wrapped -> PointProcess_voice
PRAAT_LIB_EXPORT void PointProcess_voice_wrapped(PointProcess arg0,double arg1,double arg2) {
	try {
		PointProcess_voice(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextPoint_create_wrapped -> TextPoint_create
PRAAT_LIB_EXPORT TextPoint TextPoint_create_wrapped(double arg0,conststring32 arg1) {
	try {
		return TextPoint_create(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextPoint_setText_wrapped -> TextPoint_setText
PRAAT_LIB_EXPORT void TextPoint_setText_wrapped(TextPoint arg0,conststring32 arg1) {
	try {
		TextPoint_setText(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextInterval_create_wrapped -> TextInterval_create
PRAAT_LIB_EXPORT TextInterval TextInterval_create_wrapped(double arg0,double arg1,conststring32 arg2) {
	try {
		return TextInterval_create(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextInterval_setText_wrapped -> TextInterval_setText
PRAAT_LIB_EXPORT void TextInterval_setText_wrapped(TextInterval arg0,conststring32 arg1) {
	try {
		TextInterval_setText(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextTier_create_wrapped -> TextTier_create
PRAAT_LIB_EXPORT TextTier TextTier_create_wrapped(double arg0,double arg1) {
	try {
		return TextTier_create(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextTier_addPoint_wrapped -> TextTier_addPoint
PRAAT_LIB_EXPORT void TextTier_addPoint_wrapped(TextTier arg0,double arg1,conststring32 arg2) {
	try {
		TextTier_addPoint(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextTier_readFromXwaves_wrapped -> TextTier_readFromXwaves
PRAAT_LIB_EXPORT TextTier TextTier_readFromXwaves_wrapped(MelderFile arg0) {
	try {
		return TextTier_readFromXwaves(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextTier_getPoints_wrapped -> TextTier_getPoints
PRAAT_LIB_EXPORT PointProcess TextTier_getPoints_wrapped(TextTier arg0,conststring32 arg1) {
	try {
		return TextTier_getPoints(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextTier_removePoint_wrapped -> TextTier_removePoint
PRAAT_LIB_EXPORT void TextTier_removePoint_wrapped(TextTier arg0,integer arg1) {
	try {
		TextTier_removePoint(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// IntervalTier_create_wrapped -> IntervalTier_create
PRAAT_LIB_EXPORT IntervalTier IntervalTier_create_wrapped(double arg0,double arg1) {
	try {
		return IntervalTier_create(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// IntervalTier_readFromXwaves_wrapped -> IntervalTier_readFromXwaves
PRAAT_LIB_EXPORT IntervalTier IntervalTier_readFromXwaves_wrapped(MelderFile arg0) {
	try {
		return IntervalTier_readFromXwaves(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// IntervalTier_writeToXwaves_wrapped -> IntervalTier_writeToXwaves
PRAAT_LIB_EXPORT void IntervalTier_writeToXwaves_wrapped(IntervalTier arg0,MelderFile arg1) {
	try {
		IntervalTier_writeToXwaves(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// IntervalTier_getStartingPoints_wrapped -> IntervalTier_getStartingPoints
PRAAT_LIB_EXPORT PointProcess IntervalTier_getStartingPoints_wrapped(IntervalTier arg0,conststring32 arg1) {
	try {
		return IntervalTier_getStartingPoints(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// IntervalTier_getEndPoints_wrapped -> IntervalTier_getEndPoints
PRAAT_LIB_EXPORT PointProcess IntervalTier_getEndPoints_wrapped(IntervalTier arg0,conststring32 arg1) {
	try {
		return IntervalTier_getEndPoints(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// IntervalTier_getCentrePoints_wrapped -> IntervalTier_getCentrePoints
PRAAT_LIB_EXPORT PointProcess IntervalTier_getCentrePoints_wrapped(IntervalTier arg0,conststring32 arg1) {
	try {
		return IntervalTier_getCentrePoints(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// IntervalTier_PointProcess_startToCentre_wrapped -> IntervalTier_PointProcess_startToCentre
PRAAT_LIB_EXPORT PointProcess IntervalTier_PointProcess_startToCentre_wrapped(IntervalTier arg0,PointProcess arg1,double arg2) {
	try {
		return IntervalTier_PointProcess_startToCentre(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// IntervalTier_PointProcess_endToCentre_wrapped -> IntervalTier_PointProcess_endToCentre
PRAAT_LIB_EXPORT PointProcess IntervalTier_PointProcess_endToCentre_wrapped(IntervalTier arg0,PointProcess arg1,double arg2) {
	try {
		return IntervalTier_PointProcess_endToCentre(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// IntervalTier_removeLeftBoundary_wrapped -> IntervalTier_removeLeftBoundary
PRAAT_LIB_EXPORT void IntervalTier_removeLeftBoundary_wrapped(IntervalTier arg0,integer arg1) {
	try {
		IntervalTier_removeLeftBoundary(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_createWithoutTiers_wrapped -> TextGrid_createWithoutTiers
PRAAT_LIB_EXPORT TextGrid TextGrid_createWithoutTiers_wrapped(double arg0,double arg1) {
	try {
		return TextGrid_createWithoutTiers(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrids_merge_wrapped -> TextGrids_merge
PRAAT_LIB_EXPORT TextGrid TextGrids_merge_wrapped(TextGrid arg0,TextGrid arg1) {
	try {
		return TextGrids_merge(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_extendTime_wrapped -> TextGrid_extendTime
PRAAT_LIB_EXPORT void TextGrid_extendTime_wrapped(TextGrid arg0,double arg1,int arg2) {
	try {
		TextGrid_extendTime(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_setTierName_wrapped -> TextGrid_setTierName
PRAAT_LIB_EXPORT void TextGrid_setTierName_wrapped(TextGrid arg0,integer arg1,conststring32 arg2) {
	try {
		TextGrid_setTierName(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextTier_changeLabels_wrapped -> TextTier_changeLabels
PRAAT_LIB_EXPORT void TextTier_changeLabels_wrapped(TextTier arg0,integer arg1,integer arg2,conststring32 arg3,conststring32 arg4,bool arg5,intptr_t* arg6,intptr_t* arg7) {
	try {
		TextTier_changeLabels(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_changeLabels_wrapped -> TextGrid_changeLabels
PRAAT_LIB_EXPORT void TextGrid_changeLabels_wrapped(TextGrid arg0,integer arg1,integer arg2,integer arg3,conststring32 arg4,conststring32 arg5,bool arg6,intptr_t* arg7,intptr_t* arg8) {
	try {
		TextGrid_changeLabels(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// IntervalTier_removeBoundariesBetweenIdenticallyLabeledIntervals_wrapped -> IntervalTier_removeBoundariesBetweenIdenticallyLabeledIntervals
PRAAT_LIB_EXPORT void IntervalTier_removeBoundariesBetweenIdenticallyLabeledIntervals_wrapped(IntervalTier arg0,conststring32 arg1) {
	try {
		IntervalTier_removeBoundariesBetweenIdenticallyLabeledIntervals(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// IntervalTier_combineIntervalsOnLabelMatch_wrapped -> IntervalTier_combineIntervalsOnLabelMatch
PRAAT_LIB_EXPORT void IntervalTier_combineIntervalsOnLabelMatch_wrapped(IntervalTier arg0,conststring32 arg1) {
	try {
		IntervalTier_combineIntervalsOnLabelMatch(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// IntervalTier_cutIntervals_minimumDuration_wrapped -> IntervalTier_cutIntervals_minimumDuration
PRAAT_LIB_EXPORT void IntervalTier_cutIntervals_minimumDuration_wrapped(IntervalTier arg0,conststring32 arg1,double arg2) {
	try {
		IntervalTier_cutIntervals_minimumDuration(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// IntervalTier_setLaterEndTime_wrapped -> IntervalTier_setLaterEndTime
PRAAT_LIB_EXPORT void IntervalTier_setLaterEndTime_wrapped(IntervalTier arg0,double arg1,conststring32 arg2) {
	try {
		IntervalTier_setLaterEndTime(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// IntervalTier_setEarlierStartTime_wrapped -> IntervalTier_setEarlierStartTime
PRAAT_LIB_EXPORT void IntervalTier_setEarlierStartTime_wrapped(IntervalTier arg0,double arg1,conststring32 arg2) {
	try {
		IntervalTier_setEarlierStartTime(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// IntervalTier_moveBoundary_wrapped -> IntervalTier_moveBoundary
PRAAT_LIB_EXPORT void IntervalTier_moveBoundary_wrapped(IntervalTier arg0,long arg1,bool arg2,double arg3) {
	try {
		IntervalTier_moveBoundary(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextTier_setLaterEndTime_wrapped -> TextTier_setLaterEndTime
PRAAT_LIB_EXPORT void TextTier_setLaterEndTime_wrapped(TextTier arg0,double arg1,conststring32 arg2) {
	try {
		TextTier_setLaterEndTime(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextTier_setEarlierStartTime_wrapped -> TextTier_setEarlierStartTime
PRAAT_LIB_EXPORT void TextTier_setEarlierStartTime_wrapped(TextTier arg0,double arg1,conststring32 arg2) {
	try {
		TextTier_setEarlierStartTime(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_setEarlierStartTime_wrapped -> TextGrid_setEarlierStartTime
PRAAT_LIB_EXPORT void TextGrid_setEarlierStartTime_wrapped(TextGrid arg0,double arg1,conststring32 arg2,conststring32 arg3) {
	try {
		TextGrid_setEarlierStartTime(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_setLaterEndTime_wrapped -> TextGrid_setLaterEndTime
PRAAT_LIB_EXPORT void TextGrid_setLaterEndTime_wrapped(TextGrid arg0,double arg1,conststring32 arg2,conststring32 arg3) {
	try {
		TextGrid_setLaterEndTime(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// IntervalTiers_append_inplace_wrapped -> IntervalTiers_append_inplace
PRAAT_LIB_EXPORT void IntervalTiers_append_inplace_wrapped(IntervalTier arg0,IntervalTier arg1,bool arg2) {
	try {
		IntervalTiers_append_inplace(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextTiers_append_inplace_wrapped -> TextTiers_append_inplace
PRAAT_LIB_EXPORT void TextTiers_append_inplace_wrapped(TextTier arg0,TextTier arg1,bool arg2) {
	try {
		TextTiers_append_inplace(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrids_append_inplace_wrapped -> TextGrids_append_inplace
PRAAT_LIB_EXPORT void TextGrids_append_inplace_wrapped(TextGrid arg0,TextGrid arg1,bool arg2) {
	try {
		TextGrids_append_inplace(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_create_wrapped -> TextGrid_create
PRAAT_LIB_EXPORT TextGrid TextGrid_create_wrapped(double arg0,double arg1,conststring32 arg2,conststring32 arg3) {
	try {
		return TextGrid_create(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_countLabels_wrapped -> TextGrid_countLabels
PRAAT_LIB_EXPORT integer TextGrid_countLabels_wrapped(TextGrid arg0,integer arg1,conststring32 arg2) {
	try {
		return TextGrid_countLabels(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_getStartingPoints_wrapped -> TextGrid_getStartingPoints
PRAAT_LIB_EXPORT PointProcess TextGrid_getStartingPoints_wrapped(TextGrid arg0,integer arg1,enum kMelder_string arg2,conststring32 arg3) {
	try {
		return TextGrid_getStartingPoints(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_getEndPoints_wrapped -> TextGrid_getEndPoints
PRAAT_LIB_EXPORT PointProcess TextGrid_getEndPoints_wrapped(TextGrid arg0,integer arg1,enum kMelder_string arg2,conststring32 arg3) {
	try {
		return TextGrid_getEndPoints(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_getCentrePoints_wrapped -> TextGrid_getCentrePoints
PRAAT_LIB_EXPORT PointProcess TextGrid_getCentrePoints_wrapped(TextGrid arg0,integer arg1,enum kMelder_string arg2,conststring32 arg3) {
	try {
		return TextGrid_getCentrePoints(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_getPoints_wrapped -> TextGrid_getPoints
PRAAT_LIB_EXPORT PointProcess TextGrid_getPoints_wrapped(TextGrid arg0,integer arg1,enum kMelder_string arg2,conststring32 arg3) {
	try {
		return TextGrid_getPoints(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_getPoints_preceded_wrapped -> TextGrid_getPoints_preceded
PRAAT_LIB_EXPORT PointProcess TextGrid_getPoints_preceded_wrapped(TextGrid arg0,integer arg1,enum kMelder_string arg2,conststring32 arg3,enum kMelder_string arg4,conststring32 arg5) {
	try {
		return TextGrid_getPoints_preceded(arg0,arg1,arg2,arg3,arg4,arg5).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_getPoints_followed_wrapped -> TextGrid_getPoints_followed
PRAAT_LIB_EXPORT PointProcess TextGrid_getPoints_followed_wrapped(TextGrid arg0,integer arg1,enum kMelder_string arg2,conststring32 arg3,enum kMelder_string arg4,conststring32 arg5) {
	try {
		return TextGrid_getPoints_followed(arg0,arg1,arg2,arg3,arg4,arg5).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_checkSpecifiedTierNumberWithinRange_wrapped -> TextGrid_checkSpecifiedTierNumberWithinRange
PRAAT_LIB_EXPORT Function TextGrid_checkSpecifiedTierNumberWithinRange_wrapped(TextGrid arg0,integer arg1) {
	try {
		return TextGrid_checkSpecifiedTierNumberWithinRange(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_checkSpecifiedTierIsIntervalTier_wrapped -> TextGrid_checkSpecifiedTierIsIntervalTier
PRAAT_LIB_EXPORT IntervalTier TextGrid_checkSpecifiedTierIsIntervalTier_wrapped(TextGrid arg0,integer arg1) {
	try {
		return TextGrid_checkSpecifiedTierIsIntervalTier(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_checkSpecifiedTierIsPointTier_wrapped -> TextGrid_checkSpecifiedTierIsPointTier
PRAAT_LIB_EXPORT TextTier TextGrid_checkSpecifiedTierIsPointTier_wrapped(TextGrid arg0,integer arg1) {
	try {
		return TextGrid_checkSpecifiedTierIsPointTier(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_addTier_copy_wrapped -> TextGrid_addTier_copy
PRAAT_LIB_EXPORT void TextGrid_addTier_copy_wrapped(TextGrid arg0,Function arg1) {
	try {
		TextGrid_addTier_copy(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_removeTier_wrapped -> TextGrid_removeTier
PRAAT_LIB_EXPORT void TextGrid_removeTier_wrapped(TextGrid arg0,integer arg1) {
	try {
		TextGrid_removeTier(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_extractPart_wrapped -> TextGrid_extractPart
PRAAT_LIB_EXPORT TextGrid TextGrid_extractPart_wrapped(TextGrid arg0,double arg1,double arg2,bool arg3) {
	try {
		return TextGrid_extractPart(arg0,arg1,arg2,arg3).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_convertToBackslashTrigraphs_wrapped -> TextGrid_convertToBackslashTrigraphs
PRAAT_LIB_EXPORT void TextGrid_convertToBackslashTrigraphs_wrapped(TextGrid arg0) {
	try {
		TextGrid_convertToBackslashTrigraphs(arg0);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_convertToUnicode_wrapped -> TextGrid_convertToUnicode
PRAAT_LIB_EXPORT void TextGrid_convertToUnicode_wrapped(TextGrid arg0) {
	try {
		TextGrid_convertToUnicode(arg0);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_insertBoundary_wrapped -> TextGrid_insertBoundary
PRAAT_LIB_EXPORT void TextGrid_insertBoundary_wrapped(TextGrid arg0,integer arg1,double arg2) {
	try {
		TextGrid_insertBoundary(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_removeBoundaryAtTime_wrapped -> TextGrid_removeBoundaryAtTime
PRAAT_LIB_EXPORT void TextGrid_removeBoundaryAtTime_wrapped(TextGrid arg0,integer arg1,double arg2) {
	try {
		TextGrid_removeBoundaryAtTime(arg0,arg1,arg2);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_setIntervalText_wrapped -> TextGrid_setIntervalText
PRAAT_LIB_EXPORT void TextGrid_setIntervalText_wrapped(TextGrid arg0,integer arg1,integer arg2,conststring32 arg3) {
	try {
		TextGrid_setIntervalText(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_insertPoint_wrapped -> TextGrid_insertPoint
PRAAT_LIB_EXPORT void TextGrid_insertPoint_wrapped(TextGrid arg0,integer arg1,double arg2,conststring32 arg3) {
	try {
		TextGrid_insertPoint(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_setPointText_wrapped -> TextGrid_setPointText
PRAAT_LIB_EXPORT void TextGrid_setPointText_wrapped(TextGrid arg0,integer arg1,integer arg2,conststring32 arg3) {
	try {
		TextGrid_setPointText(arg0,arg1,arg2,arg3);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_writeToChronologicalTextFile_wrapped -> TextGrid_writeToChronologicalTextFile
PRAAT_LIB_EXPORT void TextGrid_writeToChronologicalTextFile_wrapped(TextGrid arg0,MelderFile arg1) {
	try {
		TextGrid_writeToChronologicalTextFile(arg0,arg1);
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
}

// TextGrid_readFromChronologicalTextFile_wrapped -> TextGrid_readFromChronologicalTextFile
PRAAT_LIB_EXPORT TextGrid TextGrid_readFromChronologicalTextFile_wrapped(MelderFile arg0) {
	try {
		return TextGrid_readFromChronologicalTextFile(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_readFromCgnSyntaxFile_wrapped -> TextGrid_readFromCgnSyntaxFile
PRAAT_LIB_EXPORT TextGrid TextGrid_readFromCgnSyntaxFile_wrapped(MelderFile arg0) {
	try {
		return TextGrid_readFromCgnSyntaxFile(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// TextGrid_downto_Table_wrapped -> TextGrid_downto_Table
PRAAT_LIB_EXPORT Table TextGrid_downto_Table_wrapped(TextGrid arg0,bool arg1,int arg2,bool arg3,bool arg4) {
	try {
		return TextGrid_downto_Table(arg0,arg1,arg2,arg3,arg4).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Ltas_create_wrapped -> Ltas_create
PRAAT_LIB_EXPORT Ltas Ltas_create_wrapped(integer arg0,double arg1) {
	try {
		return Ltas_create(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Matrix_to_Ltas_wrapped -> Matrix_to_Ltas
PRAAT_LIB_EXPORT Ltas Matrix_to_Ltas_wrapped(Matrix arg0) {
	try {
		return Matrix_to_Ltas(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Ltas_to_Matrix_wrapped -> Ltas_to_Matrix
PRAAT_LIB_EXPORT Matrix Ltas_to_Matrix_wrapped(Ltas arg0) {
	try {
		return Ltas_to_Matrix(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Ltas_computeTrendLine_wrapped -> Ltas_computeTrendLine
PRAAT_LIB_EXPORT Ltas Ltas_computeTrendLine_wrapped(Ltas arg0,double arg1,double arg2) {
	try {
		return Ltas_computeTrendLine(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Ltas_subtractTrendLine_wrapped -> Ltas_subtractTrendLine
PRAAT_LIB_EXPORT Ltas Ltas_subtractTrendLine_wrapped(Ltas arg0,double arg1,double arg2) {
	try {
		return Ltas_subtractTrendLine(arg0,arg1,arg2).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrum_to_Ltas_wrapped -> Spectrum_to_Ltas
PRAAT_LIB_EXPORT Ltas Spectrum_to_Ltas_wrapped(Spectrum arg0,double arg1) {
	try {
		return Spectrum_to_Ltas(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Spectrum_to_Ltas_1to1_wrapped -> Spectrum_to_Ltas_1to1
PRAAT_LIB_EXPORT Ltas Spectrum_to_Ltas_1to1_wrapped(Spectrum arg0) {
	try {
		return Spectrum_to_Ltas_1to1(arg0).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// PointProcess_Sound_to_Ltas_wrapped -> PointProcess_Sound_to_Ltas
PRAAT_LIB_EXPORT Ltas PointProcess_Sound_to_Ltas_wrapped(PointProcess arg0,Sound arg1,double arg2,double arg3,double arg4,double arg5,double arg6) {
	try {
		return PointProcess_Sound_to_Ltas(arg0,arg1,arg2,arg3,arg4,arg5,arg6).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// PointProcess_Sound_to_Ltas_harmonics_wrapped -> PointProcess_Sound_to_Ltas_harmonics
PRAAT_LIB_EXPORT Ltas PointProcess_Sound_to_Ltas_harmonics_wrapped(PointProcess arg0,Sound arg1,integer arg2,double arg3,double arg4,double arg5) {
	try {
		return PointProcess_Sound_to_Ltas_harmonics(arg0,arg1,arg2,arg3,arg4,arg5).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Ltas_wrapped -> Sound_to_Ltas
PRAAT_LIB_EXPORT Ltas Sound_to_Ltas_wrapped(Sound arg0,double arg1) {
	try {
		return Sound_to_Ltas(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Sound_to_Ltas_pitchCorrected_wrapped -> Sound_to_Ltas_pitchCorrected
PRAAT_LIB_EXPORT Ltas Sound_to_Ltas_pitchCorrected_wrapped(Sound arg0,double arg1,double arg2,double arg3,double arg4,double arg5,double arg6,double arg7) {
	try {
		return Sound_to_Ltas_pitchCorrected(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}

// Interpreter_create_wrapped -> Interpreter_create
PRAAT_LIB_EXPORT Interpreter Interpreter_create_wrapped(const char32* arg0,ClassInfo arg1) {
	try {
		return Interpreter_create(arg0,arg1).releaseToAmbiguousOwner();
	} catch (const char* e) {
		jpraat_set_error(e);
	} catch (MelderError) {
		jpraat_set_melder_error();
	} catch (...) {
		jpraat_set_error("Unknown error");
	}
	return NULL;
}
