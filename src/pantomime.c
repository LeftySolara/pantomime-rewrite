/*******************************************************************************
 * pantomime.c
 *******************************************************************************
 * Copyright (C) 2019-2023 Julianne Adams
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "arguments.h"
#include "mpdwrapper.h"

int main(int argc, char *argv[])
{
    struct arguments arguments = parse_arguments(argc, argv);
    /*
      setlocale(LC_ALL, "");
      initscr();

      cbreak();
      noecho();
      curs_set(0);
      // nodelay(stdscr, TRUE);
      keypad(stdscr, TRUE);

      printw("Hello World!");
      refresh();

      getch();
      endwin();
    */

    struct mpdwrapper *mpd = mpdwrapper_new(arguments.host, arguments.port, 0);
    if (!mpd) {
        fprintf(stderr, "Error connecting to MPD.\n");
        exit(EXIT_FAILURE);
    }

    mpdwrapper_print_queue(mpd);
    mpdwrapper_free(mpd);

    return 0;
}
