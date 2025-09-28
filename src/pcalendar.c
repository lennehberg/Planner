#include "pcalendar.h"
#include "pevent.h"

#define EPOCH_YEAR 1900


int _compare_event_executions(const void *a, const void *b)
{
	time_t time_a = ((const PlannerEvent *)a)->execution_time;
	time_t time_b = ((const PlannerEvent *)b)->execution_time;

	if (time_a < time_b) return -1;
	if (time_a > time_b) return 1;

	return 0;
} 



/**
 * Convert the month/year to a a start month time_t and an end month time_t
 */
void get_month_time_t(time_t *month_start_t, time_t *month_end_t ,int month, int year)
{
	// find the start of the month in time_t
	struct tm time_spec = {0};
	time_spec.tm_year = year - EPOCH_YEAR;
	time_spec.tm_mon = month - 1; // assuming months are labeled Jan = 1,...,Dec = 12	
	time_spec.tm_mday = 1;
	
	if (month_start_t)
	{
		*month_start_t = mktime(&time_spec);
	}

	// find the end of the month in time_t
	time_spec = (struct tm){0};
	time_spec.tm_year = year - EPOCH_YEAR;
	time_spec.tm_mon = month; // assuming months are labeled Jan = 1,...,Dec = 12	
	time_spec.tm_mday = 1; // by calculating the first day of the next month, mktime sets the time to 				// 00:00:00 of that day, in an [inclusive_start, exclusive_end] range 
			       // should work pretty well
	if (month_end_t)
	{
		*month_end_t = mktime(&time_spec);
	}
}


void get_day_time_t(time_t *day_start_t, time_t *day_end_t, int day, int month, int year)
{
	// find the time_t of the start of the day
	struct tm time_spec = {0};
	time_spec.tm_year = year - EPOCH_YEAR;
	time_spec.tm_mon = month - 1; // assuming Jan = 1,...,Dec = 12
	time_spec.tm_mday = day;

	if (day_start_t)
	{
		*day_start_t = mktime(&time_spec);
	}

	// find the time_t of the end of the day (00:00:00 of the next day)
	time_spec = (struct tm){0};
	time_spec.tm_year = year - EPOCH_YEAR;
	time_spec.tm_mon = month - 1;
	time_spec.tm_mday = day + 1;

	if (day_end_t)
	{
		*day_end_t = mktime(&time_spec);
	}
}

/**
 * Get the length of the month in days
 */
int get_month_len_days(int month, int year)
{
	// find the length of the month in days
	struct tm time_spec = {0};
	time_spec.tm_year = year - 1900;
	time_spec.tm_mon = month; // Month after the target one
	time_spec.tm_mday = 0; // 0th day is last day of previous month
	mktime(&time_spec);
	return time_spec.tm_mday;
}

/**
* Given a list of event, and a month/year to display - filter the list of events accordingly
*/
size_t filter_events_month_year(PlannerEvent* events, PlannerEvent** ret_ptr, int event_count,
					int month, int year)
{
	size_t filtered_amount = 0;

	// get the first day and last day of the month
	time_t month_start_t = 0, month_end_t = 0;
	get_month_time_t(&month_start_t, &month_end_t, month, year);

	// use binary search (lower bound) to find the first event in the month
	PlannerEvent key_event; // dummy event for key
	key_event.execution_time = month_start_t;

	PlannerEvent *first_event = (PlannerEvent *)find_lower_bound(&key_event, 
									events,
									event_count,
									sizeof(PlannerEvent),
									_compare_event_executions);
	key_event.execution_time = month_end_t;

	PlannerEvent *last_event = (PlannerEvent *)find_lower_bound(&key_event, 
									events,
									event_count,
									sizeof(PlannerEvent),
									_compare_event_executions);
	

	// iteratae from the first event in the month to the last event of the month, adding
	// the events to filtered events
	if (first_event < events + event_count) // make sure an appropriate event 									was found
	{
		*ret_ptr = first_event;
		filtered_amount = last_event - first_event;
	}


	return filtered_amount;
}


size_t filter_events_day_month_year(PlannerEvent *events, PlannerEvent **ret_ptr, int event_count,
					int day, int month, int year)
{
	size_t filtered_amount = 0;

	// get the beginning and end of the day
	time_t day_start_t = 0, day_end_t = 0;
	get_day_time_t(&day_start_t, &day_end_t, day, month, year);

	// use lower bound binary search to find the first event of the day
	PlannerEvent key_event;
	key_event.execution_time = day_start_t;

	PlannerEvent *first_event = (PlannerEvent *)find_lower_bound(&key_event,
									events,
									event_count,
									sizeof(PlannerEvent),
									_compare_event_executions);

	key_event.execution_time = day_end_t;

	PlannerEvent *last_event = (PlannerEvent *)find_lower_bound(&key_event,
									events,
									event_count,
									sizeof(PlannerEvent),
									_compare_event_executions);

	// check the first event of the day was found and is valid
	if (first_event < events + event_count)
	{
		*ret_ptr = first_event;
		filtered_amount = last_event - first_event;
	}

	return filtered_amount;
}


int get_first_wday_month(int month, int year)
{
	time_t month_start_t = 0;
	get_month_time_t(&month_start_t, NULL, month, year);

	// convert to tm struct to extract the first week day
	struct tm *month_start_st = localtime(&month_start_t);
	return month_start_st->tm_wday;
}
