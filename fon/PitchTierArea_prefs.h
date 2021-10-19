/* PitchTierArea_prefs.h
 *
 * Copyright (C) 2012,2014-2016,2020,2021 Paul Boersma
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

prefs_begin (PitchTierArea)

	prefs_override_double (PitchTierArea, dataFreeMinimum, 1, U"50.0")   // Hz
	prefs_override_double (PitchTierArea, dataFreeMaximum, 1, U"300.0")   // Hz

prefs_end (PitchTierArea)

/* End of file PitchTierArea_prefs.h */
