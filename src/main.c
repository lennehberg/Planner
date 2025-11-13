#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "pevent.h"
#include "scheduler.h"
#include "pschedule_policies.h"
#include "p_ui.h"
#include "pcontroller.h"

#define MAX_LINE_LEN 256
#define EVENTS_CAP 100


int load_events_from_csv(const char *filepath, PlannerEvent *events_buffer, int max_events)
{
	FILE *file = fopen(filepath, "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return -1;
	}

	char line[MAX_LINE_LEN];
	int event_count = 0;

	while (fgets(line, sizeof(line), file) && event_count < max_events)
	{
		char title[sizeof(ptitle_t)] = {0};
		char description[sizeof(pdesc_t)] = {0}; // Correctly sized empty buffer
		int priority = 0;
		long deadline_l = 0;

		// Use sscanf for safe, non-destructive parsing from the buffer
		int items_scanned = sscanf(line, "%[^,],%d,%ld", title, &priority, &deadline_l);

		if (items_scanned >= 2) { // At least title and priority are required
			PlannerEvent *current_event = &events_buffer[event_count];
			bool has_deadline = (items_scanned == 3);
			
			// Use the official constructor with the correctly sized buffer
			initPlannerEvent(current_event, title, description,
					has_deadline, (Priorety)priority);

			if (has_deadline) {
				current_event->deadline = (time_t)deadline_l;
			}
			
			event_count++;
		}
	}

	fclose(file);
	return event_count;
}


size_t read_events(const char *filename, PlannerEvent *events_buffer, size_t buffer_cap)
{
	return 0;
}



void check_mailbox(Controller *context)
{
	return;
}


int init(Controller *context, PlannerEvent *initial_events, size_t buffer_cap, const char* filename)
{
	// TODO load events for inital events

	size_t event_count = load_events_from_csv(filename, initial_events, buffer_cap);	
	
	// init the planner ui, the scheduler, and a base for the list of events
	if (!controller_init(context, initial_events, event_count))
	{
		// TODO error handling
		return 0;
	}

	return 1;
}



int run(Controller *context)
{
	jump_to_today(&context->p_ui._month_win);
	update_planner(context);

	timeout(10000);

	// wait for user input
	while(true)
	{
		int ch = getch();
		if (ch == 'q')
		{
			break; // user has decided to terminate program
		}
		else if (ch == ERR)
		{
			// check if a day has passed
			jump_to_today(&context->p_ui._month_win);
		
			// check mailbox for new events
			check_mailbox(context);
		}
		else
		{
			// move curser upon specified input and update
			move_cursor(&context->p_ui._month_win, ch);	
		}
		// update planner
		update_planner(context);
	}

	return 1;
}


int end(Controller *context)
{
	// destroy all objects, save events for continuity
	destroy_p_ui(&context->p_ui);
	return 1;
}


int main(int argc, char *argv[])
{
	// get filepath from argv
	const char *events_filepath = "events.csv";

	if (argc > 1)
	{
		// user passed a filepath to program, use it instead of default
		events_filepath = argv[1];
		printf("Loading events from specified file: %s...\n", events_filepath);
	}
	else
	{
		printf("Defaulting to default events file.\n");
	}

	// init all resrouces
	PlannerEvent initial_events[EVENTS_CAP]; 
	Controller context = {0};
	context.sched_func = edf_event_policy;

	init(&context, initial_events, EVENTS_CAP, events_filepath);

	// run the program
	run(&context);	
	// terminate gracefully
	end(&context);

	return 0;
}
