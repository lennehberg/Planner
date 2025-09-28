#include "pschedule_policies.h"
#include "utils.h"
#include "pevent.h"
#include <string.h>

int _compare_event_executions(const void *a, const void *b)
{
	time_t time_a = ((const PlannerEvent *)a)->execution_time;
	time_t time_b = ((const PlannerEvent *)b)->execution_time;

	if (time_a < time_b) return -1;
	if (time_a > time_b) return 1;

	return 0;
}


void sorted_insert(PlannerEvent *head, PlannerEvent *event, size_t count, size_t memb_size)
{
	// using lower bound, find the event with the closest execution time
	PlannerEvent *l_bound = (PlannerEvent *)find_lower_bound(event, 
								head,
								count,
								memb_size,
								_compare_event_executions);

	
	size_t index = l_bound - head;
	// make room for the event after the head 
	if (index < count)
	{
	
		memmove(&head[index + 1],
			&head[index],
			(count - index) * memb_size);	
	}

	// copy the event into the list
	head[index] = *event;
}


void edf_event_policy(void** events_base, void *event, size_t count, size_t memb_size)
{
	
	// cast events
	PlannerEvent **pevents_base = (PlannerEvent **)events_base;
	PlannerEvent *pevent = (PlannerEvent *)event;
	
	// set the execution time of the event to it's deadline
	if (pevent->has_deadline)
	{
		pevent->execution_time = pevent->deadline;
	}

	// fit the event in the list
	sorted_insert(*pevents_base, pevent, count, memb_size);
}
