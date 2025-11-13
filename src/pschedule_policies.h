#ifndef PSCHEDULE_POLICIES_H
#define PSCHEDULE_POLICIES_H

#include <stdio.h>

/******************************************************
 * header file for potential planner scheduler policies
 ******************************************************/

/**
 * Eealiest deadline first scheduling - schedules events based on their deadlines
 * @param events_base - void ** to the head of the array of events
 * @param event - void * to event to schedule
 * @param count - amount of events in events_base
 * @param memb_size - size of event
 */
void edf_event_policy(void* events_base, void *events_batch, size_t batch_size, 
			size_t count, size_t memb_size);

#endif // PSCHEDULE_POLICIES_H
