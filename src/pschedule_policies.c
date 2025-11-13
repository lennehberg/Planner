#include "pschedule_policies.h"
#include "utils.h"
#include "pevent.h"
#include <string.h>


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


void edf_event_policy(void* events_base, void *events_batch, size_t batch_size, 
			size_t count, size_t memb_size)
{
	
	// cast events
	PlannerEvent *pevents_base = (PlannerEvent *)events_base;
	PlannerEvent *pevent = (PlannerEvent *)events_batch;
	
	for (int i = 0; i < batch_size; i++)
	{
		// set the execution time of the event to it's deadline
		if (pevent->has_deadline)
		{
			pevent->execution_time = pevent->deadline;
		}
		// fit the event in the list
		sorted_insert(pevents_base, pevent, count + i, memb_size);

		pevent++;

	}
}
