/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../slstatus.h"
#include "../util.h"

const char *
datetime(const char *fmt)
{
    time_t t;
    char time_str[32];
    static char result[64];  // Increased buffer size to accommodate icon and time
    
    t = time(NULL);
    // Use %I for 12-hour format, %M for minutes, %p for AM/PM
    if (!strftime(time_str, sizeof(time_str), "%I:%M %p", localtime(&t))) {
        warn("strftime: Result string exceeds buffer size");
        return NULL;
    }
    
    // Combine icon and time string
    snprintf(result, sizeof(result), " %s", time_str);
    
    return result;
}
