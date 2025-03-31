#include "schedule.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Create a new schedule with 7 days
struct Schedule* CreateSchedule() {

}

// Add an exam to a day in the schedule
int AddExamToSchedule(struct Schedule* schedule, const char* day, int startTime, int endTime, const char* courseCode) {

}

// Remove an exam from a specific day in the schedule
int RemoveExamFromSchedule(struct Schedule* schedule, const char* day, int startTime) {

}

// Update an exam in the schedule
int UpdateExam(struct Schedule* schedule, const char* oldDay, int oldStartTime, const char* newDay, int newStartTime, int newEndTime) {
 
}

// Clear all exams from a specific day and relocate them to other days
int ClearDay(struct Schedule* schedule, const char* day) {

}

// Clear all exams and days from the schedule and deallocate memory
void DeleteSchedule(struct Schedule* schedule) {

}

// Read schedule from file
int ReadScheduleFromFile(struct Schedule* schedule, const char* filename) {

}

// Write schedule to file
int WriteScheduleToFile(struct Schedule* schedule, const char* filename) {

}
