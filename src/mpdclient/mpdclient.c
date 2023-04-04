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

#include "mpdclient.h"

#include <stdio.h>
#include <stdlib.h>

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

    mpd->connection = mpd_connection_new(host, port, timeout);

    /* Unable to connect to MPD */
    if (mpd_connection_get_error(mpd->connection) != MPD_ERROR_SUCCESS) {
        const char *error_message = mpd_connection_get_error_message(mpd->connection);
        fprintf(stderr, "MPD error: %s\n", error_message);

        mpdclient_free(mpd);
        return NULL;
    }

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
