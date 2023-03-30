/*******************************************************************************
 * arguments.h - Command-line argument parsing
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
 * @file arguments.h
 */

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <argp.h>

/**
 * @brief Holds command-line arguments passed to the program.
 */
struct arguments {
    char *args[0];
    char *host;
    int port;
};

error_t parse_opt(int key, char *arg, struct argp_state *state);
struct arguments parse_arguments(int argc, char *argv[]);

#endif /* ARGUMENTS_H */
