#ifndef _PointProcess_h_
#define _PointProcess_h_
/* PointProcess.h
 *
 * Copyright (C) 1992-2005,2007,2011,2015-2020 Paul Boersma
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

#include "Function.h"
#include "Graphics.h"

#include "praatlib.h"

#include "PointProcess_def.h"

PRAAT_LIB_EXPORT autoPointProcess PointProcess_create (double startingTime, double finishingTime, integer initialMaxnt);
PRAAT_LIB_EXPORT autoPointProcess PointProcess_createPoissonProcess (double startingTime, double finishingTime, double density);
PRAAT_LIB_EXPORT void PointProcess_init (PointProcess me, double startingTime, double finishingTime, integer initialMaxnt);
PRAAT_LIB_EXPORT integer PointProcess_getLowIndex (PointProcess me, double t);
PRAAT_LIB_EXPORT integer PointProcess_getHighIndex (PointProcess me, double t);
PRAAT_LIB_EXPORT integer PointProcess_getNearestIndex (PointProcess me, double t);
PRAAT_LIB_EXPORT MelderIntegerRange PointProcess_getWindowPoints (PointProcess me, double tmin, double tmax);
PRAAT_LIB_EXPORT void PointProcess_addPoint (PointProcess me, double t);
PRAAT_LIB_EXPORT void PointProcess_addPoints (PointProcess me, constVECVU const& times);
PRAAT_LIB_EXPORT integer PointProcess_findPoint (PointProcess me, double t);
PRAAT_LIB_EXPORT void PointProcess_removePoint (PointProcess me, integer index);
PRAAT_LIB_EXPORT void PointProcess_removePointNear (PointProcess me, double t);
PRAAT_LIB_EXPORT void PointProcess_removePoints (PointProcess me, integer first, integer last);
PRAAT_LIB_EXPORT void PointProcess_removePointsBetween (PointProcess me, double fromTime, double toTime);
PRAAT_LIB_EXPORT void PointProcess_draw (PointProcess me, Graphics g, double fromTime, double toTime, bool garnish);
PRAAT_LIB_EXPORT double PointProcess_getInterval (PointProcess me, double t);
PRAAT_LIB_EXPORT autoPointProcess PointProcesses_union (PointProcess me, PointProcess thee);
PRAAT_LIB_EXPORT autoPointProcess PointProcesses_intersection (PointProcess me, PointProcess thee);
PRAAT_LIB_EXPORT autoPointProcess PointProcesses_difference (PointProcess me, PointProcess thee);
PRAAT_LIB_EXPORT void PointProcess_fill (PointProcess me, double tmin, double tmax, double period);
PRAAT_LIB_EXPORT void PointProcess_voice (PointProcess me, double period, double maxT);

PRAAT_LIB_EXPORT integer PointProcess_getNumberOfPeriods (PointProcess me, double tmin, double tmax,
	double minimumPeriod, double maximumPeriod, double maximumPeriodFactor);
PRAAT_LIB_EXPORT double PointProcess_getMeanPeriod (PointProcess me, double tmin, double tmax,
	double minimumPeriod, double maximumPeriod, double maximumPeriodFactor);
PRAAT_LIB_EXPORT double PointProcess_getStdevPeriod (PointProcess me, double tmin, double tmax,
	double minimumPeriod, double maximumPeriod, double maximumPeriodFactor);
MelderCountAndFraction PointProcess_getCountAndFractionOfVoiceBreaks (PointProcess me, double tmin, double tmax,
	double maximumPeriod);

#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT double PointProcess_getValueAtIndex(PointProcess me, integer idx);
#endif

/* End of file PointProcess.h */
#endif
