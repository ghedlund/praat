#ifndef _praat_uvafon_h_
#define _praat_uvafon_h_
/* praat_uvafon.h
 *
 * Copyright (C) 2016,2021 Paul Boersma
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

#include "praatM.h"

void praat_uvafon_init ();
void praat_uvafon_TextGrid_init ();

#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT void praat_lib_uvafon_init();
#endif

#endif
/* End of file praat_uvafon.h */
