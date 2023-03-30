/*******************************************************************************
 * mpdwrapper.c
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
 * @file mpdwrapper.h
 */

#include "mpdwrapper.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Creates a new connection to an MPD server.
 *
 * @param host The MPD server host to connect to.
 * @param port The port MPD is running on.
 * @param timeout The MPD timeout.
 *
 * @return Pointer to an mpdwrapper struct.
 */
struct mpdwrapper *mpdwrapper_new(const char *host, unsigned int port, unsigned int timeout)
{
    struct mpdwrapper *mpd = malloc(sizeof(*mpd));
    if (!mpd) {
        return NULL;
    }

    mpd->connection = mpd_connection_new(host, port, timeout);

    /* Unable to connect to MPD */
    if (mpd_connection_get_error(mpd->connection) != MPD_ERROR_SUCCESS) {
        const char *error_message = mpd_connection_get_error_message(mpd->connection);
        fprintf(stderr, "MPD error: %s\n", error_message);

        mpdwrapper_free(mpd);
        return NULL;
    }

    mpd->last_error = mpd_connection_get_error(mpd->connection);

    return mpd;
}

/**
 * @brief Frees memory used by an mpdwrapper struct.
 */
void mpdwrapper_free(struct mpdwrapper *mpd)
{
    if (!mpd) {
        return;
    }

    if (mpd->connection) {
        mpd_connection_free(mpd->connection);
    }

    free(mpd);
}

/* @brief Get the last error message encountered by MPD. */
const char *mpdwrapper_get_last_error_message(struct mpdwrapper *mpd)
{
    if (mpd->last_error == MPD_ERROR_SUCCESS) {
        return NULL;
    }

    return mpd_connection_get_error_message(mpd->connection);
}
