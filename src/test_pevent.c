#include "pevent.h"
#include <stdio.h>

int test_init_event()
{
	PlannerEvent event;

	initPlannerEvent(&event, "test event", "desc", false, 0);

	printf("Event title: %s\nEvent desc: %s\n", event.title, event.desc);

	return 1;
}


int main(int argc, char *argv[])
{
	test_init_event();
}
