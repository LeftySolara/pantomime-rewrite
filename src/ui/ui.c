/*******************************************************************************
 * ui.c - General user interface functions
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
 *
 * @brief Functions for manipulating the overall UI comonent of the program.
 */

#include "pantomime/ui/ui.h"

#include <curses.h>
#include <locale.h>
#include <panel.h>
#include <stdlib.h>

enum ui_panel default_panel = QUEUE;

/**
 * @brief Creates and initializes the UI.
 */
struct ui *ui_new()
{
    struct ui *ui = malloc(sizeof(*ui));
    if (!ui) {
        return NULL;
    }

    getmaxyx(stdscr, ui->maxy, ui->maxx);

    ui->panels = create_panels(NUM_PANELS, ui->maxx, ui->maxy - STATUSBAR_HEIGHT);
    ui->queue_screen = queue_screen_new(panel_window(ui->panels[QUEUE]));

    ui->visible_panel = default_panel;
    top_panel(ui->panels[ui->visible_panel]);

    return ui;
}

/**
 * @brief Tears down and frees memory used by the UI.
 *
 * @param ui A pointer to the UI to tear down.
 */
void ui_free(struct ui *ui)
{
    destroy_panels(ui->panels, NUM_PANELS);
    queue_screen_free(ui->queue_screen);
    free(ui);
}

/**
 * @brief Starts ncurses.
 */
void start_curses()
{
    setlocale(LC_ALL, "");
    initscr();

    cbreak();
    noecho();
    curs_set(0);
    // nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

/**
 * @brief Stops ncurses.
 */
void stop_curses()
{
    endwin();
}

/**
 * @brief Creates an array of panels to display in the UI.
 *
 * @param num_panels The number of panels to create.
 * @param width The width of the panels.
 * @param height The height of the panels.
 *
 * @return An array of PANEL pointers.
 */
PANEL **create_panels(int num_panels, int width, int height)
{
    PANEL **panels = malloc(sizeof(PANEL *) * num_panels);
    WINDOW *win;

    for (int i = 0; i < num_panels; ++i) {
        win = newwin(height, width, 0, 0);
        panels[i] = new_panel(win);
    }

    return panels;
}

/**
 * @brief Frees memory used by UI panels.
 *
 * @param panels The panels to destroy.
 * @param num_panels The number of panels to destroy.
 */
void destroy_panels(PANEL **panels, int num_panels)
{
    WINDOW *win;

    for (int i = 0; i < num_panels; ++i) {
        win = panel_window(panels[i]);
        del_panel(panels[i]);
        delwin(win);
    }
    free(panels);
}

/**
 * @brief Sets the given panel as visible.
 *
 * @param ui A pointer to the UI struct.
 * @param panel The panel to make visible.
 */
void ui_set_visible_panel(struct ui *ui, enum ui_panel panel)
{
    ui->visible_panel = panel;
    top_panel(ui->panels[panel]);
}

/**
 * @brief Draws the UI on the screen.
 *
 * @param ui A pointer to a struct containing UI information.
 * @param mpd A connection to the MPD server.
 */
void ui_draw(struct ui *ui, struct mpdclient *mpd)
{
    WINDOW *win = panel_window(ui->panels[ui->visible_panel]);
    wclear(win);

    switch (ui->visible_panel) {
        case HELP:
            wprintw(win, "HELP Screen");
            break;
        case QUEUE:
            queue_screen_draw(ui->queue_screen, mpd->queue);
            break;
        case LIBRARY:
            wprintw(win, "LIBRARY Screen");
            break;
        default:
            break;
    }

    update_panels();
    doupdate();
}
