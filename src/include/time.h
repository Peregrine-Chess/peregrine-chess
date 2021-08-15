/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __TIME_H__
#define __TIME_H__

#ifdef WIN32
    #include <windows.h>
#else 
    #include <sys/time.h>
    #include <stddef.h>
#endif 

int get_time_ms();

#endif