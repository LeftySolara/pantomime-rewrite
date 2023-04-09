/*******************************************************************************
 * ui.h - General user interface functions
 *******************************************************************************
 * Copyright (C) 2019-2023 Julianne Adams
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

/**
 * @file ui.h
 */

#ifndef UI_H
#define UI_H

#include <panel.h>

#define STATUSBAR_HEIGHT 2

enum ui_panel { HELP, QUEUE, LIBRARY, NUM_PANELS };

struct ui {
    PANEL **panels;
    enum ui_panel visible_panel;

    int maxx;
    int maxy;
};

struct ui *ui_new();
void ui_free(struct ui *ui);

void start_curses();
void stop_curses();

PANEL **create_panels(int num_panels, int width, int height);
void destroy_panels(PANEL **panels, int num_panels);

void ui_draw(struct ui *ui);

#endif /* UI_H */
