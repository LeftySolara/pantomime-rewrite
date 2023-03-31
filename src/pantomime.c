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
#include "mpdclient.h"
#include "ui/screens/queue_screen.h"
#include "ui/ui.h"

int main(int argc, char *argv[])
{
    struct arguments arguments = parse_arguments(argc, argv);

    struct mpdclient *mpd = mpdclient_new(arguments.host, arguments.port, 0);
    if (!mpd) {
        fprintf(stderr, "Error connecting to MPD.\n");
        exit(EXIT_FAILURE);
    }

    start_curses();

    struct mpd_song *song;
    mpd_send_list_queue_meta(mpd->connection);
    while ((song = mpd_recv_song(mpd->connection)) != NULL) {
        const char *song_title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);
        const char *song_artist = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);
        const char *song_album = mpd_song_get_tag(song, MPD_TAG_ALBUM, 0);
        unsigned song_length = mpd_song_get_duration(song);

        queue_screen_write_song_info(stdscr, song_title, song_artist, song_album, song_length);
        wprintw(stdscr, "\n");

        mpd_song_free(song);
    }
    mpd_response_finish(mpd->connection);

    refresh_window();
    wait_for_input();

    stop_curses();

    mpdclient_free(mpd);

    return 0;
}
