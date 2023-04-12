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

/**
 * @brief A linked list node.
 */
struct node {
    void *data;         /** The data to be stored. */
    struct node *prev;  /** The previous item in the list. */
    struct node *next;  /** The next item in the list. */
};

/**
 * @brief A generic linked list.
 */
struct linkedlist {
    struct node *head; /** The first item in the list. */
    struct node *tail; /** The last item in the list. */
    unsigned length; /** The number of items in the list. */
};
