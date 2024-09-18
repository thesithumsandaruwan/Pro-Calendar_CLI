#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "Calendar.h"
#include "Utils.h"

using namespace std;

Calendar::Calendar(int y, int m, int nowday) : year(y), month(m), realtimedate(nowday) {}

Calendar::~Calendar(){}

void Calendar::addEvent() {
    string title, startTime, endTime, evtdata;
    int day, choice;
    char choice3;
    cout << "What type of event you want to add?\n";
    cout << "\t1. Event\n\t2.Day Off" << endl;
    cout << "Select the log type: " ;
    cin >> choice;
    cin.ignore();
    if (choice == 1) {
        cout << "Enter event title: ";
        getline(std::cin, title);
        cout<< "Enter event data: ";
        getline(std::cin, evtdata);
        while (true)
        {
        	cout << "Enter day (1-31): ";
	        cin >> day;
	        cin.ignore();
	        if (day<realtimedate){
	        	cout<<"Cannot do the operation to past dates.\n";
			}
			else if (!isValidDate(day, month, year))
			{
				cout<<"Invalid date.\n";
			}
	        else if (isDayOff(day)==true || isWeekend(day)==true) {
	        	if (isWeekend(day)==true)
	        	{
	        		cout << "The date you entered is a weekend day.\n";
				}
				else if (isDayOff(day)==true)
				{
					cout<< "The date you entered is a day off.\n";
				}
	            cout<< "1. Go ahead and schedule at that day.\n2. Select another day.\n";
	            int choice2;
	            cin >> choice2;
	            cin.ignore();
	            if (choice2 == 1){
	                break;
	            }
	            else if (choice2 == 2){
	            }
	            else{
	                cout << "invalid option!" << endl;
	            }
			}
			else
			{
				break;
			}
        }
        cout << "Enter start time (HHMM): ";
        cin >> startTime;
        cout << "Enter end time (HHMM): ";
        cin >> endTime;
        cin.ignore();

        if (!isValidTimeFormat(startTime) || !isValidTimeFormat(endTime)) {
            cout << "Invalid date or time format.\n";
            return;
        }
		
		if (startTime>endTime){
			cout << "Invalid time range.\n";
            return;
		}
		while (true)
		{
			cout<<"\n   Set this event, \n";
			cout<<"a. Only for this date\n";
			cout<<"b. Daily\n";
			cout<<"c. Weekly\n";
			cout<<"Select an option: ";
			cin>>choice3;
			if (choice3=='a' || choice3=='b' || choice3=='c')
			{
				break;
			}
			else
			{
				cout<<"Wrong choice selection!\n\n";
			}
		}
		switch (choice3)
		{
			case 'a': {
				Event newEvent(title, day, startTime, endTime, evtdata, choice3);
		        if (isOverlapping(newEvent)) {
		            cout << "Event overlaps with an existing event.\n";
		            return;
		        }
        		events[day].push_back(newEvent);
				break;
			}
			case 'b': {
				for (int i=day; i<=31; i++)
				{
					Event newEvent(title, i, startTime, endTime, evtdata, choice3);
			        if (isOverlapping(newEvent)) {
			            cout << "Event overlaps with an existing event.\n";
			            break;
			        }
	        		events[i].push_back(newEvent);
				}
				break;
			}
			case 'c': {
				for (int i=day; i<=31; i=i+7)
				{
					Event newEvent(title, i, startTime, endTime, evtdata, choice3);
			        if (isOverlapping(newEvent)) {
			            cout << "Event overlaps with an existing event.\n";
			            break;
			        }
	        		events[i].push_back(newEvent);
				}
				break;
			}
		}
        cout << "Event added successfully.\n";
    }

    else if (choice == 2){
        int day2;
        while (true){
        	cout << "Enter day (1-31): ";
	        cin >> day2;
	        cin.ignore();
	        if (day2<realtimedate){
	        	cout<<"Cannot do the operation to past dates.\n";
			}
			else if (!isValidDate(day2, month, year))
			{
				cout<<"Invalid date.\n";
			}
			else{
				setDayOff(day2);
	        	cout << day2 << " is set as an Off-day." << endl;
	        	break;
			}
		}
    }

    else{
        cout << "invalid option!" << endl;
        addEvent();
    }
}

