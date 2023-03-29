/*******************************************************************************
 * mpdwrapper.h
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

#ifndef MPDWRAPPER_H
#define MPDWRAPPER_H

#include <mpd/client.h>

/**
 * @brief Holds information about the current MPD server connection.
 *
 * This struct contains information about the current MPD server connection.
 * With this struct, we are able to keep track of the connection state
 * without having to make continual (often unnecessary) server requests.
 */
struct mpdwrapper {
    struct mpd_connection *connection;
    enum mpd_error last_error;
};

struct mpdwrapper *mpdwrapper_new(const char *host, unsigned int port, unsigned int timeout);
void mpdwrapper_free(struct mpdwrapper *mpdwrapper);

const char *mpdwrapper_get_last_error_message(struct mpdwrapper *mpd);

#endif /* MPDWRAPPER_H */
