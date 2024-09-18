#include "Event.h"

bool Event::overlapsWith(const Event& other) const {
    if (day != other.getDay()) return false;

    int thisStart = stoi(startTime);
    int thisEnd = stoi(endTime);
    int otherStart = stoi(other.getStartTime());
    int otherEnd = stoi(other.getEndTime());

    return !(thisEnd <= otherStart || otherEnd <= thisStart);
}
