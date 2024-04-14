#include "../include/uptime.h"

mytime::uptime mytime::getCurrentUptime(unsigned long currentUptimeInSeconds){
    unsigned long days = currentUptimeInSeconds / 86400;
    currentUptimeInSeconds %= 86400;
    unsigned long hours = currentUptimeInSeconds / 3600;
    currentUptimeInSeconds %= 3600;
    unsigned long minutes = currentUptimeInSeconds / 60;
    unsigned long seconds = currentUptimeInSeconds % 60;

    String uptimeStr = String(days) + " days, " + String(hours) + " hours, " + String(minutes) + " minutes, " + String(seconds) + " seconds";

    struct uptime uptime;
    uptime.days = days;
    uptime.hours = hours;
    uptime.minutes = minutes;
    uptime.seconds = seconds;
    uptime.uptimeStr = uptimeStr;

    return uptime;
}