#ifndef _TextGrid_h_
#define _TextGrid_h_
/* TextGrid.h
 *
 * Copyright (C) 1992-2012,2014,2015 Paul Boersma
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

#include "AnyTier.h"
#include "Label.h"
#include "Graphics.h"
#include "TableOfReal.h"
#include "Table.h"

Collection_define (FunctionList, OrderedOf, Function) {
};

#include "TextGrid_def.h"

#ifdef PRAAT_LIB
#include "praatlib.h"
#endif

PRAAT_LIB_EXPORT autoTextPoint TextPoint_create (double time, const char32 *mark);

PRAAT_LIB_EXPORT void TextPoint_setText (TextPoint me, const char32 *text);

PRAAT_LIB_EXPORT autoTextInterval TextInterval_create (double tmin, double tmax, const char32 *text);

PRAAT_LIB_EXPORT void TextInterval_setText (TextInterval me, const char32 *text);

PRAAT_LIB_EXPORT autoTextTier TextTier_create (double tmin, double tmax);

PRAAT_LIB_EXPORT void TextTier_addPoint (TextTier me, double time, const char32 *mark);
PRAAT_LIB_EXPORT autoTextTier TextTier_readFromXwaves (MelderFile file);
PRAAT_LIB_EXPORT autoPointProcess TextTier_getPoints (TextTier me, const char32 *text);

PRAAT_LIB_EXPORT autoIntervalTier IntervalTier_create (double tmin, double tmax);
PRAAT_LIB_EXPORT autoIntervalTier IntervalTier_readFromXwaves (MelderFile file);
PRAAT_LIB_EXPORT void IntervalTier_writeToXwaves (IntervalTier me, MelderFile file);

PRAAT_LIB_EXPORT long IntervalTier_timeToLowIndex (IntervalTier me, double t);
PRAAT_LIB_EXPORT long IntervalTier_timeToIndex (IntervalTier me, double t);   // obsolete
PRAAT_LIB_EXPORT long IntervalTier_timeToHighIndex (IntervalTier me, double t);
PRAAT_LIB_EXPORT long IntervalTier_hasTime (IntervalTier me, double t);
PRAAT_LIB_EXPORT long IntervalTier_hasBoundary (IntervalTier me, double t);
PRAAT_LIB_EXPORT autoPointProcess IntervalTier_getStartingPoints (IntervalTier me, const char32 *text);
PRAAT_LIB_EXPORT autoPointProcess IntervalTier_getEndPoints (IntervalTier me, const char32 *text);
PRAAT_LIB_EXPORT autoPointProcess IntervalTier_getCentrePoints (IntervalTier me, const char32 *text);
PRAAT_LIB_EXPORT autoPointProcess IntervalTier_PointProcess_startToCentre (IntervalTier tier, PointProcess point, double phase);
PRAAT_LIB_EXPORT autoPointProcess IntervalTier_PointProcess_endToCentre (IntervalTier tier, PointProcess point, double phase);
PRAAT_LIB_EXPORT void IntervalTier_removeLeftBoundary (IntervalTier me, long iinterval);

PRAAT_LIB_EXPORT void TextTier_removePoint (TextTier me, long ipoint);

PRAAT_LIB_EXPORT autoTextGrid TextGrid_createWithoutTiers (double tmin, double tmax);
PRAAT_LIB_EXPORT autoTextGrid TextGrid_create (double tmin, double tmax, const char32 *tierNames, const char32 *pointTiers);

PRAAT_LIB_EXPORT long TextGrid_countLabels (TextGrid me, long itier, const char32 *text);
long TextGrid_countIntervalsWhere (TextGrid me, long tierNumber, int which_Melder_STRING, const char32 *criterion);
long TextGrid_countPointsWhere (TextGrid me, long tierNumber, int which_Melder_STRING, const char32 *criterion);
PRAAT_LIB_EXPORT autoPointProcess TextGrid_getStartingPoints (TextGrid me, long itier, int which_Melder_STRING, const char32 *criterion);
PRAAT_LIB_EXPORT autoPointProcess TextGrid_getEndPoints (TextGrid me, long itier, int which_Melder_STRING, const char32 *criterion);
PRAAT_LIB_EXPORT autoPointProcess TextGrid_getCentrePoints (TextGrid me, long itier, int which_Melder_STRING, const char32 *criterion);
PRAAT_LIB_EXPORT autoPointProcess TextGrid_getPoints (TextGrid me, long itier, int which_Melder_STRING, const char32 *criterion);
PRAAT_LIB_EXPORT autoPointProcess TextGrid_getPoints_preceded (TextGrid me, long tierNumber,
	int which_Melder_STRING, const char32 *criterion,
	int which_Melder_STRING_precededBy, const char32 *criterion_precededBy);
PRAAT_LIB_EXPORT autoPointProcess TextGrid_getPoints_followed (TextGrid me, long tierNumber,
	int which_Melder_STRING, const char32 *criterion,
	int which_Melder_STRING_followedBy, const char32 *criterion_followedBy);

PRAAT_LIB_EXPORT Function TextGrid_checkSpecifiedTierNumberWithinRange (TextGrid me, long tierNumber);
PRAAT_LIB_EXPORT IntervalTier TextGrid_checkSpecifiedTierIsIntervalTier (TextGrid me, long tierNumber);
PRAAT_LIB_EXPORT TextTier TextGrid_checkSpecifiedTierIsPointTier (TextGrid me, long tierNumber);

PRAAT_LIB_EXPORT void TextGrid_addTier_copy (TextGrid me, Function tier);
autoTextGrid TextGrids_merge (OrderedOf<structTextGrid>* textGrids);
PRAAT_LIB_EXPORT autoTextGrid TextGrid_extractPart (TextGrid me, double tmin, double tmax, int preserveTimes);

autoTextGrid Label_to_TextGrid (Label me, double duration);
autoTextGrid Label_Function_to_TextGrid (Label me, Function function);

autoTextTier PointProcess_upto_TextTier (PointProcess me, const char32 *text);
autoTableOfReal IntervalTier_downto_TableOfReal (IntervalTier me, const char32 *label);
autoTableOfReal IntervalTier_downto_TableOfReal_any (IntervalTier me);
autoTableOfReal TextTier_downto_TableOfReal (TextTier me, const char32 *label);
autoTableOfReal TextTier_downto_TableOfReal_any (TextTier me);

autoTextGrid PointProcess_to_TextGrid_vuv (PointProcess me, double maxT, double meanT);

PRAAT_LIB_EXPORT long TextInterval_labelLength (TextInterval me);
PRAAT_LIB_EXPORT long TextPoint_labelLength (TextPoint me);
PRAAT_LIB_EXPORT long IntervalTier_maximumLabelLength (IntervalTier me);
PRAAT_LIB_EXPORT long TextTier_maximumLabelLength (TextTier me);
PRAAT_LIB_EXPORT long TextGrid_maximumLabelLength (TextGrid me);
PRAAT_LIB_EXPORT void TextGrid_genericize (TextGrid me);
PRAAT_LIB_EXPORT void TextGrid_nativize (TextGrid me);

PRAAT_LIB_EXPORT void TextInterval_removeText (TextInterval me);
PRAAT_LIB_EXPORT void TextPoint_removeText (TextPoint me);
PRAAT_LIB_EXPORT void IntervalTier_removeText (IntervalTier me);
PRAAT_LIB_EXPORT void TextTier_removeText (TextTier me);

PRAAT_LIB_EXPORT void TextTier_removePoints (TextTier me, int which_Melder_STRING, const char32 *criterion);
PRAAT_LIB_EXPORT void TextGrid_removePoints (TextGrid me, long tierNumber, int which_Melder_STRING, const char32 *criterion);

PRAAT_LIB_EXPORT void TextGrid_insertBoundary (TextGrid me, int itier, double t);
PRAAT_LIB_EXPORT void TextGrid_removeBoundaryAtTime (TextGrid me, int itier, double t);
PRAAT_LIB_EXPORT void TextGrid_setIntervalText (TextGrid me, int itier, long iinterval, const char32 *text);
PRAAT_LIB_EXPORT void TextGrid_insertPoint (TextGrid me, int itier, double t, const char32 *mark);
PRAAT_LIB_EXPORT void TextGrid_setPointText (TextGrid me, int itier, long ipoint, const char32 *text);

PRAAT_LIB_EXPORT void TextGrid_writeToChronologicalTextFile (TextGrid me, MelderFile file);
PRAAT_LIB_EXPORT autoTextGrid TextGrid_readFromChronologicalTextFile (MelderFile file);
PRAAT_LIB_EXPORT autoTextGrid TextGrid_readFromCgnSyntaxFile (MelderFile file);

PRAAT_LIB_EXPORT autoTable TextGrid_downto_Table (TextGrid me, bool includeLineNumbers, int timeDecimals, bool includeTierNames, bool includeEmptyIntervals);
void TextGrid_list (TextGrid me, bool includeLineNumbers, int timeDecimals, bool includeTierNames, bool includeEmptyIntervals);

void TextGrid_correctRoundingErrors (TextGrid me);
autoTextGrid TextGrids_concatenate (OrderedOf<structTextGrid>* me);

/* End of file TextGrid.h */
#endif
