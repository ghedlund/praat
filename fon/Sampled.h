#ifndef _Sampled_h_
#define _Sampled_h_
/* Sampled.h
 *
 * Copyright (C) 1992-2005,2007,2011,2013-2020 Paul Boersma
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */

/* Sampled inherits from Function */
#include "Function.h"
#include "Graphics.h"

#include "praatlib.h"

#include "Sampled_def.h"

/* A Sampled is a Function that is sampled at nx points [1..nx], */
/* which are spaced apart by a constant distance dx. */
/* The first sample point is at x1, the second at x1 + dx, */
/* and the last at x1 + (nx - 1) * dx. */

#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT double Sampled_indexToX (Sampled me, integer i);

PRAAT_LIB_EXPORT double Sampled_xToIndex (Sampled me, double x);

PRAAT_LIB_EXPORT integer Sampled_xToLowIndex (Sampled me, double x);

PRAAT_LIB_EXPORT integer Sampled_xToHighIndex (Sampled me, double x);

PRAAT_LIB_EXPORT integer Sampled_xToNearestIndex (Sampled me, double x);
#else
template <typename T> static inline double Sampled_indexToX (Sampled me, T index) { return my x1 + (index - (T) 1) * my dx; }
static inline double Sampled_xToIndex (Sampled me, double x) { return (x - my x1) / my dx + 1.0; }
static inline integer Sampled_xToLowIndex     (Sampled me, double x) { return Melder_ifloor   ((x - my x1) / my dx + 1.0); }
static inline integer Sampled_xToHighIndex    (Sampled me, double x) { return Melder_iceiling ((x - my x1) / my dx + 1.0); }
static inline integer Sampled_xToNearestIndex (Sampled me, double x) { return Melder_iround   ((x - my x1) / my dx + 1.0); }
#endif

static inline autoVEC Sampled_listAllXValues (Sampled me) {
	autoVEC result = raw_VEC (my nx);
	for (integer i = 1; i <= my nx; i ++)
		result [i] = my x1 + (i - 1) * my dx;
	return result;
}

PRAAT_LIB_EXPORT integer Sampled_getWindowSamples (Sampled me, double xmin, double xmax, integer *ixmin, integer *ixmax);

PRAAT_LIB_EXPORT void Sampled_init (Sampled me, double xmin, double xmax, integer nx, double dx, double x1);

PRAAT_LIB_EXPORT void Sampled_shortTermAnalysis (Sampled me, double windowDuration, double timeStep,
	integer *numberOfFrames, double *firstTime);
/*
	Function:
		how to put as many analysis windows of length 'windowDuration' as possible into my duration,
		when they are equally spaced by 'timeStep'.
	Input arguments:
		windowDuration:
			the duration of the analysis window, in seconds.
		timeStep:
			the time step, in seconds.
	Output arguments:
		numberOfFrames:
			at least 1 (if no failure); equals floor ((nx * dx - windowDuration) / timeStep) + 1.
		firstTime:
			the centre of the first frame, in seconds.
	Failures:
		Window longer than signal.
	Postconditions:
		the frames are divided symmetrically over my defined domain,
		which is [x1 - dx/2, x[nx] + dx/2], where x[nx] == x1 + (nx - 1) * dx.
		All analysis windows will fit into this domain.
	Usage:
		the resulting Sampled (analysis sequence, e.g., Pitch, Formant, Spectrogram, etc.)
		will have the following attributes:
			result -> xmin == my xmin;   // Copy logical domain.
			result -> xmax == my xmax;
			result -> nx == numberOfFrames;
			result -> dx == timeStep;
			result -> x1 == firstTime;
*/

PRAAT_LIB_EXPORT double Sampled_getValueAtSample (Sampled me, integer sampleNumber, integer level, int unit);
autoVEC Sampled_listValuesOfAllSamples (Sampled me, integer levelNumber, int unit);
PRAAT_LIB_EXPORT double Sampled_getValueAtX (Sampled me, double x, integer level, int unit, bool interpolate);
autoVEC Sampled_listValuesAtXes (Sampled me, constVECVU const& xes, integer levelNumber, int unit, bool interpolate);

integer Sampled_countDefinedSamples
	(Sampled me, double xmin, double xmax, integer levelNumber, int unit);
autoVEC Sampled_getSortedValues
	(Sampled me, double xmin, double xmax, integer levelNumber, int unit);

PRAAT_LIB_EXPORT double Sampled_getQuantile
	(Sampled me, double xmin, double xmax, double quantile, integer levelNumber, int unit);
PRAAT_LIB_EXPORT double Sampled_getMean
	(Sampled me, double xmin, double xmax, integer levelNumber, int unit, bool interpolate);
PRAAT_LIB_EXPORT double Sampled_getMean_standardUnit
	(Sampled me, double xmin, double xmax, integer levelNumber, int averagingUnit, bool interpolate);
PRAAT_LIB_EXPORT double Sampled_getIntegral
	(Sampled me, double xmin, double xmax, integer levelNumber, int unit, bool interpolate);
PRAAT_LIB_EXPORT double Sampled_getIntegral_standardUnit
	(Sampled me, double xmin, double xmax, integer levelNumber, int averagingUnit, bool interpolate);
PRAAT_LIB_EXPORT double Sampled_getStandardDeviation
	(Sampled me, double xmin, double xmax, integer levelNumber, int unit, bool interpolate);
PRAAT_LIB_EXPORT double Sampled_getStandardDeviation_standardUnit
	(Sampled me, double xmin, double xmax, integer levelNumber, int averagingUnit, bool interpolate);

PRAAT_LIB_EXPORT void Sampled_getMinimumAndX
	(Sampled me, double xmin, double xmax, integer levelNumber, int unit, bool interpolate,
	 double *return_minimum, double *return_xOfMinimum);
PRAAT_LIB_EXPORT double Sampled_getMinimum
	(Sampled me, double xmin, double xmax, integer levelNumber, int unit, bool interpolate);
PRAAT_LIB_EXPORT double Sampled_getXOfMinimum
	(Sampled me, double xmin, double xmax, integer levelNumber, int unit, bool interpolate);
PRAAT_LIB_EXPORT void Sampled_getMaximumAndX
	(Sampled me, double xmin, double xmax, integer levelNumber, int unit, bool interpolate,
	 double *return_maximum, double *return_xOfMaximum);
PRAAT_LIB_EXPORT double Sampled_getMaximum
	(Sampled me, double xmin, double xmax, integer levelNumber, int unit, bool interpolate);
PRAAT_LIB_EXPORT double Sampled_getXOfMaximum
	(Sampled me, double xmin, double xmax, integer levelNumber, int unit, bool interpolate);

void Sampled_drawInside
	(Sampled me, Graphics g, double xmin, double xmax, double ymin, double ymax, bool speckle, integer levelNumber, int unit);

#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT double Sampled_getXMin(Sampled me);
PRAAT_LIB_EXPORT double Sampled_getXMax(Sampled me);
PRAAT_LIB_EXPORT integer Sampled_getNx(Sampled me);
PRAAT_LIB_EXPORT double Sampled_getDx(Sampled me);
PRAAT_LIB_EXPORT double Sampled_getX1(Sampled me);
#endif

/* End of file Sampled.h */
#endif
