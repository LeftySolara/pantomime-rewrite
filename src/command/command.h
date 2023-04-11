/*******************************************************************************
 * command.h - Structs and functions for handling user input commands.
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

#ifndef COMMAND_H
#define COMMAND_H

#define MAX_KEYS 3 /* Maximum number of keys a command can be mapped to. */

enum command_type {
    CMD_NULL,
    CMD_QUIT,
    CMD_HELP,
    CMD_QUEUE,
    CMD_LIBRARY,
    NUM_CMDS
};

struct command {
    enum command_type cmd_type; /** The type of command to execute. */
    int keys[MAX_KEYS];         /** The keys bound to the command. */
    char *name;                 /** The name of the command. */
    char *description;          /** Brief description of what the command does. */
};

enum command_type find_key_command(int key);
void get_command_keys(enum command_type cmd_type, char *buffer);
char *get_command_desc(enum command_type cmd_type);
void key_to_str(int key, char *buffer);

#endif /* COMMAND_H */
