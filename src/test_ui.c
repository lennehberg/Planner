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


	populate_month_grid(month_win._month_grid, month_win.grid_height, month_win.grid_width, 7, 5,
				month_win.r_grid_starty, month_win.r_grid_startx, 9, 2025);

	getch();
	
	destroy_p_ui(&p_ui);

	return 1;
	
}

int main(int argc, char *argv[])
{
	test_ui_init();
	test_ui_populate_month();
}
