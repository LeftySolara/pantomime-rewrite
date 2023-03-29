/*******************************************************************************
 * arguments.c - Command-line argument parsing
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

#include "arguments.h"

#include <stdlib.h>

const char *argp_program_version = "Pantomime 0.0.1";
const char *argp_program_bug_address = "<julianne@julianneadams.info>";

char doc[] = "An MPD client built on NCURSES.";
char args_doc[] = "";

struct argp_option options[] = {
    {"host", 'h', "HOST", 0, "The IP address or UNIX socket path of the MPD host."},
    {"port", 'p', "PORT", 0, "The port of the MPD host. Only used when connecting via IP address."},
    {0}};

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;
    switch (key) {
        case 'h':
            arguments->host = arg;
            break;
        case 'p':
            arguments->port = atoi(arg);
            break;
        case ARGP_KEY_ARG:
            /* Too many arguments. */
            if (state->arg_num > 2) {
                argp_usage(state);
            }
            arguments->args[state->arg_num] = arg;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

struct arguments parse_arguments(int argc, char *argv[])
{
    struct argp argp = {options, parse_opt, args_doc, doc};
    struct arguments arguments;

    /* Default arguments */
    arguments.host = "localhost";
    arguments.port = 6600;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    return arguments;
}
