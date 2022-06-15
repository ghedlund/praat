/* EEGWindow.cpp
 *
 * Copyright (C) 2011-2018,2021,2022 Paul Boersma
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

#include "EEGWindow.h"
#include "EditorM.h"

Thing_implement (EEGWindow, TextGridEditor, 0);

#include "Prefs_define.h"
#include "EEGWindow_prefs.h"
#include "Prefs_install.h"
#include "EEGWindow_prefs.h"
#include "Prefs_copyToInstance.h"
#include "EEGWindow_prefs.h"

static void menu_cb_EEGWindowHelp (EEGWindow, EDITOR_ARGS_DIRECT) { Melder_help (U"EEG window"); }

void structEEGWindow :: v_createMenus () {
	EEGWindow_Parent :: v_createMenus ();
}

void structEEGWindow :: v_createHelpMenuItems (EditorMenu menu) {
	TextGridEditor_Parent :: v_createHelpMenuItems (menu);
	EditorMenu_addCommand (menu, U"EEGWindow help", '?', menu_cb_EEGWindowHelp);
}

static void CONVERT_DATA_TO_ONE__ExtractSelectedEEG_preserveTimes (EEGWindow me, EDITOR_ARGS_DIRECT_WITH_OUTPUT) {
	CONVERT_DATA_TO_ONE
		if (my endSelection <= my startSelection)
			Melder_throw (U"No selection.");
		autoEEG result = EEG_extractPart (my eeg(), my startSelection, my endSelection, true);
	CONVERT_DATA_TO_ONE_END (U"untitled")
}

static void CONVERT_DATA_TO_ONE__ExtractSelectedEEG_timeFromZero (EEGWindow me, EDITOR_ARGS_DIRECT_WITH_OUTPUT) {
	CONVERT_DATA_TO_ONE
		if (my endSelection <= my startSelection)
			Melder_throw (U"No selection.");
		autoEEG result = EEG_extractPart (my eeg(), my startSelection, my endSelection, false);
	CONVERT_DATA_TO_ONE_END (U"untitled")
}

void structEEGWindow :: v_createMenuItems_file_extract (EditorMenu menu) {
	EEGWindow_Parent :: v_createMenuItems_file_extract (menu);
	our extractSelectedEEGPreserveTimesButton = EditorMenu_addCommand (menu, U"Extract selected EEG (preserve times)", 0,
			CONVERT_DATA_TO_ONE__ExtractSelectedEEG_preserveTimes);
	our extractSelectedEEGTimeFromZeroButton = EditorMenu_addCommand (menu, U"Extract selected EEG (time from zero)", 0,
			CONVERT_DATA_TO_ONE__ExtractSelectedEEG_timeFromZero);
}

void structEEGWindow :: v_updateMenuItems_file () {
	EEGWindow_Parent :: v_updateMenuItems_file ();
	GuiThing_setSensitive (our extractSelectedEEGPreserveTimesButton, our endSelection > our startSelection);
	GuiThing_setSensitive (our extractSelectedEEGTimeFromZeroButton,  our endSelection > our startSelection);
}

autoEEGWindow EEGWindow_create (conststring32 title, EEG eeg) {
	try {
		autoEEGWindow me = Thing_new (EEGWindow);
		my soundArea = EEGArea_create (me.get(),
			eeg -> sound.get(),
			eeg   // BUG: quick fix, because `eeg` should not be contained in the SoundArea
		);
		TextGridEditor_init (me.get(), title,
			eeg -> textgrid.get(),   // BUG: quick fix, because the actual data should be `eeg` (solved as soon as TextGridArea exists)
			nullptr,   // no spelling checker
			nullptr   // no callback socket
		);
		return me;
	} catch (MelderError) {
		Melder_throw (U"EEG window not created.");
	}
}

/* End of file EEGWindow.cpp */
