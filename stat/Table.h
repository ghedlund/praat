#ifndef _Table_h_
#define _Table_h_
/* Table.h
 *
 * Copyright (C) 2002-2012,2014-2019,2021,2022 Paul Boersma
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

#include "Collection.h"
#include "Graphics.h"
Thing_declare (Interpreter);

#include "praatlib.h"

#include "Table_def.h"

void Table_initWithColumnNames (Table me, integer numberOfRows, constSTRVEC columnNames);
autoTable Table_createWithColumnNames (integer numberOfRows, constSTRVEC columnNames);
void Table_initWithoutColumnNames (Table me, integer numberOfRows, integer numberOfColumns);
PRAAT_LIB_EXPORT autoTable Table_createWithoutColumnNames (integer numberOfRows, integer numberOfColumns);
#define Table_create Table_createWithoutColumnNames

void Table_checkSpecifiedColumnNumbersWithinRange (Table me, constINTVECVU const& columnNumbers);

autoTable Tables_append (OrderedOf<structTable>* me);
PRAAT_LIB_EXPORT void Table_appendRow (Table me);
PRAAT_LIB_EXPORT void Table_appendColumn (Table me, conststring32 label);
PRAAT_LIB_EXPORT void Table_appendSumColumn (Table me, integer column1, integer column2, conststring32 label);
PRAAT_LIB_EXPORT void Table_appendDifferenceColumn (Table me, integer column1, integer column2, conststring32 label);
PRAAT_LIB_EXPORT void Table_appendProductColumn (Table me, integer column1, integer column2, conststring32 label);
PRAAT_LIB_EXPORT void Table_appendQuotientColumn (Table me, integer column1, integer column2, conststring32 label);
PRAAT_LIB_EXPORT void Table_removeRow (Table me, integer row);
PRAAT_LIB_EXPORT void Table_removeColumn (Table me, integer column);
PRAAT_LIB_EXPORT void Table_insertRow (Table me, integer row);
PRAAT_LIB_EXPORT void Table_insertColumn (Table me, integer column, conststring32 label /* cattable */);
PRAAT_LIB_EXPORT void Table_setColumnLabel (Table me, integer column, conststring32 label /* cattable */);
PRAAT_LIB_EXPORT integer Table_findColumnIndexFromColumnLabel (Table me, conststring32 label) noexcept;
PRAAT_LIB_EXPORT integer Table_getColumnIndexFromColumnLabel (Table me, conststring32 columnLabel);
integer Table_findColumnIndexFromColumnLabel (Table me, conststring32 label) noexcept;
integer Table_getColumnIndexFromColumnLabel (Table me, conststring32 columnLabel);
autoINTVEC Table_columnNamesToNumbers (Table me, constSTRVEC const& columnNames);
autoINTVEC Table_getColumnIndicesFromColumnLabelString (Table me, conststring32 string);
PRAAT_LIB_EXPORT integer Table_searchColumn (Table me, integer column, conststring32 value) noexcept;

/*
 * Procedure for reading strings or numbers from table cells:
 * use the following two calls exclusively.
 */
PRAAT_LIB_EXPORT conststring32 Table_getStringValue_Assert (Table me, integer row, integer column);
PRAAT_LIB_EXPORT double Table_getNumericValue_Assert (Table me, integer row, integer column);

/*
 * Procedure for writing strings or numbers into table cells:
 * use the following two calls exclusively.
 */
PRAAT_LIB_EXPORT void Table_setStringValue (Table me, integer rowNumber, integer columnNumber, conststring32 value /* cattable */);
PRAAT_LIB_EXPORT void Table_setNumericValue (Table me, integer row, integer column, double value);

/* For optimizations only (e.g. conversion to Matrix or TableOfReal). */
PRAAT_LIB_EXPORT void Table_numericize_Assert (Table me, integer columnNumber);

PRAAT_LIB_EXPORT double Table_getQuantile (Table me, integer column, double quantile);
PRAAT_LIB_EXPORT double Table_getSum (Table me, integer column);
PRAAT_LIB_EXPORT double Table_getMean (Table me, integer column);
PRAAT_LIB_EXPORT double Table_getMaximum (Table me, integer icol);
PRAAT_LIB_EXPORT double Table_getMinimum (Table me, integer icol);
PRAAT_LIB_EXPORT double Table_getGroupMean (Table me, integer column, integer groupColumn, conststring32 group);
PRAAT_LIB_EXPORT double Table_getStdev (Table me, integer column);
PRAAT_LIB_EXPORT integer Table_drawRowFromDistribution (Table me, integer column);
PRAAT_LIB_EXPORT double Table_getCorrelation_pearsonR (Table me, integer column1, integer column2, double significanceLevel,
	double *out_significance, double *out_lowerLimit, double *out_upperLimit);
PRAAT_LIB_EXPORT double Table_getCorrelation_kendallTau (Table me, integer column1, integer column2, double significanceLevel,
	double *out_significance, double *out_lowerLimit, double *out_upperLimit);
PRAAT_LIB_EXPORT double Table_getMean_studentT (Table me, integer column, double significanceLevel,
	double *out_tFromZero, double *out_numberOfDegreesOfFreedom, double *out_significanceFromZero, double *out_lowerLimit, double *out_upperLimit);
