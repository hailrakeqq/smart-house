#ifndef UPTIME_H
#define UPTIME_H

#include <Arduino.h>

namespace mytime {

    struct uptime
    {
        unsigned long days;
        unsigned long hours;
        unsigned long minutes;
        unsigned long seconds;
        String uptimeStr;
    };  

    uptime getCurrentUptime(unsigned long currentUptimeInSeconds);
}
#endif // !UPTIME_H