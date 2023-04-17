/*******************************************************************************
 * mpdclient.c
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

#include "pantomime/mpd/client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Creates a new connection to an MPD server.
 *
 * @param host The server's hostname, IP address, or Unix socket path.
 * @param port The TCP port to connect to (0 for default). If "host" is a Unix socket path, this
 * parameter is ignored.
 *
 * @return An @ref mpdclient object (which may have failed to connect), or NULL on out-of-memory.
 */
struct mpdclient *mpdclient_new(const char *host, unsigned int port, unsigned int timeout)
{
    struct mpdclient *mpd = malloc(sizeof(*mpd));
    if (!mpd) {
        return NULL;
    }

    mpd->connection = NULL;
    mpd->queue = NULL;

    mpd->connection = mpd_connection_new(host, port, timeout);

    if (mpd_connection_get_error(mpd->connection) != MPD_ERROR_SUCCESS) {
        const char *error_message = mpd_connection_get_error_message(mpd->connection);
        fprintf(stderr, "MPD error: %s\n", error_message);

        mpdclient_free(mpd);
        return NULL;
    }

    mpd->queue = songlist_new();

    /* Fetch the queue */
    struct mpd_song *song;
    while ((song = mpd_recv_song(mpd->connection)) != NULL) {
        songlist_append(mpd->queue, song);
    }
    mpd_response_finish(mpd->connection);

    mpd->last_error = mpd_connection_get_error(mpd->connection);

    return mpd;
}

/**
 * @brief Closes the connection and frees all memory used by an @ref mpdclient object.
 *
 * @param mpd The connection to MPD.
 */
void mpdclient_free(struct mpdclient *mpd)
{
    if (!mpd) {
        return;
    }

    if (mpd->connection) {
        mpd_connection_free(mpd->connection);
    }
    if (mpd->queue) {
        songlist_free(mpd->queue);
    }

    free(mpd);
}

/**
 * @brief Returns a human-readable string describing the most recent MPD error.
 *
 * @return A human-readable string, or NULL if no error has occurred.
 */
const char *mpdclient_get_last_error_message(struct mpdclient *mpd)
{
    if (mpd->last_error == MPD_ERROR_SUCCESS) {
        return NULL;
    }

    return mpd_connection_get_error_message(mpd->connection);
}

/**
 * @brief Get a song's title.
 *
 * @param song The song to query.
 *
 * @return A dynamically-allocated string containing the song's title.
 *
 * This function returns a string that is dynamically-allocated, as if
 * malloc() were called. The caller is responsible for freeing the memory
 * used by this string.
 */
char *mpdclient_get_song_title(struct mpd_song *song)
{
    const char *title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);

    char *return_value = malloc(sizeof(char) * strlen(title));
    strcpy(return_value, title);  // NOLINT

    return return_value;
}

/**
 * @brief Get the name of a song's artist.
 *
 * @param song The song to query.
 *
 * @return A dynamically-allocated string containing the name of the song's artist.
 *
 * This function returns a string that is dynamically-allocated, as if
 * malloc() were called. The caller is responsible for freeing the memory
 * used by this string.
 */
char *mpdclient_get_song_artist(struct mpd_song *song)
{
    const char *artist = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);

    char *return_value = malloc(sizeof(char) * strlen(artist));
    strcpy(return_value, artist);  // NOLINT

    return return_value;
}

/**
 * @brief Get the name of the album a song belongs to.
 *
 * @param song The song to query.
 *
 * @return A dynamically-allocated string containing the name of the song's album name.
 *
 * This function returns a string that is dynamically-allocated, as if
 * malloc() were called. The caller is responsible for freeing the memory
 * used by this string.
 */
char *mpdclient_get_song_album(struct mpd_song *song)
{
    const char *album = mpd_song_get_tag(song, MPD_TAG_ALBUM, 0);

    char *return_value = malloc(sizeof(char) * strlen(album));
    strcpy(return_value, album);  // NOLINT

    return return_value;
}

/**
 * @brief Get the length of a song.
 *
 * @param song The song to query.
 *
 * @return An unsigned integer representing the song's length in seconds.
 */
unsigned mpdclient_get_song_length(struct mpd_song *song)
{
    return mpd_song_get_duration(song);
}
