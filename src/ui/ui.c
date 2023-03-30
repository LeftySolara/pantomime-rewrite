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

#include "ui.h"

#include <curses.h>
#include <locale.h>

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
 * @brief Refreshes the currently visible window.
 */
void refresh_window()
{
    refresh();
}

/* Temporary fuction. Delete later. */
void write_text(const char *text)
{
    printw("%s\n", text);
}

/* Temporary fuction. Delete later. */
void wait_for_input()
{
    getch();
}
