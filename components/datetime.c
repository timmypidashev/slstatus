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
	static char result[64];
	
	t = time(NULL);
	if (!strftime(time_str, sizeof(time_str), "%I:%M", localtime(&t))) {
		warn("strftime: Result string exceeds buffer size");
		return NULL;
	}
	
	snprintf(result, sizeof(result), "󰥔 %s", time_str);
	
	return result;
}
