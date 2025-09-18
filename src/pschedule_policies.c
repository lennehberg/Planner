#include "pschedule_policies.h"
#include "utils.h"
#include "pevent.h"


void* basic_policy(void* events, size_t count)
{
	
	PlannerEvent* events_array = (PlannerEvent*)events;


	// very basic, return the first event in the array
	return (void*)&events_array[0];

}
