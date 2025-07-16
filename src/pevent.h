#ifndef PEVENT_H
#define PEVENT_H

#include "utils.h"

/**
 * PlannerEvent struct responsible for holding relevant information of 
 * Planner events.
 */
typedef struct {
	ptitle_t title; // title of event
	pdesc_t desc;	// description of event
	bool_t has_deadline;
	pdate_t date_created;	// date at which event was created
	pdate_t deadline;	// date up to which to complete the event
	ptime_t time_created;	// time at which event was created
	ptime_t deadline_time;	// time up to which to complete the event  
	Priorety prio;

} PlannerEvent;

#endif // PEVENT_H	