void Calendar::editEvent() {
    viewMonthSummaryfordelete();
    int day, index;
    while (true){
    	cout << "Enter day of the event to edit (1-31): ";
    	cin >> day;
    	if (day<realtimedate){
	       	cout<<"Cannot do the operation to past dates.\n";
		}
		else if (!isValidDate(day, month, year))
		{
			cout<<"Invalid date.\n";
		}
		else{
	       	break;
		}
	}
    cout << "Enter event index to edit: ";
    cin >> index;
    index--;
    cin.ignore();

    if (events.find(day) == events.end() || index < 0 || index >= events[day].size()) {
        cout << "Invalid day or event index.\n";
        return;
    }

    string title, startTime, endTime, evtdata;
    cout << "Enter new event title: ";
    getline(std::cin, title);
    cout<< "Enter event data: ";
    getline(std::cin, evtdata);
    cout << "Enter new start time (HHMM, e.g., 0800 or 0830): ";
    cin >> startTime;
    cout << "Enter new end time (HHMM, e.g., 0900 or 0930): ";
    cin >> endTime;
    cin.ignore();

    if (!isValidTimeFormat(startTime) || !isValidTimeFormat(endTime)) {
        cout << "Invalid time format.\n";
        return;
    }
	
	if (startTime>endTime){
		cout << "Invalid time range.\n";
        return;
	}
	
    Event& event = events[day][index];
    event.setTitle(title);
    event.setStartTime(startTime);
    event.setEndTime(endTime);
    event.setData(evtdata);

    if (isOverlapping(event)) {
        cout << "Event overlaps with another event.\n";
        return;
    }

    cout << "Event updated successfully.\n";
}

void Calendar::deleteEvent() {
    viewMonthSummaryfordelete();
    int day, index;
    cout << "Enter day of the event to delete (1-31): ";
    cin >> day;
    cout << "Enter event index to delete: ";
    cin >> index;
    index--;
    cin.ignore();

    if (events.find(day) == events.end() || index < 0 || index >= events[day].size()) {
        cout << "Invalid day or event index.\n";
        return;
    }

    Event tempE=events[day][index];
    string tempTitle=events[day][index].getTitle();
    string tempST=events[day][index].getStartTime();
    char deltype;
    switch (events[day][index].getScheduletype()){
        case 'a': events[day].erase(events[day].begin() + index);
            cout << "Event deleted successfully.\n";
            break;
        case 'b': cout<<"\nSelect delete type:\n";
            cout<<"a. Selected date only.\n";
            cout<<"b. All dates (Neglect past dates)\n";
            cout<<"Select an option: ";
            cin>>deltype;
            if (deltype=='a')
            {
                events[day].erase(events[day].begin() + index);
                cout << "Event deleted successfully.\n";
                break;
            }
            else if (deltype=='b')
            {
                for (int i=day; i<=31; i++)
                {
                    for (int j=0; j<events[i].size(); j++)
                    {
                        if (events[i][j].getTitle()==tempTitle && events[i][j].getStartTime()==tempST)
                        {
                            events[i].erase(events[i].begin() + j);
                        }
                    }
                }
                cout << "Event deleted successfully.\n";
            }
            break;
        case 'c': cout<<"\nSelect delete type:\n";
            cout<<"a. Selected date only.\n";
            cout<<"b. All dates (Neglect past dates)\n";
            cout<<"Select an option: ";
            cin>>deltype;
            if (deltype=='a')
            {
                events[day].erase(events[day].begin() + index);
                cout << "Event deleted successfully.\n";
                break;
            }
            else if (deltype=='b')
            {
                for (int i=day; i<=31; i=i+7)
                {
                    for (int j=0; j<events[i].size(); j++)
                    {
                        if (events[i][j].getTitle()==tempTitle && events[i][j].getStartTime()==tempST)
                        {
                            events[i].erase(events[i].begin() + j);
                        }
                    }
                }
                cout << "Event deleted successfully.\n";
            }
            break;
    }
}

void Calendar::viewDaySchedule() {
    int day;
    cout << "Enter day to view schedule (1-31): ";
    cin >> day;

    if (!isValidDate(day, month, year)) {
        std::cout << "Invalid day.\n";
        return;
    }

    cout << "\n" << day << " July " << year << "\n";

    std::string timeSlots[48];  // 48 slots for 30-minute intervals in a day

    for (int i = 0; i < 48; ++i) {
        int hour = i / 2;
        int minute = (i % 2) * 30;
        std::string timeSlot1 = Utils::formatTime(hour, minute);
        std::string timeSlot2 = (i == 47) ? "2400" : Utils::formatTime(hour, minute + 30);  // Handle last interval
        timeSlots[i] = timeSlot1 + "-" + timeSlot2 + "H";
    }

    for (int i = 0; i < 48; ++i) {
        cout << timeSlots[i] << " ";
        if (events.find(day) != events.end()) {
            bool printed = false;
            for (const Event& event : events[day]) {
                int startIdx = (std::stoi(event.getStartTime().substr(0, 2)) * 2) + (event.getStartTime().substr(2, 2) == "30" ? 1 : 0);
                int endIdx = (std::stoi(event.getEndTime().substr(0, 2)) * 2) + (event.getEndTime().substr(2, 2) == "30" ? 1 : 0);
                if (i >= startIdx && i < endIdx) {
                    if (!printed) {
                        cout << "  " << event.getTitle();
                        printed = true;
                    }
                }
            }
        }
        cout << endl;
    }
}

