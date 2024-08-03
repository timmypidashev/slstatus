/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>

#include "../slstatus.h"
#include "../util.h"

#include <limits.h>
#include <stdint.h>
#include <unistd.h>

#define POWER_SUPPLY_CAPACITY "/sys/class/power_supply/%s/capacity"
#define POWER_SUPPLY_STATUS   "/sys/class/power_supply/%s/status"
#define POWER_SUPPLY_CHARGE   "/sys/class/power_supply/%s/charge_now"
#define POWER_SUPPLY_ENERGY   "/sys/class/power_supply/%s/energy_now"
#define POWER_SUPPLY_CURRENT  "/sys/class/power_supply/%s/current_now"
#define POWER_SUPPLY_POWER    "/sys/class/power_supply/%s/power_now"
#define POWER_SUPPLY_AC       "/sys/class/power_supply/AC/online"

const char *
battery_perc(const char *bat)
{
    int cap_perc;
    char path[PATH_MAX];
    static char glyph[8];
    static char output[16];  // Increased size to accommodate glyph and percentage
    int charging;

    if (esnprintf(path, sizeof(path), POWER_SUPPLY_CAPACITY, bat) < 0)
        return NULL;
    if (pscanf(path, "%d", &cap_perc) != 1)
        return NULL;

    // Check if charging
    if (pscanf(POWER_SUPPLY_AC, "%d", &charging) != 1)
        return NULL;

    // Select glyph based on battery percentage and charging status
    if (cap_perc <= 9) {
        strcpy(glyph, charging ? "󰢟" : "󰂎");
    } else if (cap_perc <= 19) {
        strcpy(glyph, charging ? "󰢜" : "󰁺");
    } else if (cap_perc <= 29) {
        strcpy(glyph, charging ? "󰂆" : "󰁻");
    } else if (cap_perc <= 39) {
        strcpy(glyph, charging ? "󰂇" : "󰁼");
    } else if (cap_perc <= 49) {
        strcpy(glyph, charging ? "󰂈" : "󰁽");
    } else if (cap_perc <= 59) {
        strcpy(glyph, charging ? "󰢝" : "󰁾");
    } else if (cap_perc <= 69) {
        strcpy(glyph, charging ? "󰂉" : "󰁿");
    } else if (cap_perc <= 79) {
        strcpy(glyph, charging ? "󰢞" : "󰂀");
    } else if (cap_perc <= 89) {
        strcpy(glyph, charging ? "󰂊" : "󰂁");
    } else if (cap_perc <= 99) {
        strcpy(glyph, charging ? "󰂋" : "󰂂");
    } else {
        strcpy(glyph, charging ? "󰂄" : "󰁹");
    }

    // Combine glyph and percentage into output
    snprintf(output, sizeof(output), "%s %d%%", glyph, cap_perc);
    return output;
}
