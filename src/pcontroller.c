#include <stdio.h>
#include "pevent.h"
#include "p_ui.h"
#include "pcalendar.h"
#include "pcontroller.h"
#include <string.h>
#include "pschedule_policies.h"

#define EVENTS_CAP 100

void update_planner(Controller *app)
{
	MonthGridWin *month_win_ptr = &app->p_ui._month_win;
	DayTaskWin *day_win_ptr = &app->p_ui._day_win;

	int day = month_win_ptr->cursor_cur_nday;
	int month = month_win_ptr->month;
	int year = month_win_ptr->year;

	// filter the events of events_base according to cursor
	PlannerEvent *event_ptr = NULL;
	size_t count = filter_events_day_month_year(app->events_base, &event_ptr, app->event_count,
							day, month, year);	
	// populate the day task
	populate_day_task(day_win_ptr, day, month, year, event_ptr, count);
}

int controller_init(Controller *app, PlannerEvent *initial_events, size_t event_count)
{
	// init the planner ui and scheduler
	app->event_count = 0;

	if (!p_init_ui(&app->p_ui))
		return 0;

	if (!scheduler_init(&app->p_sched, sizeof(PlannerEvent), EVENTS_CAP, 
				app->sched_func, app->events_base))
		return 0;
	

	// copy events from initial events to events base
	if (initial_events != NULL && event_count > 0)
	{
		// check how many events to copy
		size_t count_to_copy = (event_count < EVENTS_CAP) ? event_count : EVENTS_CAP;
		// copy the data from the initial events to events base
		memcpy(app->events_base, initial_events, count_to_copy * sizeof (PlannerEvent));
		app->event_count = count_to_copy;
	}
	
	// schedule added events
	if (app->event_count > 0)
	{
		add_batch(&app->p_sched, app->events_base, event_count);
	}

	return 1;
	
}
