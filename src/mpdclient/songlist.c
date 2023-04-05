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

#include "songlist.h"

#include <stdlib.h>

/**
 * @brief Allocates memory for a new node in a @ref songlist.
 */
struct songlist_node *songlist_node_new(struct mpd_song *song)
{
    struct songlist_node *node = malloc(sizeof(*node));
    if (!node) {
        return NULL;
    }

    node->song = song;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

/**
 * @brief Frees memory allocated by a @ref songlist node.
 */
void songlist_node_free(struct songlist_node *node)
{
    if (!node) {
        return;
    }

    mpd_song_free(node->song);
    node->prev = NULL;
    node->next = NULL;

    free(node);
}

/**
 * @brief Allocates memory for a new songlist.
 */
struct songlist *songlist_new()
{
    struct songlist *list = malloc(sizeof(*list));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

/**
 * @brief Frees memory used by a songlist.
 */
void songlist_free(struct songlist *list)
{
    /* Remove all songs from list before freeing the list's memory. */
    if (list->head) {
        songlist_clear(list);
    }

    free(list);
}

/**
 * Appends a song to the end of a list.
 */
void songlist_append(struct songlist *list, struct mpd_song *song)
{
    if (!list || !song) {
        return;
    }

    struct songlist_node *new_node = songlist_node_new(song);

    if (!list->head) {
        list->head = new_node;
    }
    else {
        struct songlist_node *current = list->tail;
        current->next = new_node;
        new_node->prev = current;
    }

    list->tail = new_node;
    ++list->size;
}

/**
 * Removes all songs from a songlist and frees the songs' memory.
 */
void songlist_clear(struct songlist *list)
{
    if (!list || !list->head) {
        return;
    }

    struct songlist_node *current = list->head;
    struct songlist_node *next;

    while (current) {
        next = current->next;
        songlist_node_free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
