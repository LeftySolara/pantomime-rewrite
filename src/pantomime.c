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

#include <stdio.h>
#include <stdlib.h>

#include "arguments.h"
#include "command/command.h"
#include "pantomime/mpd/client.h"
#include "pantomime/ui/ui.h"
#include "ui/screens/queue_screen.h"

int main(int argc, char *argv[])
{
    struct arguments arguments = parse_arguments(argc, argv);

    struct mpdclient *mpd = mpdclient_new(arguments.host, arguments.port, 0);
    if (!mpd) {
        fprintf(stderr, "Error connecting to MPD.\n");
        exit(EXIT_FAILURE);
    }

    start_curses();

    /*
    struct queue_screen *queue_screen = malloc(sizeof(*queue_screen));
    queue_screen->win = stdscr;

    queue_screen_draw_songlist(queue_screen, mpd->queue);
    */

    struct ui *ui = ui_new();
    ui_draw(ui);

    int ch;
    enum command_type cmd_type = CMD_NULL;

    while (cmd_type != CMD_QUIT) {
        ch = getch();
        cmd_type = find_key_command(ch);

        switch (ch) {
            case '1':
                ui_set_visible_panel(ui, HELP);
                break;
            case '2':
                ui_set_visible_panel(ui, QUEUE);
                break;
            case '3':
                ui_set_visible_panel(ui, LIBRARY);
                break;
            default:
                break;
        }

        switch (ui->visible_panel) {
            case HELP:
                break;
            case QUEUE:
                break;
            case LIBRARY:
                break;
            default:
                break;
        }

        ui_draw(ui);
    }

    stop_curses();

    ui_free(ui);

    /* free(queue_screen); */
    mpdclient_free(mpd);

    return 0;
}
