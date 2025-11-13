#ifndef PCONTROLLER_H
#define PCONTROLLER_H

#include "pevent.h"
#include "p_ui.h"
#include "scheduler.h"
#include "pschedule_policies.h"

#define EVENTS_CAP 100

typedef struct AppContext {

	PlannerUI p_ui;
	PlannerEvent events_base[EVENTS_CAP];
	Scheduler p_sched;
	scheduleBatchFunc sched_func;

	size_t event_count;
	size_t event_cap;

} Controller;


int controller_init(Controller *app, PlannerEvent *initial_events, size_t event_count);

void update_planner(Controller *app);

#endif // PCONTROLLER_H
