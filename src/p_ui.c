#include "p_ui.h"
#include "pcalendar.h"
#include <ncurses.h>


// A macro for drawing a horizontal line, inset by 1 character on each side.
#define draw_header(win, width, hheader_liney) mvwhline(win, hheader_liney, 1, ACS_HLINE, width - 2)

// Forward declare the helper functions
WINDOW *init_day_task_win(int height, int width, int starty, int startx);
WINDOW *init_month_grid(int height, int width, int starty, int startx);
void draw_h_lines(WINDOW* win, int height, int width, int num_lines, int starty, int startx);
void draw_v_lines(WINDOW* win, int height, int width, int num_lines, int starty, int startx);
void draw_intersections(WINDOW *win, int height, int width, int grid_rows, int grid_cols,
				int starty, int startx);
void print_week_days(WINDOW* win, int width, int starty, int startx);


/**
 * Initializes the entire Planner UI.
 */
int p_init_ui(PlannerUI *p_ui)
{
	// check p_ui is allocated
	if (!p_ui)
	{
		// TODO error handling
		return 0;
	}

	WINDOW *_day_task, *_month_grid;

	initscr();
    	cbreak(); // no buffering
    	noecho(); // no echoing user input
    	curs_set(0); // cursor visibility 
    	keypad(stdscr, TRUE); // enable special keys
	
	// get terminal parameteres
    	int term_height = LINES;
	int term_width = COLS;
	
	// calculate the size of the day's tasks window
    	int day_win_height = term_height;
    	int day_win_width = term_width / 4;
    	int day_win_starty = 0;
    	int day_win_startx = 0;
	
	// calculate the size of the month grid
    	int month_grid_height = term_height;
    	int month_grid_width = term_width - day_win_width;
    	int month_grid_starty = 0;
    	int month_grid_startx = day_win_width;
	
	// init day task and month grid subwindows
    	_day_task = init_day_task_win(day_win_height, day_win_width,
                                  day_win_starty, day_win_startx);
    	_month_grid = init_month_grid(month_grid_height, month_grid_width,
                                  month_grid_starty,month_grid_startx);
	
	// save windows to ui struct
	DayTaskWin _day_win = {
		_day_task,
		day_win_height,
		day_win_width,
		day_win_height / 5,
		1
	};

	MonthGridWin _month_win = {
		_month_grid,
		month_grid_height,
		month_grid_width,
		month_grid_height - (month_grid_height / 13),
		month_grid_width,
		month_grid_height / 13,
		1
	};

	p_ui->_day_win = _day_win;
	p_ui->_month_win = _month_win;

	// TODO error handling
    	if (!_day_task || !_month_grid)
    	{
        	endwin();
        	return 0;
    	}
	
	// update the screen
    	refresh();
    	wrefresh(_day_task);
    	wrefresh(_month_grid);

    	return 1;
}

// --- DRAWING FUNCTIONS --- //

void draw_h_lines(WINDOW* win, int height, int width, int num_rows, int starty, int startx)
{
    	int available_height = height - starty;
    	for (int i = 1; i < num_rows; i++)
    	{
        	// Calculate the precise y-coordinate for this line
        	int y = starty + (i * available_height) / num_rows;
        	mvwhline(win, y, startx, ACS_HLINE, width - startx - 1);
    	}
}

void draw_v_lines(WINDOW* win, int height, int width, int num_cols, int starty, int startx)
{
    	for (int i = 1; i < num_cols; i++)
    	{
        	// Calculate the precise x-coordinate for this line
        	int x = startx + (i * (width - startx)) / num_cols;
        	mvwvline(win, starty, x, ACS_VLINE, height - starty - 1);
    	}
}

