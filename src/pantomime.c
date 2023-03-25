/*******************************************************************************
 * pantomime.c
 *******************************************************************************
 * Copyright (C) 2019-2023 Julianne Adams
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#include <argp.h>
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "mpdwrapper.h"

struct arguments {
    char *args[1];
    char *host;
    int port;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
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

int main(int argc, char *argv[])
{
    const char *argp_program_version = "Pantomime 0.0.1";
    static char argp_program_bug_address[] = "<julianne@julianneadams.info>";
    static char doc[] = "An MPD client built on NCURSES.";
    static char args_doc[] = "";
    static struct argp_option options[] = {
        {"host", 'h', "HOST", OPTION_ARG_OPTIONAL,
         "The IP address or UNIX socket path of the MPD host."},
        {"port", 'p', "PORT", OPTION_ARG_OPTIONAL,
         "The port of the MPD host. Only used when connecting via IP address."},
    };
    static struct argp argp = {options, parse_opt, args_doc, doc};

    struct arguments arguments;
    arguments.host = "localhost";
    arguments.port = 6600;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    /*
      setlocale(LC_ALL, "");
      initscr();

      cbreak();
      noecho();
      curs_set(0);
      // nodelay(stdscr, TRUE);
      keypad(stdscr, TRUE);

      printw("Hello World!");
      refresh();

      getch();
      endwin();
    */

    printf("%s\n", argp_program_version);
    printf("Please send bug reports to %s\n", argp_program_bug_address);

    struct mpdwrapper *mpd = mpdwrapper_new(arguments.host, arguments.port, 0);
    if (!mpd) {
        fprintf(stderr, "Error connecting to MPD.\n");
        exit(EXIT_FAILURE);
    }

    mpdwrapper_print_queue(mpd);
    mpdwrapper_free(mpd);

    return 0;
}
