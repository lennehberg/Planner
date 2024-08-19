#ifndef CALENDER_H_
#define CALENDER_H_

#include "constants.h"

/*
* @description a calender struct, holds events in specific dates,
* events are sorted by time for each day
*/
typedef struct calender_t{

    event_list *calender_arr_[NUM_YEARS][NUM_MONTHS];
    date_t *cur_day_;

}calender_t;


// calender interface
/*
* @description initiates a new calender struct, and returns a pointer to it
*/
calender_t *init_calender_(date_t *date);

/*
* @description adds a new event to the calendar
*/
void add_calender_event_(calender_t *calen, event_t *event);

/*
* @description returns an array of events by a given date
*/
event_list *get_events_(calender_t *calen, date_t date);


void print_calender_(calender_t *calen);

/*
* @description frees the resources of calender
*/
void free_calender_(calender_t **calen_ptr);

#endif // CALENDER_H_