void draw_intersections(WINDOW *win, int height, int width, int grid_rows, int grid_cols, int starty, int startx)
{
    	int available_height = height - starty;
    	for (int r = 1; r < grid_rows; r++)
    	{
        	for (int c = 1; c < grid_cols; c++)
        	{
            	// Calculate precise coordinates for the intersection
            	int y = starty + (r * available_height) / grid_rows;
            	int x = startx + (c * (width - startx)) / grid_cols;
            	mvwaddch(win, y, x, ACS_PLUS);
        	}
    	}
}

void print_week_days(WINDOW *win, int width, int starty, int startx)
{
	int num_of_days = 7;
	// print sunday,...,saturday height below starty with width padding
	const char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday",
				"Thursday", "Friday", "Saturday"};

	for (int i = 0; i < num_of_days; i++)
	{
		int x = startx + (i * (width - startx)) / num_of_days;
		mvwaddstr(win, starty, x, days[i]);
	}
}

/**
 * Creates the window for the daily task list.
 */
WINDOW *init_day_task_win(int height, int width, int starty, int startx)
{
    	WINDOW *day_win = newwin(height, width, starty, startx);
    	if (!day_win) return NULL;
	
	// draw header for a title / time - date display
    	int hheader_liney = height / 5;
    	draw_header(day_win, width, hheader_liney);

	// draw the day's tasks list
    	int list_rows = 10;
    	draw_h_lines(day_win, height, width, list_rows, hheader_liney, 1);

    	box(day_win, 0, 0);
    	return day_win;
}

/**
 * Creates the window for the monthly calendar grid.
 */
WINDOW *init_month_grid(int height, int width, int starty, int startx)
{
    	WINDOW *month_grid = newwin(height, width, starty, startx);
    	if (!month_grid) 
	{
		
		return NULL;
	}
	
	// Draw header for sunday,...,saturday
    	int hheader_liney = height / 13;
    	draw_header(month_grid, width, hheader_liney);

    	int grid_cols = 7, grid_rows = 5; // a maximum of 35 days per month should fit any month conf

    	// Draw the month grid
    	draw_h_lines(month_grid, height, width, grid_rows, hheader_liney, 1);
    	draw_v_lines(month_grid, height, width, grid_cols, hheader_liney + 1, 1); // eliminate 
										  // intersection with
										  // header line
    	draw_intersections(month_grid, height, width, grid_rows, grid_cols, hheader_liney, 1);

	print_week_days(month_grid, width, hheader_liney - 2, 2);

    	box(month_grid, 0, 0);
    	return month_grid;
}

// populate
void populate_month_grid(WINDOW *grid, int height, int width, int grid_cols, int grid_rows,
			int starty, int startx, int month, int year)
{
	// get the start and end of the month
	time_t month_start_t = 0, month_end_t = 0;
	get_month_time_t(&month_start_t, &month_end_t, month, year);

	// find the length of the month in days
	int days_in_month = get_month_len_days(month, year);

	// convert to time struct to extract which day is the first day of the month
	struct tm *month_start_st = localtime(&month_start_t);
	int wday = month_start_st->tm_wday;
	int day_num = 1;
	int available_height = height;

	for (int row = 0; row < grid_rows && day_num <= days_in_month; row++)
	{
		int y = starty + (row * available_height) / grid_rows + 1; // Top left in cell
		for (int col = 0; col < grid_cols && day_num <= days_in_month; col++)
		{
			// Skip cells for the first week until the start day
        		if (row == 0 && col < wday)
			{
            			continue;
        		}

		int x = startx + (col * (width - startx)) / grid_cols + 1; // Top left in cell
		mvwprintw(grid, y, x, "%d", day_num);
		day_num++;
    		}
	}

	wrefresh(grid);
}


void destroy_p_ui(PlannerUI *p_ui)
{
	if (p_ui)
	{
		// delete month window
		if (p_ui->_day_win._day_task)
		{
			delwin(p_ui->_day_win._day_task);
		}

		// delete day window
		if (p_ui->_month_win._month_grid)
		{
			delwin(p_ui->_month_win._month_grid);
		}
	}

	// end curses mode
	endwin();
}
