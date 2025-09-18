#include "scheduler.h"

typedef void* (*ScheduleFunc)(void *events, size_t count, size_t memb_size); // custom schedule policy



/**
 * Scheduler struct, with the ability to set a custom scheduling policy
 */
typedef struct Scheduler{
	
	void* events; // array of events to schedule
	size_t event_size; // size of each event
	size_t events_len; // length of events array
	ScheduleFunc __schedule; // dynamic schedule policy

} Scheduler;



/**
 * Scheduler Init method
 * @param events - void* to array of events
 * @param schedule - function which takes array of events and returns 
 * 			an array of array to run
 *			void* (*ScheduleFunc)(void *events, size_t count, size_t memb_size)
 *
 * @return scheduler entity
 */
Scheduler schedulerInit(void* events, size_t event_size, 
		size_t events_len, ScheduleFunc schedule)
{
	Scheduler scheduler = {events, event_size, events_len, schedule};
	return scheduler;
}


	/**
 * Scheduler custom schedule policy method - calls the policy set by init
 * @param scheduler
 * @return void * of events
 */
void* scheduleEvent(Scheduler *scheduler)
{
	return scheduler->__schedule(scheduler->events, scheduler->events_len, scheduler->event_size);
}
