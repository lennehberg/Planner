#include "scheduler.h"

typedef void (*scheduleEventFunc)(void **events_base, void *event,
					size_t count, size_t memb_size); // custom schedule policy

typedef void (*scheduleBatchFunc)(void **events_base, void *events, size_t batch_size, 
					size_t count, size_t memb_size); // custom schedule 
									 // policy for batch
									 // events

#define INITIAL_CAP 100

/**
 * Scheduler struct, with the ability to set a custom scheduling policy
 */
typedef struct Scheduler{
	
	void* events; // array of events to schedule
	size_t event_size; // size of each event
	size_t events_len; // length of events array
	size_t capacity;   // total capacity of scheduler
	scheduleEventFunc schedule_event; // dynamic schedule policy for a single event
	scheduleBatchFunc schedule_batch; // 			     for batch of events

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
Scheduler *scheduler_init(Scheduler *scheduler, size_t event_size, 
			scheduleBatchFunc schedule_batch, scheduleEventFunc schedule_event)
{
	scheduler->events = NULL;
	scheduler->event_size = event_size;
	scheduler->events_len = 0;
	scheduler->capacity = INITIAL_CAP;

	scheduler->schedule_batch = schedule_batch;
	scheduler->schedule_event = schedule_event;

	return scheduler;
}


int add_batch(Scheduler *scheduler, void *events, size_t batch_size)
{
	// TODO handling over capcaity
	if (scheduler->events_len + batch_size < scheduler->capacity)
	{
		scheduler->schedule_batch(&scheduler->events, events, batch_size, 
						scheduler->events_len, scheduler->event_size);
		return 1;
	}
	return 0;
}


/**
 * Scheduler custom schedule policy method - calls the policy set by init
 * @param scheduler
 * @return void * of events
 */
int add_event(Scheduler *scheduler, void *event)
{
	// TODO handling over capacity
	if (scheduler->events_len + 1 < scheduler->capacity)
	{
	 	scheduler->schedule_event(&scheduler->events, event,
				 scheduler->events_len, scheduler->event_size);
		return 1;
	}
	return 0;
}
