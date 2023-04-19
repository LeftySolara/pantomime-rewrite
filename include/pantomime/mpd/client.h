/*******************************************************************************
 * mpdclient.h
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

/**
 * @file mpdclient.h
 */

#ifndef MPDCLIENT_H 
#define MPDCLIENT_H

#include <mpd/client.h>

#include "pantomime/linkedlist.h"

/**
 * @brief Holds information about the current MPD server connection.
 *
 * This struct contains information about the current MPD server connection.
 * With this struct, we are able to keep track of the connection state
 * without having to make continual (often unnecessary) server requests.
 */
struct mpdclient {
    struct mpd_connection *connection;
    struct linkedlist *queue;

    enum mpd_error last_error;
};

struct mpdclient *mpdclient_new(const char *host, unsigned int port, unsigned int timeout);
void mpdclient_free(struct mpdclient *mpdclient);
void mpdclient_song_free(void *);

const char *mpdclient_get_last_error_message(struct mpdclient *mpd);

char *mpdclient_get_song_title(struct mpd_song *song);
char *mpdclient_get_song_artist(struct mpd_song *song);
char *mpdclient_get_song_album(struct mpd_song *song);
unsigned mpdclient_get_song_length(struct mpd_song *song);

#endif /* MPDCLIENT_H */
