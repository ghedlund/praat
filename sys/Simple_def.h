/* Simple_def.h
 *
 * Copyright (C) 1992-2012,2015,2017 Paul Boersma
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

#define ooSTRUCT SimpleInteger
oo_DEFINE_CLASS (SimpleInteger, Daata)
	oo_INTEGER (number)
oo_END_CLASS (SimpleInteger)
#undef ooSTRUCT
#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT integer SimpleInteger_getNumber(SimpleInteger me);
PRAAT_LIB_EXPORT void SimpleInteger_setNumber(SimpleInteger me, integer number);
#endif

#define ooSTRUCT SimpleDouble
oo_DEFINE_CLASS (SimpleDouble, Daata)
	oo_DOUBLE (number)
oo_END_CLASS (SimpleDouble)
#undef ooSTRUCT
#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT double SimpleDouble_getNumber(SimpleDouble me);
PRAAT_LIB_EXPORT void SimpleDouble_setNumber(SimpleDouble me, double number);
#endif

#define ooSTRUCT SimpleString
oo_DEFINE_CLASS (SimpleString, Daata)
	oo_STRING (string)
oo_END_CLASS (SimpleString)
#undef ooSTRUCT
#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT conststring32 SimpleString_getString(SimpleString me);
PRAAT_LIB_EXPORT void SimpleString_setString(SimpleString me, conststring32 string);
#endif

/* End of file Simple_def.h */
