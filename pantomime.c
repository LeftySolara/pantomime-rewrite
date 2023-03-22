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


#include <mpd/client.h>
#include <stdio.h>

int main()
{
    struct mpd_connection *conn = mpd_connection_new("127.0.0.1", 6600, 0);

    if (!conn) {
        printf("Out of memory!\n");
        return 1;
    }
    if (mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS) {
        printf("Failed to connect to MPD\n");
        return 1;
    }
    
    /* Print a list of all songs in the queue. */
    struct mpd_song *song;
    mpd_send_list_queue_meta(conn);
    while ((song = mpd_recv_song(conn)) != NULL) {
        const char *song_title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);
        printf("%s\n", song_title);
        mpd_song_free(song);
    }

    mpd_response_finish(conn);
    mpd_connection_free(conn);
}
