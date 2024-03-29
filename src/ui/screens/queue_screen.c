/*******************************************************************************
 * queue_screen.c - Functions for displaying the MPD queue
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
 * @file queue_screen.h
 */

#include "pantomime/ui/queue_screen.h"

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief The length of the a string that displays time. i.e., something like 12:54.
 *
 * The length is calculated based on the maximum number of digits in an unsigned short,
 * plus a colon, two more digits, and a null terminator.
 */
#define TIME_STRING_LENGTH 9

/**
 * @brief Creates a new queue screen instance.
 *
 * This function initializes a window meant to be used to display the MPD queue.
 * If the "win" parameter is NULL, a new window is created from stdscr.
 *
 * @param win The NCURSES window to assign to the screen.
 */
struct queue_screen *queue_screen_new(WINDOW *win)
{
    struct queue_screen *screen = malloc(sizeof(*screen));
    if (!screen) {
        return NULL;
    }

    if (win) {
        screen->win = win;
    }
    else {
        screen->win = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
    }

    return screen;
}

/**
 * @brief Frees memory used by a queue screen.
 *
 * @param screen The queue screen to free.
 */
void queue_screen_free(struct queue_screen *screen)
{
    if (!screen) {
        return;
    }

    delwin(screen->win);
    free(screen);
}

/**
 * @brief Creates a string representation of a length of time.
 *
 * Creates a string in the format minutes:seconds and stores it in @p buffer.
 *
 * @param buffer A dynamically-allocated buffer for storing the result string.
 * @param length The length of time to convert to a string.
 */
void queue_screen_create_label_time(char *buffer, unsigned length)
{
    unsigned short minutes = length / 60;
    unsigned short seconds = length % 60;

    snprintf(buffer, TIME_STRING_LENGTH, "%d:%02d", minutes, seconds);  // NOLINT
}

/**
 * @brief Writes song information on the screen.
 *
 * This function writes a song's title, artist, album, and length on the given window.
 * Note that calling this function does **not** refresh the screen.
 *
 * @param win The window to draw on.
 * @param title The title of the song.
 * @param artist The song's artist.
 * @param album The album the song appears on.
 * @param length The length of the song in seconds.
 */
void queue_screen_write_song_info(WINDOW *win, const char *title, const char *artist,
                                  const char *album, unsigned int length)
{
    char *label_time = malloc(sizeof(char) * TIME_STRING_LENGTH);
    queue_screen_create_label_time(label_time, length);

    /* TODO: Temorary formatting. Will create nicely-formatted rows later. */
    wprintw(win, "%s    %s    %s    %s\n", artist, title, album, label_time);

    free(label_time);
}

/**
 * @brief Draws the contents of a queue screen to its window.
 *
 * @param screen The queue screen to draw.
 * @param queue A link list containing the songs in the queue.
 */
void queue_screen_draw(struct queue_screen *screen, struct linkedlist *queue)
{
    int list_length = linkedlist_get_length(queue);
    struct mpd_song *song;

    for (int i = 0; i < list_length; ++i) {
        song = linkedlist_at(queue, i);
        const char *title = mpdclient_get_song_title(song);
        const char *artist = mpdclient_get_song_artist(song);
        const char *album = mpdclient_get_song_album(song);
        unsigned length = mpdclient_get_song_length(song);

        queue_screen_write_song_info(screen->win, title, artist, album, length);
    }

    wnoutrefresh(screen->win);
}
