#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stddef.h>


typedef void (*scheduleBatchFunc)(void *events_base, void *events, size_t batch_size, 
					size_t count, size_t memb_size); // custom schedule 
									 // policy for batch
									 // events

typedef void* (*ScheduleFunc)(void* events, size_t count, size_t memb_size);

/**
 * Scheduler struct, with the ability to set a custom scheduling policy
 */
typedef struct Scheduler{
	
	void* events; // array of events to schedule
	size_t event_size; // size of each event
	size_t events_len; // length of events array
	size_t capacity;   // total capacity of scheduler
	
	scheduleBatchFunc schedule_batch; //  dynamic schedule policy for batch of events

} Scheduler;

Scheduler *scheduler_init(Scheduler *scheduler, size_t event_size, size_t cap, 
			scheduleBatchFunc schedule_batch, void *events);

int add_batch(Scheduler *scheduler, void *events, size_t batch_size);

int add_event(Scheduler *scheduler, void *event);

#endif //
