#ifndef PCALENDAR_H
#define PCALENDAR_H

#include "utils.h"
#include "pevent.h"

void get_month_time_t(time_t *month_start_t, time_t *month_end_t, int month, int year);

int get_month_len_days(int month, int year);

int get_first_wday_month(int month, int year);


size_t filter_events_day_month_year(PlannerEvent *events, PlannerEvent **ret_ptr, int event_count,
					int day, int month, int year);

#endif // PCALENDAR_H
