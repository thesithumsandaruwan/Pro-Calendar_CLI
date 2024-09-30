# Console-Based Calendar Application for July 2024

This is a console-based calendar application designed to manage events and meetings for the month of July 2024. The application provides various functionalities including scheduling events, managing day-offs, handling repeating events, and much more.

## Features

- *Event Scheduling:* Schedule meetings/events on any date in July 2024. You can choose a non-repeating event, repeating daily, or repeating weekly events.
- *Day Off Scheduling:* Mark specific dates as day-offs. No meetings can be scheduled on day-offs.
- *Weekend Handling:* Weekends are automatically marked, but meetings can be scheduled on weekends with user permission.
- *View Schedule:* 
  - View meetings scheduled for a specific day, week, or the entire month.
  - When viewing a day schedule, the application displays 24-hour time slots with 30-minute intervals.
- *Event Management:* Shift, edit, or delete meetings. Ensure no overlaps between events.
- *Past Dates Restriction:* Events cannot be scheduled for past dates.
- *Event Deletion:* Option to delete a single instance of a repeating event or all its future occurrences.
- *Validation:*
  - Events must have a start and end time within the same day (no overnight events).
  - Event times must be in the format of either XX:00 or XX:30 (hourly or half-hour intervals).
  - Ending time must be later than starting time.
  - No overlap is allowed between meetings/events.

## Usage

Once the application is running, follow the prompts to:

- *Schedule a Meeting/Event:* Enter the date, start time, end time, and title of the event. Validate the input as per the rules mentioned.
- *View Scheduled Events:* View the schedule for a specific day, week, or month.
- *Edit/Delete an Event:* Select a scheduled event to edit its details or delete it.
- *Handle Repeating Events:* Choose whether to apply changes to only one instance or to all future instances of a repeating event.

## Validations

The following validations are implemented:

- *Date:* Must be within the month of July 2024.
- *Start and End Time:* The end time must be later than the start time and within the same day (no overnight events).
- *Time Format:* Events must start at an hour or half-hour interval (e.g., 13:00, 13:30).
- *No Overlaps:* Ensure that no event overlaps with any existing event.
- *Weekends & Day Offs:* No meetings on day-offs unless explicitly allowed on weekends by the user.

## Example

- *Scheduling an Event:*
  - Input: Title: Team Meeting, Date: 2024-07-10, Start Time: 09:00, End Time: 10:00.
  - The event will be added to the schedule on July 10th from 9:00 AM to 10:00 AM.
  
- *View Weekly Schedule:*
  - The schedule for the chosen week will show events day-by-day with their respective time slots.

- *Shifting an Event:*
  - You can select an event and move it to a different time or day within July.
