#include "scheduler.h"


#define INITIAL_CAP 100

/**
 * Scheduler Init method
 * @param events - void* to array of events
 * @param schedule - function which takes array of events and returns 
 * 			an array of array to run
 *			void* (*ScheduleFunc)(void *events, size_t count, size_t memb_size)
 *
 * @return scheduler entity
 */
Scheduler *scheduler_init(Scheduler *scheduler, size_t event_size, size_t cap, 
			scheduleBatchFunc schedule_batch, void *events)
{
	scheduler->events = events;
	scheduler->event_size = event_size;
	scheduler->events_len = 0;
	scheduler->capacity = cap;

	scheduler->schedule_batch = schedule_batch;

	return scheduler;
}


int add_batch(Scheduler *scheduler, void *events, size_t batch_size)
{
	// TODO handling over capcaity
	if (scheduler->events_len + batch_size <= scheduler->capacity)
	{
		scheduler->schedule_batch(scheduler->events, events, batch_size, 
						scheduler->events_len, scheduler->event_size);
		scheduler->events_len += batch_size;
		return 1;
	}
	return 0;
}

int add_event(Scheduler *scheduler, void *event)
{
	if (scheduler->events_len + 1 <= scheduler->capacity)
	{
		scheduler->schedule_batch(scheduler->events, event, 1, 
						scheduler->events_len, scheduler->event_size);
		scheduler->events_len++;
		return 1;
	}
	return 0;
}


