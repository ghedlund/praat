/* TextGrid_def.h
 *
 * Copyright (C) 1992-2012,2014-2016,2018,2022 Paul Boersma
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

#include "praatlib.h"

#define ooSTRUCT TextPoint
oo_DEFINE_CLASS (TextPoint, AnyPoint)

	oo_STRING (mark)

oo_END_CLASS (TextPoint)
#undef ooSTRUCT
#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT conststring32 TextPoint_getText(TextPoint me);
#endif


#define ooSTRUCT TextInterval
oo_DEFINE_CLASS (TextInterval, Function)

	oo_STRING (text)

	#if oo_DECLARING
		int v_domainQuantity ()
			override { return MelderQuantity_TIME_SECONDS; }
	#endif

oo_END_CLASS (TextInterval)
#undef ooSTRUCT
#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT conststring32 TextInterval_getText(TextInterval me);
#endif

#define ooSTRUCT TextTier
oo_DEFINE_CLASS (TextTier, Function)   // a kind of AnyTier though

	oo_COLLECTION_OF (SortedSetOfDoubleOf, points, TextPoint, 0)

	#if oo_DECLARING
		AnyTier_METHODS

		int v_domainQuantity ()
			override { return MelderQuantity_TIME_SECONDS; }
	#endif

oo_END_CLASS (TextTier)
#undef ooSTRUCT
#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT integer TextTier_numberOfPoints (TextTier me);
PRAAT_LIB_EXPORT TextPoint TextTier_point (TextTier me, integer i);
PRAAT_LIB_EXPORT void TextTier_removePoints (TextTier me, kMelder_string which, conststring32 criterion);
PRAAT_LIB_EXPORT int TextTier_domainQuantity (TextTier me);
PRAAT_LIB_EXPORT void TextTier_shiftX (TextTier me, double xfrom, double xto);
PRAAT_LIB_EXPORT void TextTier_scaleX (TextTier me, double xminfrom, double xmaxfrom, double xminto, double xmaxto);
#endif


#define ooSTRUCT IntervalTier
oo_DEFINE_CLASS (IntervalTier, Function)

	oo_COLLECTION_OF (SortedSetOfDoubleOf, intervals, TextInterval, 0)

	#if oo_DECLARING
		int v_domainQuantity ()
			override { return MelderQuantity_TIME_SECONDS; }
		void v_shiftX (double xfrom, double xto)
			override;
		void v_scaleX (double xminfrom, double xmaxfrom, double xminto, double xmaxto)
			override;
	#endif

oo_END_CLASS (IntervalTier)
#undef ooSTRUCT
#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT integer IntervalTier_numberOfIntervals (IntervalTier me);
PRAAT_LIB_EXPORT TextInterval IntervalTier_interval (IntervalTier me, integer i);
PRAAT_LIB_EXPORT int IntervalTier_domainQuantity (IntervalTier me);
PRAAT_LIB_EXPORT void IntervalTier_shiftX (IntervalTier me, double xfrom, double xto);
PRAAT_LIB_EXPORT void IntervalTier_scaleX (IntervalTier me, double xminfrom, double xmaxfrom, double xminto, double xmaxto);

// 'unsafe' addition of interval to end of internal list
PRAAT_LIB_EXPORT void IntervalTier_addInterval (IntervalTier me, double tmin, double tmax, conststring32 label);
PRAAT_LIB_EXPORT void IntervalTier_removeInterval (IntervalTier me, integer iinterval);
#endif

#define ooSTRUCT TextGrid
oo_DEFINE_CLASS (TextGrid, Function)

	oo_OBJECT (FunctionList, 0, tiers)   // TextTier and IntervalTier objects

	#if oo_DECLARING
		void v1_info ()
			override;
		void v_repair ()
			override;
		int v_domainQuantity ()
			override { return MelderQuantity_TIME_SECONDS; }
		void v_shiftX (double xfrom, double xto)
			override;
		void v_scaleX (double xminfrom, double xmaxfrom, double xminto, double xmaxto)
			override;

		IntervalTier intervalTier_cast (int32 tierNumber) {
			return static_cast <IntervalTier> (our tiers -> at [tierNumber]);
		}
		TextTier textTier_cast (int32 tierNumber) {
			return static_cast <TextTier> (our tiers -> at [tierNumber]);
		}
	#endif

oo_END_CLASS (TextGrid)
#undef ooSTRUCT
#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT integer TextGrid_numberOfTiers (TextGrid me);
PRAAT_LIB_EXPORT Function TextGrid_tier (TextGrid me, integer i);
PRAAT_LIB_EXPORT void TextGrid_removePoints (TextGrid me, integer tierNumber, kMelder_string which, conststring32 criterion);
PRAAT_LIB_EXPORT void TextGrid_repair (TextGrid me);
PRAAT_LIB_EXPORT int TextGrid_domainQuantity (TextGrid me);
PRAAT_LIB_EXPORT void TextGrid_shiftX (TextGrid me, double xfrom, double xto);
PRAAT_LIB_EXPORT void TextGrid_scaleX (TextGrid me, double xminfrom, double xmaxfrom, double xminto, double xmaxto);
#endif


/* End of file TextGrid_def.h */
