#include <stdio.h>
#include "scheduler.h"
#include "pschedule_policies.h"
#include "pevent.h"

#define CAP_1 10

int test_edf_scheduling()
{
	PlannerEvent events_base[3];
	
	// set some test events
	initPlannerEvent(&events_base[0], "test event 0", "desc", true, 0);
	initPlannerEvent(&events_base[1], "test event 1", "desc", true, 0);

	events_base[0].deadline = 100;
	events_base[0].execution_time = 100;
	events_base[1].deadline = 150;
	events_base[1].execution_time = 150;

	// set an event to schedule
	PlannerEvent test_event;

	initPlannerEvent(&test_event, "test event to schedule", "desc", true, 0);
	test_event.deadline = 125;
	

	edf_event_policy((void *)events_base, &test_event, 1, 2, sizeof(PlannerEvent));

	printf("Event 0 title: %s, execution time: %ld\
		\nEvent 1 title: %s, execution time: %ld\
		\nEvent 2 title: %s, execution time: %ld\n", 
					events_base[0].title, events_base[0].execution_time,
					events_base[1].title, events_base[1].execution_time,
					events_base[2].title, events_base[2].execution_time);

	return 1;
}


int test_scheduler()
{
	time_t deadlines[] = {150, 432, 234, 10, 234, 324, 42130, 12232, 32, 3124};

	Scheduler sched = {0};
	Scheduler *sched_inst = &sched;
	size_t cap = 10;
	sched_inst = scheduler_init(&sched, sizeof(PlannerEvent), CAP_1, edf_event_policy);

	PlannerEvent events_base[CAP_1] = {0};
	sched.events = events_base;

	PlannerEvent test_batch[CAP_1 / 2] = {0};

	for (int i = 0; i < CAP_1 / 2 + 1; i++)
	{
		char title[TITLE_LEN];
		snprintf(title, TITLE_LEN, "test title %d", i);
		char *desc = "desc";
		initPlannerEvent(&test_batch[i], title, desc, true, 0);
		test_batch[i].deadline = deadlines[i];
	}

	add_batch(&sched, test_batch, CAP_1 / 2);
	add_event(&sched, &test_batch[CAP_1 / 2]); 
	PlannerEvent *pevents = (PlannerEvent *)sched.events;

	for (int i = 0; i < CAP_1 / 2 + 1; i++)
	{
		
		printf("Event %d title %s, execution_time: %ld, deadline: %ld\n", 
								i, 
								pevents[i].title, 
								pevents[i].execution_time,
								pevents[i].deadline);
	}

	return 1;
}


int main(int argc, char *argv[])
{
	test_scheduler();
}
