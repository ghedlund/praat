#ifndef _TableOfReal_h_
#define _TableOfReal_h_
/* TableOfReal.h
 *
 * Copyright (C) 1992-2005,2007,2009,2011,2012,2015-2018,2021 Paul Boersma
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

/* TableOfReal inherits from Data */
#include "Collection.h"
#include "Strings_.h"
#include "Table.h"
Thing_declare (Interpreter);

#include "TableOfReal_def.h"

#include "praatlib.h"

PRAAT_LIB_EXPORT void TableOfReal_init (TableOfReal me, integer numberOfRows, integer numberOfColumns);
PRAAT_LIB_EXPORT autoTableOfReal TableOfReal_create (integer numberOfRows, integer numberOfColumns);
PRAAT_LIB_EXPORT void TableOfReal_removeRow (TableOfReal me, integer rowNumber);
PRAAT_LIB_EXPORT void TableOfReal_removeColumn (TableOfReal me, integer columnNumber);
PRAAT_LIB_EXPORT void TableOfReal_insertRow (TableOfReal me, integer rowNumber);
PRAAT_LIB_EXPORT void TableOfReal_insertColumn (TableOfReal me, integer columnNumber);
PRAAT_LIB_EXPORT void TableOfReal_setRowLabel    (TableOfReal me, integer rowNumber, conststring32 label /* cattable */);
PRAAT_LIB_EXPORT void TableOfReal_setColumnLabel (TableOfReal me, integer columnNumber, conststring32 label /* cattable */);
PRAAT_LIB_EXPORT integer TableOfReal_rowLabelToIndex    (TableOfReal me, conststring32 label /* cattable */);
PRAAT_LIB_EXPORT integer TableOfReal_columnLabelToIndex (TableOfReal me, conststring32 label /* cattable */);
PRAAT_LIB_EXPORT double TableOfReal_getColumnMean (TableOfReal me, integer columnNumber);
PRAAT_LIB_EXPORT double TableOfReal_getColumnStdev (TableOfReal me, integer columnNumber);

PRAAT_LIB_EXPORT autoTableOfReal Table_to_TableOfReal (Table me, integer labelColumn);
PRAAT_LIB_EXPORT autoTable TableOfReal_to_Table (TableOfReal me, conststring32 labelOfFirstColumn);
void TableOfReal_formula (TableOfReal me, conststring32 expression, Interpreter interpreter, TableOfReal target);
void TableOfReal_drawAsNumbers (TableOfReal me, Graphics g, integer rowmin, integer rowmax, int iformat, int precision);
void TableOfReal_drawAsNumbers_if (TableOfReal me, Graphics g, integer rowmin, integer rowmax, int iformat, int precision,
	conststring32 conditionFormula, Interpreter interpreter);
void TableOfReal_drawAsSquares (TableOfReal me, Graphics g, integer rowmin, integer rowmax,
	integer colmin, integer colmax, bool garnish);
void TableOfReal_drawVerticalLines (TableOfReal me, Graphics g, integer rowmin, integer rowmax);
void TableOfReal_drawHorizontalLines (TableOfReal me, Graphics g, integer rowmin, integer rowmax);
void TableOfReal_drawLeftAndRightLines (TableOfReal me, Graphics g, integer rowmin, integer rowmax);
void TableOfReal_drawTopAndBottomLines (TableOfReal me, Graphics g, integer rowmin, integer rowmax);

PRAAT_LIB_EXPORT autoTableOfReal TablesOfReal_append (TableOfReal me, TableOfReal thee);
autoTableOfReal TablesOfReal_appendMany (OrderedOf<structTableOfReal>* me);
PRAAT_LIB_EXPORT void TableOfReal_sortByLabel (TableOfReal me, integer column1, integer column2);
PRAAT_LIB_EXPORT void TableOfReal_sortByColumn (TableOfReal me, integer column1, integer column2);

PRAAT_LIB_EXPORT void TableOfReal_writeToHeaderlessSpreadsheetFile (TableOfReal me, MelderFile file);
PRAAT_LIB_EXPORT autoTableOfReal TableOfReal_readFromHeaderlessSpreadsheetFile (MelderFile file);

autoTableOfReal TableOfReal_extractRowsByNumber (TableOfReal me, constINTVECVU const& rowNumbers);
autoTableOfReal TableOfReal_extractColumnsByNumber (TableOfReal me, constINTVECVU const& columnNumbers);

PRAAT_LIB_EXPORT autoTableOfReal TableOfReal_extractRowsWhereColumn (TableOfReal me, integer icol, kMelder_number which, double criterion);
PRAAT_LIB_EXPORT autoTableOfReal TableOfReal_extractColumnsWhereRow (TableOfReal me, integer icol, kMelder_number which, double criterion);

PRAAT_LIB_EXPORT autoTableOfReal TableOfReal_extractRowsWhoseLabel (TableOfReal me, kMelder_string which, conststring32 criterion);
PRAAT_LIB_EXPORT autoTableOfReal TableOfReal_extractColumnsWhoseLabel (TableOfReal me, kMelder_string which, conststring32 criterion);

PRAAT_LIB_EXPORT autoTableOfReal TableOfReal_extractRowsWhere (TableOfReal me, conststring32 condition, Interpreter interpreter);
PRAAT_LIB_EXPORT autoTableOfReal TableOfReal_extractColumnsWhere (TableOfReal me, conststring32 condition, Interpreter interpreter);

PRAAT_LIB_EXPORT autoStrings TableOfReal_extractRowLabelsAsStrings (TableOfReal me);
PRAAT_LIB_EXPORT autoStrings TableOfReal_extractColumnLabelsAsStrings (TableOfReal me);

#pragma mark - class TableOfRealList

Collection_define (TableOfRealList, OrderedOf, TableOfReal) {
};

/* End of file TableOfReal.h */
#endif
