/*******************************************************************************
 * queue_screen.h - Functions for displaying the MPD queue
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

#include <curses.h>

#include "pantomime/linkedlist.h"
#include "pantomime/mpd/client.h"

struct queue_screen_row {
    
    char *song_title;
    char *song_artist;
    char *song_album;
    unsigned song_length;
    unsigned selected;
};

struct queue_screen {
    WINDOW *win;
};

struct queue_screen *queue_screen_new(WINDOW *win);
void queue_screen_free(struct queue_screen *screen);

void queue_screen_create_label_time(char *buffer, unsigned int length);

void queue_screen_write_song_info(WINDOW *win, const char *title, const char *artist, const char *album, unsigned length);

void queue_screen_draw(struct queue_screen *screen, struct linkedlist *queue);
