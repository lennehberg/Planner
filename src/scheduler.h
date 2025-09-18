#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stddef.h>

typedef void* (*ScheduleFunc)(void* events, size_t count, size_t memb_size);

typedef struct Scheduler Scheduler;

Scheduler schedulerInit(void* events, size_t event_size, 
		size_t events_len, ScheduleFunc schedule);

void* schedulerEvent(Scheduler* scheduler);

#endif //
