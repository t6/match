/*
 * Copyright (c) 2015-2017 Tobias Kortkamp <t@tobik.me>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <ctype.h>
#include <err.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "patterns.h"

extern int expand_string(char *, size_t, const char *, const char *);
extern void expand_format(struct str_match *, char *, char *, size_t);
static void match(char *);
static void run(char *, char *);
static void usage(void);

static char *command = "echo";
static char *pattern = NULL;
static char *target_format = "%0";
static int verbose = 0;
static int ignore_errors = 0;
static int matches_only = 0;
static int target_only = 0;

int
main(int argc, char **argv)
{
	int ch;
	while ((ch = getopt(argc, argv, "omivc:p:t:")) != -1) {
		switch (ch) {
		case 'm':
			matches_only = 1;
			break;
		case 'o':
			target_only = 1;
			break;
		case 'i':
			ignore_errors = 1;
			break;
		case 'v':
			verbose = 1;
			break;
		case 'c':
			command = optarg;
			break;
		case 'p':
			pattern = optarg;
			break;
		case 't':
			target_format = optarg;
			break;
		default:
			usage();
		}
	}

	argc -= optind;
	argv += optind;

	if (argc == 0 || pattern == NULL)
		usage();

	if (target_only && matches_only) {
		warnx("-m and -o are mutually exclusive");
		usage();
	}

	for (int i = 0; i < argc; i++) {
		match(argv[i]);
	}

	return 0;
}

static void
match(char *string)
{
	struct str_match matches;
	const char *errstr = NULL;
	char buf[4096];
	str_match(string, pattern, &matches, &errstr);
	if (errstr)
		err(1, "%s", errstr);

	if (matches.sm_nmatch > 0) {
		expand_format(&matches, target_format, buf, sizeof(buf));
		run(string, buf);
	} else if (verbose) {
		warnx("ignoring %s (no match)", string);
	}
}

static void
run(char *source, char *target)
{
	char *argv[4];
	size_t i = 0;
	argv[i++] = command;
	if (!target_only)
		argv[i++] = source;
	if (!matches_only)
		argv[i++] = target;
	argv[i++] = NULL;

	pid_t child = fork();
	if (child == 0)
		execvp(command, argv);
	else if (child == -1)
		err(1, "fork");

	int status;
	if (waitpid(child, &status, 0) == -1)
		err(1, "waitpid");

	if (status != 0) {
		if (ignore_errors)
			warnx("'%s %s %s' failed with status %i (ignoring)", command, source,
			      target, status);
		else
			errx(1, "'%s %s %s' failed with status %i", command, source, target,
			     status);
	}
}

static void
usage()
{
	fprintf(stderr, "usage: match -p pattern [-c command] [-i] [-m] [-o] "
		"[-t format] [-v] string ...\n");
	exit(1);
}