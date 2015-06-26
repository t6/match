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

static char *action = NULL;
static char *pattern = NULL;
static char *format = NULL;
static int be_quiet = 0;
static int ignore_errors = 0;

int main(int argc, char **argv) {
  int ch;
  while ((ch = getopt(argc, argv, "iqa:p:f:")) != -1) {
    switch (ch) {
      case 'i':
        ignore_errors = 1;
        break;
      case 'q':
        be_quiet = 1;
        break;
      case 'a':
        action = optarg;
        break;
      case 'p':
        pattern = optarg;
        break;
      case 'f':
        format = optarg;
        break;
      default:
        usage();
    }
  }

  argc -= optind;
  argv += optind;

  if (argc == 0 || pattern == NULL || format == NULL)
    usage();

  for (int i = 0; i < argc; i++) {
    match(argv[i]);
  }
  if (action == NULL)
    warnx("Did nothing; to apply matches run with e.g. '%s' or '%s'", "-a cp",
          "-a mv");

  return 0;
}

static void match(char *filename) {
  struct str_match match;
  const char *errstr = NULL;
  char buf[4096];
  str_match(filename, pattern, &match, &errstr);
  if (errstr)
    err(1, "%s", errstr);

  if (match.sm_nmatch > 0) {
    expand_format(&match, format, buf, sizeof(buf));
    run(filename, buf);
  } else if (!be_quiet) {
    warnx("ignoring %s (no match)", filename);
  }
}

static void run(char *source, char *target) {
  if (action == NULL) {
    printf("%s => %s\n", source, target);
  } else {
    char *argv[] = { action, source, target, NULL };
    pid_t child = fork();
    if (child == 0)
      execvp(action, argv);
    else if (child == -1)
      err(1, "fork");

    int status;
    if (waitpid(child, &status, 0) == -1)
      err(1, "waitpid");

    if (status != 0) {
      if (be_quiet) {
        exit(1);
      } else {
        if (ignore_errors)
          warnx("'%s %s %s' failed with status %i (ignoring)", action, source,
                target, status);
        else
          errx(1, "'%s %s %s' failed with status %i", action, source, target,
               status);
      }
    }
  }
}

static void usage() {
  fprintf(stderr,
          "usage: match -p pattern -f format [-a action] [-iq] file ...\n");
  exit(1);
}
