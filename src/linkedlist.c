/*******************************************************************************
 * linkedlist.c
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

#include "pantomime/linkedlist.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief A linked list node.
 */
struct node {
    void *data;        /** The data to be stored. */
    struct node *prev; /** The previous item in the list. */
    struct node *next; /** The next item in the list. */
};

/**
 * @brief A generic linked list.
 */
struct linkedlist {
    struct node *head; /** The first item in the list. */
    struct node *tail; /** The last item in the list. */
    unsigned length;   /** The number of items in the list. */
    size_t data_size;  /** The size of each piece of data in bytes. */
};

/**
 * @brief Creates a new linked list node containing the given data.
 *
 * @param data The data to store.
 * @param data_size The size of the data in bytes.
 *
 * @return A newly-allocated node struct, or NULL on error.
 */
struct node *node_new(void *data, size_t data_size)
{
    if (!data) {
        return NULL;
    }

    struct node *node = malloc(sizeof(*node));
    if (!node) {
        return NULL;
    }
    memset(node, 0, sizeof(*node));  // NOLINT

    node->data = malloc(data_size);
    if (!node->data) {
        free(node);
        return NULL;
    }

    memcpy(node->data, data, data_size);  // NOLINT

    return node;
}

/**
 * @brief Free memory ised by a linked list node.
 *
 * @param node The node to free.
 * @param free_fn The function used to clear the node's data.
 */
void node_free(struct node *node, void (*free_fn)(void *))
{
    if (!node) {
        return;
    }

    free_fn(node->data);
    free(node);
}

/**
 * @brief Allocates memory for a new linked list.
 *
 * @param data_size The size of the type of data being stored in bytes.
 */
struct linkedlist *linkedlist_new(size_t data_size)
{
    struct linkedlist *list = malloc(sizeof(*list));
    if (!list) {
        return NULL;
    }
    memset(list, 0, sizeof(*list));  // NOLINT

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->data_size = data_size;

    return list;
}

/**
 * @brief Remove all items from a linked list and
 * deallocate all memory used by it.
 *
 * @param list The list to free.
 * @param free_fn Pointer to a function used to deallocate the data in a node.
 */
void linkedlist_free(struct linkedlist *list, void (*free_fn)(void *))
{
    if (!list) {
        return;
    }

    struct node *current = list->head;
    struct node *next;

    while (current) {
        next = current->next;
        node_free(current, free_fn);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    free(list);
}

/**
 * @brief Add an item to a linked list.
 *
 * @param list The list to push to.
 * @param data The data to add to the list.
 */
enum ll_error linkedlist_push(struct linkedlist *list, void *data)
{
    if (!list || !data) {
        return LL_ERROR_PARAM;
    }
    if (list->length == UINT_MAX) {
        return LL_ERROR_FULL;
    }

    struct node *node = node_new(data, list->data_size);
    if (!node) {
        return LL_ERROR_NO_MEMORY;
    }

    if (!list->head) {
        list->head = node;
        list->tail = node;
    }
    else {
        struct node *current = list->head;
        while (current->next) {
            current = current->next;
        }

        node->prev = current;
        current->next = node;
        node->next = NULL;
    }
    ++list->length;

    return LL_ERROR_SUCCESS;
}
