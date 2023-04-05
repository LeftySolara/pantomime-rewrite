/*******************************************************************************
 * songlist.h - Linked list containing MPD songs.
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
 * @file songlist.h
 */

#include <stddef.h>

#include <mpd/client.h>

/**
 * @brief A node for a linked list containing mpd_song objects.
 */
struct songlist_node {
    struct mpd_song *song;      /** An MPD song. */
    struct songlist_node *prev; /** The previous song in the list. */
    struct songlist_node *next; /** The next song in the list. */
};

/**
 * @brief A linked list containing mpd_song objects.
 *
 * This struct is a doubly-linked list containing MPD songs.
 * It can be used to populate things like the queue or a playlist.
 */
struct songlist {
    struct songlist_node *head; /** The first song in the list. */
    struct songlist_node *tail; /** The last song in the list. */
    size_t size;
};

struct songlist_node *songlist_node_new(struct mpd_song *song);
void songlist_node_free(struct songlist_node *node);

struct songlist *songlist_new();
void songlist_free(struct songlist *list);

void songlist_append(struct songlist *list, struct mpd_song *song);

void songlist_clear(struct songlist *list);
