/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <log.h>

void logger(int status, char *message) {
  if (status) {
    fprintf(stderr, "\033[0;32m");
    fprintf(stderr, "[ OK ] ");
    fprintf(stderr, "\033[0m");
    fprintf(stderr, "%s\n", message);
  } else {
    fprintf(stderr, "\033[0;31m");
    fprintf(stderr, "[ FAIL ] ");
    fprintf(stderr, "\033[0m");
    fprintf(stderr, "%s\n", message);
  }
}