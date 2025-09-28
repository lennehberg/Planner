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
	
	bool has_deadline;
	time_t deadline;	// date up to which to complete the event
	
	time_t time_created;	// time at which event was created  
	time_t execution_time;	//  time at which to execute the event
	time_t duration_time; // duration in seconds
	
	Priorety prio;

} PlannerEvent;


#endif // PEVENT_H	
