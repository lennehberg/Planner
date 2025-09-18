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
			const ptitle_t title,
			const pdesc_t desc,
			bool_t has_deadline,
			Priorety event_prio
			)
{
	if (!event || !title || !desc ||
		!(event_prio >= NO_PRIORETY && event_prio <= PRIORETY_HIGH))
	{
		return FALSE;
	}
	
	// memcpy parameters to event
	strncpy(event->title, title, TITLE_LEN);
	strncpy(event->desc, desc, DESC_LEN);
	event->time_created = time(NULL); // Assuming localtime is set to correct timezone
	
	// make sure to call setDeadlineEventPlanner if has deadline is true
	// TODO add a check before closing the event that the deadline was added
	event->prio = event_prio;
	event->has_deadline = has_deadline;

	return TRUE;
}



/**
 * PlannerEvent set deadline method. to be called only if has deadline is set
 * to true. if set deadline is set to false, it will be automatically set to 
 * true after this method is called.
 *
 * @param event - a PlannerEvent* to be manipulated
 * @param deadline - should be in pdate_t format
 * @param opt_deadline_time (optional) - sets the deadline time of the event
 */
bool_t setDeadlineEventPlanner(PlannerEvent* event, const pdate_t deadline, 
				const ptime_t opt_deadline_time)
{
	// check event pointer
	if (!event || !deadline)
	{
		return FALSE;
	}

	// if has deadline is set to false, automatically set to true
	if (!event->has_deadline)
	{
		event->has_deadline = TRUE;
	}

	// memcpy the deadline to the event
	event->deadline = deadline;

	// if the deadline time is not null, set it to
	if (opt_deadline_time)
	{
		event->deadline_time = opt_deadline_time;
	}

	return TRUE;
}