void Calendar::viewWeekSummary() {
    cout << "Enter the start day of the week (1-31): ";
    int startDay;
    cin >> startDay;
    cout<<endl;
    if (!isValidDate(startDay, month, year)) {
        cout << "Invalid start day.\n";
        return;
    }

        for (int i = 0; i < 7; i++) {
            int currentDay = startDay + i;
            std::string dayOfWeek = Utils::getDayOfWeekString(currentDay-1, month, year);

            cout << currentDay << " July (" << dayOfWeek << ")" << endl;

            if (isDayOff(currentDay)) {
                std::cout << "    Day Off" << std::endl;
            } else if (events.find(currentDay) != events.end()) {
                for (const auto& event : events.at(currentDay)) {
                    cout << "    " << event.getTimeRange() << " " << event.getTitle() << " " << event.getData() << endl;
                }
            }
        }
}

void Calendar::viewMonthSummary() {
    cout << "\n\tSchedule for the month of July " << year << ":\n";
    for (int day = 1; day <= 31; ++day) {
        if (events.find(day) != events.end() || isDayOff(day)) {
            cout << day << " July (" << Utils::getDayOfWeekString(day, month, year) << ")\n";
            if (isDayOff(day)) {
                cout << "    Day Off\n";
            } else {
                int i = 1;
                for (const Event& event : events[day]) {
                    cout << "    " << event.getTimeRange() << " " << event.getTitle() << " " << event.getData() << endl;
                    i++;
                }
            }
        }
    }
}

void Calendar::viewMonthSummaryfordelete() {
    cout << "\n\tSchedule for the month of July " << year << ":\n";
    for (int day = 1; day <= 31; ++day) {
        if (events.find(day) != events.end() || isDayOff(day)) {
            cout << day << " July (" << Utils::getDayOfWeekString(day, month, year) << ")\n";
            if (isDayOff(day)) {
                cout << "    Day Off\n";
            } else {
                int i = 1;
                for (const Event& event : events[day]) {
                    cout <<i<< ". " << event.getTimeRange() << " " << event.getTitle() << " " << event.getData() << "\n";
                    i++;
                }
            }
        }
    }
}

void Calendar::displayMonth() {
    cout << "\n\tJuly " << year << "\n";
    cout << "Mon Tue Wed Thu Fri Sat Sun\n";

    int firstDayOfWeek = Utils::getDayOfWeek(0, month, year);
    for (int i = 1; i < firstDayOfWeek; ++i) {
        cout << "    "; // Print leading spaces
    }

    for (int day = 1; day <= 31; ++day) {
        cout << std::setw(3) << day << " ";
        if ((day + firstDayOfWeek) % 7 == 0) {
            cout << "\n";
        }
    }
    cout << "\n";
}

bool Calendar::isWeekend(int day) {
    int dayOfWeek = Utils::getDayOfWeek(day, month, year);
    return (dayOfWeek == 0 || dayOfWeek == 6); // Sunday or Saturday
}

bool Calendar::isDayOff(int day) {
    return dayOffs.find(day) != dayOffs.end() && dayOffs[day];
}

bool Calendar::isValidTimeFormat(const std::string& time) {
    if (time.size() != 4) return false;
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(2, 2));
    return ((hour >= 0 && hour < 24 && (minute == 0 || minute == 30))||(hour == 24 && minute == 0));
}

bool Calendar::isValidDate(int day, int month, int year) {
    return (month == 7 && day >= 1 && day <= 31);
}

bool Calendar::isOverlapping(const Event& newEvent) {
    if (events.find(newEvent.getDay()) != events.end()) {
        for (const Event& event : events[newEvent.getDay()]) {
            if (event.overlapsWith(newEvent)) {
                return true;
            }
        }
    }
    return false;
}

void Calendar::setDayOff(int day) {
    if (isValidDate(day, month, year)) {
        dayOffs[day] = true;
    }
}
