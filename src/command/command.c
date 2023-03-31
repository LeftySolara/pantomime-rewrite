
/*******************************************************************************
 * command.c - Structs and functions for handling user input commands.
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
 * @file command.h
 */

#include "command.h"

#include <curses.h>
#include <stdlib.h>
#include <string.h>

#define KEY_CTRL(x) ((x)&0x1f)
#define KEY_RETURN 10

static struct command commands[] = {
    {CMD_NULL, {0, 0, 0}, "Null", "Null command. Does nothing."},

    {CMD_QUIT, {'q', 'Q', KEY_CTRL('c')}, "Quit", "Quit Pantomime."}};

/**
 * @brief Finds the command mapped to a given key.
 *
 * @param key The key that was pressed by the user.
 *
 * @return The command mapped to the key.
 */
enum command_type find_key_command(int key)
{
    if (key == 0) {
        return CMD_NULL;
    }

    for (int i = 0; i < NUM_CMDS; ++i) {     /* Search each command. */
        for (int j = 0; j < MAX_KEYS; ++j) { /* Search each key mapped to the command. */
            if (key == commands[i].keys[j]) {
                return commands[i].cmd_type;
            }
        }
    }

    return CMD_NULL;
}

/**
 * @brief Gets a string representation of the keys mapped to a command.
 */
void get_command_keys(enum command_type cmd_type, char *buffer)
{
    int *keys = commands[cmd_type].keys;
    char *key_str = malloc(sizeof(char) * 16);

    if (!key_str) {
        return;
    }

    key_to_str(keys[0], key_str);
    strcpy(buffer, key_str);  // NOLINT

    if (keys[1] != 0) {
        key_to_str(keys[1], key_str);
        strcat(buffer, " ");      // NOLINT
        strcat(buffer, key_str);  // NOLINT
    }
    if (keys[2] != 0) {
        key_to_str(keys[2], key_str);
        strcat(buffer, " ");      // NOLINT
        strcat(buffer, key_str);  // NOLINT
    }

    free(key_str);
}

/**
 * @brief Gets a command's description.
 */
char *get_command_desc(enum command_type cmd_type)
{
    return commands[cmd_type].description;
}

/**
 * @brief Creates a string representation of a keypress.
 */
void key_to_str(int key, char *buffer)
{
    char *str;
    switch (key) {
        case 0:
            str = NULL;
            break;
        case KEY_RETURN:
            str = "Enter";
            break;
        case KEY_BACKSPACE:
            str = "Backspace";
            break;
        case KEY_RIGHT:
            str = "Right";
            break;
        case KEY_LEFT:
            str = "Left";
            break;
        case KEY_UP:
            str = "Up";
            break;
        case KEY_DOWN:
            str = "Down";
            break;
        case KEY_PPAGE:
            str = "PageUp";
            break;
        case KEY_NPAGE:
            str = "PageDown";
            break;
        case KEY_HOME:
            str = "Home";
            break;
        case KEY_END:
            str = "End";
            break;
        case KEY_F(1):
            str = "F1";
            break;
        case KEY_F(2):
            str = "F2";
            break;
        case KEY_F(3):
            str = "F3";
            break;
        case KEY_F(4):
            str = "F4";
            break;
        case KEY_F(5):
            str = "F5";
            break;
        case KEY_F(6):
            str = "F6";
            break;
        case KEY_F(7):
            str = "F7";
            break;
        case KEY_F(8):
            str = "F8";
            break;
        case KEY_F(9):
            str = "F9";
            break;
        case KEY_F(10):
            str = "F10";
            break;
        case KEY_F(11):
            str = "F11";
            break;
        case KEY_F(12):
            str = "F12";
            break;
        default:
            str = NULL;
            break;
    }

    int length;
    if (str) {
        length = strlen(str);
        buffer = realloc(buffer, sizeof(char) * length);
        strcpy(buffer, str);  // NOLINT
    }
    else if (!str && !(key & ~0x1f)) { /* A CTRL combo was pressed */
        length = strlen("Ctrl-a");
        buffer = realloc(buffer, sizeof(char) * length + 1);
        sprintf(buffer, "Ctrl-%c", 'a' + (key & 0x1f) - 1);  // NOLINT
    }
    else { /* The key is just one character */
        buffer = realloc(buffer, sizeof(char) + 1);
        sprintf(buffer, "%c", key);  // NOLINT
    }
}
