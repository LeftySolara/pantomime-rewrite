/*******************************************************************************
 * linkedlist.h
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
 * @file linkedlist.h
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>

enum ll_error {
    LL_ERROR_SUCCESS,  /** No error. */
    LL_ERROR_PARAM,  /** Invalid parameter passed to list-handling function. */
    LL_ERROR_FULL,  /** List is full. */
    LL_ERROR_NO_MEMORY, /** No memory available to perform operation. */
    LL_ERROR_UNKNOWN  /** Unknown error. */
};

struct node;
struct linkedlist;

struct node *node_new(void *data, size_t data_size);
void node_free(struct node *node, void (*free_fn)(void *));

struct linkedlist *linkedlist_new(size_t data_size);
void linkedlist_free(struct linkedlist *list, void (*free_fn)(void *));

unsigned linkedlist_get_length(struct linkedlist *list);

void *linkedlist_at(struct linkedlist *list, unsigned index);

enum ll_error linkedlist_push(struct linkedlist *list, void *data);

enum ll_error linkedlist_remove(struct linkedlist *list, unsigned index, void (*free_fn)(void *));
enum ll_error linkedlist_clear(struct linkedlist *list, void (*free_fn)(void *));

#endif /* LINKEDLIST_H */
