/* Sound_and_Spectrum.h
 *
 * Copyright (C) 1992-2011,2015 Paul Boersma
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

#include "Sound.h"
#include "Spectrum.h"
Thing_declare (Interpreter);

#ifdef PRAAT_LIB
#include "praatlib.h"
#endif

PRAAT_LIB_EXPORT autoSpectrum Sound_to_Spectrum_at (Sound me, double tim, double windowDuration, int windowType);

PRAAT_LIB_EXPORT autoSpectrum Sound_to_Spectrum (Sound me, int fast);
PRAAT_LIB_EXPORT autoSound Spectrum_to_Sound (Spectrum me);

PRAAT_LIB_EXPORT autoSpectrum Spectrum_lpcSmoothing (Spectrum me, int numberOfPeaks, double preemphasisFrequency);

PRAAT_LIB_EXPORT autoSound Sound_filter_passHannBand (Sound me, double fmin, double fmax, double smooth);
PRAAT_LIB_EXPORT autoSound Sound_filter_stopHannBand (Sound me, double fmin, double fmax, double smooth);
PRAAT_LIB_EXPORT autoSound Sound_filter_formula (Sound me, const char32 *formula, Interpreter interpreter);

/* End of file Sound_and_Spectrum.h */
