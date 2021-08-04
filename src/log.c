/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <log.h>

void logger(int status, char *message) {
    if (status) {
        printf("\033[0;32m");
        printf("[ OK ] ");
        printf("\033[0m");
        printf("%s\n", message);
    } else {
        printf("\033[0;31m");
        printf("[ FAIL ] ");
        printf("\033[0m");
        printf("%s\n", message);
    }
}