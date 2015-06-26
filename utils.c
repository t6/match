/*
 * Copyright (c) 2014 Reyk Floeter <reyk@openbsd.org>
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

/* Functions in this file are derived from OpenBSD's usr.sbin/httpd.c
 * $OpenBSD: httpd.c,v 1.35 2015/02/23 18:43:18 reyk Exp $
 */

#include <ctype.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "patterns.h"

#define log_debug warnx

int expand_string(char *label, size_t len, const char *srch, const char *repl);
void expand_format(struct str_match *match, char *val, char *buf, size_t len);

int expand_string(char *label, size_t len, const char *srch, const char *repl) {
  char *tmp;
  char *p, *q;

  if ((tmp = calloc(1, len)) == NULL) {
    log_debug("%s: calloc", __func__);
    return (-1);
  }
  p = q = label;
  while ((q = strstr(p, srch)) != NULL) {
    *q = '\0';
    if ((strlcat(tmp, p, len) >= len) || (strlcat(tmp, repl, len) >= len)) {
      log_debug("%s: string too long", __func__);
      free(tmp);
      return (-1);
    }
    q += strlen(srch);
    p = q;
  }
  if (strlcat(tmp, p, len) >= len) {
    log_debug("%s: string too long", __func__);
    free(tmp);
    return (-1);
  }
  (void)strlcpy(label, tmp, len); /* always fits */
  free(tmp);

  return (0);
}

void expand_format(struct str_match *match, char *val, char *buf, size_t len) {
  char *p;
  const char *errstr = NULL;
  size_t size;
  char ibuf[128];
  int n;

  if (strlcpy(buf, val, len) >= len)
    return;

  /* Find previously matched substrings by index */
  for (p = val; match->sm_nmatch && (p = strstr(p, "%")) != NULL; p++) {
    if (!isdigit(*(p + 1)))
      continue;

    /* Copy number, leading '%' char and add trailing \0 */
    size = strspn(p + 1, "0123456789") + 2;
    if (size >= sizeof(ibuf))
      return;
    (void)strlcpy(ibuf, p, size);
    n = strtonum(ibuf + 1, 0, match->sm_nmatch - 1, &errstr);
    if (errstr != NULL)
      return;

    /* Expand variable with matched value */
    if (expand_string(buf, len, ibuf, match->sm_match[n]) != 0)
      return;
  }
}