PRAAT_LIB_EXPORT double Table_getDifference_studentT (Table me, integer column1, integer column2, double significanceLevel,
	double *out_t, double *out_numberOfDegreesOfFreedom, double *out_significance, double *out_lowerLimit, double *out_upperLimit);
PRAAT_LIB_EXPORT double Table_getGroupMean_studentT (Table me, integer column, integer groupColumn, conststring32 group1, double significanceLevel,
	double *out_tFromZero, double *out_numberOfDegreesOfFreedom, double *out_significanceFromZero, double *out_lowerLimit, double *out_upperLimit);
PRAAT_LIB_EXPORT double Table_getGroupDifference_studentT (Table me, integer column, integer groupColumn, conststring32 group1, conststring32 group2, double significanceLevel,
	double *out_tFromZero, double *out_numberOfDegreesOfFreedom, double *out_significanceFromZero, double *out_lowerLimit, double *out_upperLimit);
PRAAT_LIB_EXPORT double Table_getGroupDifference_wilcoxonRankSum (Table me, integer column, integer groupColumn, conststring32 group1, conststring32 group2,
	double *out_rankSum, double *out_significanceFromZero);
//PRAAT_LIB_EXPORT double Table_getVarianceRatio (Table me, integer column1, integer column2, double significanceLevel,
//	double *out_significance, double *out_lowerLimit, double *out_upperLimit);
PRAAT_LIB_EXPORT bool Table_getExtrema (Table me, integer icol, double *minimum, double *maximum);

void Table_formula (Table me, integer column, conststring32 formula, Interpreter interpreter);
void Table_formula_columnRange (Table me, integer column1, integer column2, conststring32 expression, Interpreter interpreter);

void Table_sortRows_Assert (Table me, constINTVECVU const& columns);
void Table_sortRows (Table me, constSTRVEC columns);
PRAAT_LIB_EXPORT void Table_randomizeRows (Table me) noexcept;
PRAAT_LIB_EXPORT void Table_reflectRows (Table me) noexcept;

void Table_scatterPlot (Table me, Graphics g, integer xcolumn, integer ycolumn,
	double xmin, double xmax, double ymin, double ymax, integer markColumn, double fontSize, bool garnish);
void Table_scatterPlot_mark (Table me, Graphics g, integer xcolumn, integer ycolumn,
	double xmin, double xmax, double ymin, double ymax, double markSize_mm, conststring32 mark, bool garnish);
void Table_drawEllipse_e (Table me, Graphics g, integer xcolumn, integer ycolumn,
	double xmin, double xmax, double ymin, double ymax, double numberOfSigmas, bool garnish);

void Table_list (Table me, bool includeRowNumbers);

// allow C++ virtuals to be accessible via C linkage
#ifdef PRAAT_LIB
PRAAT_LIB_EXPORT double Table_getNrow (Table me);
PRAAT_LIB_EXPORT double Table_getNcol (Table me);
PRAAT_LIB_EXPORT conststring32 Table_getColStr (Table me, integer columnNumber);
PRAAT_LIB_EXPORT double Table_getMatrix (Table me, integer rowNumber, integer columnNumber);
PRAAT_LIB_EXPORT conststring32 Table_getMatrixStr (Table me, integer rowNumber, integer columnNumber);
PRAAT_LIB_EXPORT double Table_getColIndex  (Table me, conststring32 columnLabel);
#endif

PRAAT_LIB_EXPORT void Table_writeToTabSeparatedFile (Table me, MelderFile file);
PRAAT_LIB_EXPORT void Table_writeToCommaSeparatedFile (Table me, MelderFile file);
PRAAT_LIB_EXPORT void Table_writeToSemicolonSeparatedFile (Table me, MelderFile file);
PRAAT_LIB_EXPORT autoTable Table_readFromTableFile (MelderFile file);
PRAAT_LIB_EXPORT autoTable Table_readFromCharacterSeparatedTextFile (MelderFile file, char32 separator, bool interpretQuotes);

PRAAT_LIB_EXPORT autoTable Table_extractRowsWhereColumn_number (Table me, integer column, kMelder_number which, double criterion);
PRAAT_LIB_EXPORT autoTable Table_extractRowsWhereColumn_string (Table me, integer column, kMelder_string which, conststring32 criterion);
autoTable Table_collapseRows (Table me, constSTRVEC factors, constSTRVEC columnsToSum,
	constSTRVEC columnsToAverage, constSTRVEC columnsToMedianize,
	constSTRVEC columnsToAverageLogarithmically, constSTRVEC columnsToMedianizeLogarithmically);
autoTable Table_rowsToColumns (Table me, constSTRVEC const& factors_names, conststring32 columnToTranspose, constSTRVEC const& columnsToExpand_names);
PRAAT_LIB_EXPORT autoTable Table_transpose (Table me);

PRAAT_LIB_EXPORT void Table_checkSpecifiedRowNumberWithinRange (Table me, integer rowNumber);
PRAAT_LIB_EXPORT void Table_checkSpecifiedColumnNumberWithinRange (Table me, integer columnNumber);
PRAAT_LIB_EXPORT bool Table_isCellNumeric_ErrorFalse (Table me, integer rowNumber, integer columnNumber);
PRAAT_LIB_EXPORT bool Table_isColumnNumeric_ErrorFalse (Table me, integer columnNumber);

PRAAT_LIB_EXPORT conststring32 Table_messageColumn (Table me, integer column);

/* End of file Table.h */
#endif
