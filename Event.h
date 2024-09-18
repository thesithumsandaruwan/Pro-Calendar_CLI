#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
private:
    std::string title;
    int day;
    std::string startTime;
    std::string endTime;
    std::string data;
    char scheduletype;

public:
    Event(std::string t, int d, std::string st, std::string et, std::string setd, char scht)
            : title(t), day(d), startTime(st), endTime(et) , data(setd), scheduletype(scht) {}
	~Event() {}
    std::string getTitle() const { return title; }
    int getDay() const { return day; }
    std::string getStartTime() const { return startTime; }
    std::string getEndTime() const { return endTime; }
    std::string getData() const {return data;}
    char getScheduletype() const {return scheduletype;}
    std::string getTimeRange() const { return startTime + " - " + endTime + "H"; }


    void setTitle(const std::string& t) { title = t; }
    void setStartTime(const std::string& st) { startTime = st; }
    void setEndTime(const std::string& et) { endTime = et; }
	void setData(const std::string& setd) {data = setd;}
    bool overlapsWith(const Event& other) const;
};

#endif
