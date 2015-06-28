/*
 * Copyright (c) 2015 Tobias Kortkamp <t@tobik.me>
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

extern int expand_string(char *label, size_t len, const char *srch,
                         const char *repl);
extern void expand_format(struct str_match *match, char *val, char *buf,
                          size_t len);
static void match(char *filename);
static void run(char *source, char *target);
static void usage();

static char *command = "echo";
static char *pattern = NULL;
static char *target_format = "%0";
static int verbose = 0;
static int ignore_errors = 0;
static int matches_only = 0;

int main(int argc, char **argv) {
  int ch;
  while ((ch = getopt(argc, argv, "mivc:p:t:")) != -1) {
    switch (ch) {
      case 'm':
        matches_only = 1;
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

  for (int i = 0; i < argc; i++) {
    match(argv[i]);
  }
  if (command == NULL)
    warnx("Did nothing; to apply matches run with e.g. '%s' or '%s'", "-a cp",
          "-a mv");

  return 0;
}

static void match(char *string) {
  struct str_match match;
  const char *errstr = NULL;
  char buf[4096];
  str_match(string, pattern, &match, &errstr);
  if (errstr)
    err(1, "%s", errstr);

  if (match.sm_nmatch > 0) {
    expand_format(&match, target_format, buf, sizeof(buf));
    run(string, buf);
  } else if (verbose) {
    warnx("ignoring %s (no match)", string);
  }
}

static void run(char *source, char *target) {
  char *argv[] = { command, source, matches_only ? NULL : target, NULL };
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

static void usage() {
  fprintf(stderr,
          "usage: match -p pattern [-c command] [-i] [-m] [-t format] [-v] string ...\n");
  exit(1);
}
