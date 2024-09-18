#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

namespace Utils {
    using namespace std;

    std::string formatTime(int hour, int minute) {
        if (hour == 24 && minute == 0) return "2400";
        std::stringstream ss;
        ss << (hour < 10 ? "0" : "") << hour << (minute == 0 ? "00" : "30");
        return ss.str();
    }
    
    int getDayOfWeek(int day, int month, int year) {
        tm time_in = { 0, 0, 0, day , month - 1, year - 1900 };
        time_t time_temp = mktime(&time_in);

        // Convert time_t to tm as local time
        const tm* time_out = localtime(&time_temp);
        return time_out->tm_wday;
    }
    
    string getDayOfWeekString(int day, int month, int year) {
        const char* daysOfWeek[] = {  "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" , "Sun"};
        int dayOfWeek = getDayOfWeek(day, month, year);
        return daysOfWeek[dayOfWeek];
    }
}

#endif
