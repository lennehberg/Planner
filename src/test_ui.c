#include "p_ui.h"
#include <ncurses.h>

int test_ui_init()
{
	PlannerUI p_ui = {0};
	
	int p_init_res = p_init_ui(&p_ui);

	if (!p_init_res)
	{
		return 0;
	}

	getch();

	destroy_p_ui(&p_ui);

	return 1;
}

int test_ui_populate_month()
{
	PlannerUI p_ui = {0};
	
	int p_init_res = p_init_ui(&p_ui);

	if (!p_init_res)
	{
		return 0;
	}

	MonthGridWin month_win = p_ui._month_win;
	
	month_win.month = 9;
	month_win.year = 2025;

	populate_month_grid(&month_win);

	getch();
	
	destroy_p_ui(&p_ui);

	return 1;
	
}

int test_ui_init_cursor()
{
	PlannerUI p_ui = {0};

	int p_init_res = p_init_ui(&p_ui);

	if (!p_init_res)
	{
		return 0;
	}

	MonthGridWin month_win = p_ui._month_win;
	month_win.month = 9;
	month_win.year = 2025;

	populate_month_grid(&month_win);

	init_cursor(&month_win, 2, 4);

	getch();
	
	destroy_p_ui(&p_ui);
	
	return 1;
}

int test_ui_update_cursor()
{
	PlannerUI p_ui = {0};

	int p_init_res = p_init_ui(&p_ui);

	if (!p_init_res)
	{
		return 0;
	}

	MonthGridWin month_win = p_ui._month_win;
	month_win.month = 9;
	month_win.year = 2025;

	populate_month_grid(&month_win);

	init_cursor(&month_win, 2, 4);

	getch();

	update_cursor(&month_win, 2, 5);

	getch();
	
	destroy_p_ui(&p_ui);
	
	return 1;
}


int test_ui_cursor_control()
{
	PlannerUI p_ui = {0};

	int p_init_res = p_init_ui(&p_ui);

	if (!p_init_res)
	{
		return 0;
	}

	MonthGridWin month_win = p_ui._month_win;
	month_win.month = 9;
	month_win.year = 2025;

	populate_month_grid(&month_win);

	init_cursor(&month_win, 2, 4);

	int ch = getch();
	
	while(ch != 'q')
	{
		move_cursor(&month_win, ch);
		ch = getch();
	}
	
	destroy_p_ui(&p_ui);
	
	return 1;
}

int test_ui_populate_day_task()
{
	PlannerUI p_ui = {0};
	
	int p_init_res = p_init_ui(&p_ui);

	if (!p_init_res)
	{
		return 0;
	}

	DayTaskWin day_win = p_ui._day_win;
	
	int list_len = 10;
		
	PlannerEvent events[list_len];

	PlannerEvent event = {
		"example event",
		"",
		false,
		0,
		0,
		0,
		0,
		0
	};

	for (int i = 0; i < list_len; i++)
	{
		events[i] = event;
	}

	populate_day_task(&day_win, 0, 0, 0, events, list_len);

	getch();
	
	destroy_p_ui(&p_ui);

	return 1;
}

int test_ui_populate_w_cursor()
{
	PlannerUI p_ui = {0};
	
	int p_init_res = p_init_ui(&p_ui);

	if (!p_init_res)
	{
		return 0;
	}

	DayTaskWin day_win = p_ui._day_win;
	
	int list_len = 10;
		
	PlannerEvent events[list_len];

	PlannerEvent event = {
		"example event",
		"",
		false,
		0,
		0,
		0,
		0,
		0
	};

	for (int i = 0; i < list_len; i++)
	{
		events[i] = event;
	}

	MonthGridWin month_win = p_ui._month_win;
	
	month_win.month = 9;
	month_win.year = 2025;

	populate_month_grid(&month_win);


	init_cursor(&month_win, 2, 4);
	populate_day_task(&day_win, month_win.cursor_cur_nday, month_win.month, month_win.year, 
			events, list_len);

	int ch = getch();
	
	while(ch != 'q')
	{
		move_cursor(&month_win, ch);
		populate_day_task(&day_win, month_win.cursor_cur_nday, month_win.month, month_win.year, 
				events, list_len);
		ch = getch();
	}
	
	destroy_p_ui(&p_ui);

	return 1;

}

int main(int argc, char *argv[])
{
	test_ui_populate_w_cursor();
}
