#ifndef CALENDAR_H
#define CALENDAR_H

#include <vector>
#include <string>
#include <map>
#include "Event.h"

using namespace std;

class Calendar {
private:
    int year;
    int month;
    int realtimedate;
    map<int, vector<Event>> events; // Day-wise events
    map<int, bool> dayOffs; // Day off status

public:
    Calendar(int y, int m, int nowday);
    ~Calendar();
    void addEvent();
    void editEvent();
    void deleteEvent();
    void viewDaySchedule();
    void viewWeekSummary();
    void viewMonthSummary();
    void viewMonthSummaryfordelete();
    void displayMonth();
    bool isWeekend(int day);
    bool isDayOff(int day);
    bool isValidTimeFormat(const std::string& time);
    bool isValidDate(int day, int month, int year);
    bool isOverlapping(const Event& newEvent);
    void setDayOff(int day);
};

#endif
