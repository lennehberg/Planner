#ifndef _P_UI_H
#define _P_UI_H

#include <ncurses.h>

typedef struct {
	
	WINDOW *_month_grid;

	int month_win_height; // height of the month window
	int month_win_width; // width of the month window
	int grid_height; // height of the grid
	int grid_width; // width of the grid
	int r_grid_starty; // relative (to month window) grid starty
	int r_grid_startx; // relative grid startx

} MonthGridWin;

typedef struct {

	WINDOW *_day_task;
		
	int day_win_height; // height of day task window
	int day_win_width; // width of day task window
	int r_task_list_starty; // relative (to day window) list starty
	int r_task_list_startx; // relative list startx

} DayTaskWin;

typedef struct {

	DayTaskWin _day_win;
	MonthGridWin _month_win;	

} PlannerUI;

int p_init_ui(PlannerUI *p_ui);

void populate_month_grid(WINDOW *grid, int height, int width, int grid_cols, int grid_rows,
			int starty, int startx, int month, int year);

void destroy_p_ui(PlannerUI *p_ui);

#endif // _P_UI_H
