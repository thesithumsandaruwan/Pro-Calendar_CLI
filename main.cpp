#include <iostream>
#include "Calendar.h"
#include <ctime>

using namespace std;

int main() {
	
	char datetypechoice;
    int setrealtimedate;

    cout << "Choose an option:\n";
    cout << "1. Enter a custom date\n";
    cout << "2. Proceed with real date\n";
    cout << "Enter your choice: ";
	cin >> datetypechoice;
	if (datetypechoice == '1') {
	   	while (true)
	   	{
	   		cout << "Enter a value for the day (1-31): ";
	        cin >> setrealtimedate;
	        if (setrealtimedate >= 1 && setrealtimedate <= 31) {
	            break;
	        }
	        else{
	        	cout << "Invalid day. Please enter a value between 1 and 31.\n";
			}
		}
	} else if (datetypechoice == '2') {
	    // Get the current date
	    time_t t = time(0);   // Get current time
	    struct tm* now = localtime(&t);
	    setrealtimedate = now->tm_mday;   // Get the day of the month
	} else {
	    cout << "Invalid choice.\n";
	}
    cout << "The day is: " << setrealtimedate << std::endl;

    Calendar calendar(2024, 7, setrealtimedate);

    while (true) {
        calendar.displayMonth();
        cout << "\n\t\t\tCalendar Menu:\n";
        cout << "1. Add an Event\n";
        cout << "2. Edit Event\n";
        cout << "3. Delete Event\n";
        cout << "4. View Day Schedule\n";
        cout << "5. View Week Summary\n";
        cout << "6. View Month Summary\n";
        cout << "7. Exit\n\n";
        cout << "Select an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                calendar.addEvent();
                break;
            case 2:
                calendar.editEvent();
                break;
            case 3:
                calendar.deleteEvent();
                break;
            case 4:
                calendar.viewDaySchedule();
                break;
            case 5:
                calendar.viewWeekSummary();
                break;
            case 6:
                calendar.viewMonthSummary();
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
