#include "pevent.h"
#include <string.h>


/**
 * PlannerEvent init method
 * @param event - pointer to allocated PlannerEvent
 * @param title - should be limited to TITLE_LEN
 * @param desc - should be limited to DESC_LEN
 * @param has_deadline - if true, init should be followed up with a call to 
 * 			 addDeadlinePlannerEvent
 * @param cur_date
 * @param cur_time
 */
bool_t initPlannerEvent(PlannerEvent* event,
			ptitle_t title,
			pdesc_t desc,
			bool_t has_deadline,
			pdate_t cur_date,
			ptime_t cur_time,
			Priorety event_prio
			)
{
	if (!event || !title || !desc || !cur_time || !cur_date ||
		!(event_prio >= NO_PRIORETY && event_prio <= PRIORETY_HIGH))
	{
		return FALSE;
	}
	
	// memcpy parameters to event
	memcpy(event->title, title, TITLE_LEN);
	memcpy(event->desc, desc, DESC_LEN);
	memcpy(event->date_created, cur_date, DATE_VAR_LEN);
	memcpy(event->time_created, cur_time, TIME_VAR_LEN);
	
	event->prio = event_prio;
	event->has_deadline = has_deadline;

	return TRUE;
}

