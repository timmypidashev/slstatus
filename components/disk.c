/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include "../slstatus.h"
#include "../util.h"

const char *
disk_free(const char *path)
{
    struct statvfs fs;
    static char output[64];
    uintmax_t free_space;
    const char *unit;
    double formatted_space;

    if (statvfs(path, &fs) < 0) {
        warn("statvfs '%s':", path);
        return NULL;
    }

    free_space = fs.f_frsize * fs.f_bavail;

    if (free_space >= 1000000000000ULL) {
        formatted_space = free_space / 1000000000000.0;
        unit = "T";
        snprintf(output, sizeof(output), "󰆼 %.1f%s", formatted_space, unit);
    } else if (free_space >= 1000000000) {
        formatted_space = free_space / 1000000000;
        unit = "G";
        snprintf(output, sizeof(output), "󰆼 %ju%s", (uintmax_t)formatted_space, unit);
    } else if (free_space >= 1000000) {
        formatted_space = free_space / 1000000;
        unit = "M";
        snprintf(output, sizeof(output), "󰆼 %ju%s", (uintmax_t)formatted_space, unit);
    } else {
        formatted_space = free_space / 1000;
        unit = "K";
        snprintf(output, sizeof(output), "󰆼 %ju%s", (uintmax_t)formatted_space, unit);
    }

    return output;
}

const char *
disk_perc(const char *path)
{
    struct statvfs fs;
    if (statvfs(path, &fs) < 0) {
        warn("statvfs '%s':", path);
        return NULL;
    }
    return bprintf("%d", (int)(100 *
                   (1 - ((double)fs.f_bavail / (double)fs.f_blocks))));
}

const char *
disk_total(const char *path)
{
    struct statvfs fs;
    if (statvfs(path, &fs) < 0) {
        warn("statvfs '%s':", path);
        return NULL;
    }
    return fmt_human(fs.f_frsize * fs.f_blocks, 1024);
}

const char *
disk_used(const char *path)
{
    struct statvfs fs;
    if (statvfs(path, &fs) < 0) {
        warn("statvfs '%s':", path);
        return NULL;
    }
    return fmt_human(fs.f_frsize * (fs.f_blocks - fs.f_bfree), 1024);
}
