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
		1,
		10
	};

	MonthGridWin _month_win = {
		_month_grid,

		0, 0,

		month_grid_height,
		month_grid_width,
		month_grid_height - (month_grid_height / 13),
		month_grid_width,
		month_grid_height / 13,
		1,

		5, 7,
		0, 0
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


int grid_coords(MonthGridWin *month_win, int row, int col, int *y, int *x)
{
	int height = month_win->grid_height;
	int width = month_win->grid_width;
	int starty = month_win->r_grid_starty;
	int startx = month_win->r_grid_startx;
	int grid_rows = month_win->grid_rows;
	int grid_cols = month_win->grid_cols;

	int available_height = height;
	int available_width = width;
	
	if (row > grid_rows || col > grid_cols)
	{
		return 0;
	}

	*y = starty + (row * available_height) / grid_rows + 1;
	*x = startx + (col * available_width) / grid_cols + 1;

	return 1;
}


int list_y(DayTaskWin *day_win, int row, int *y)
{
	int height = day_win->day_win_height - day_win->r_task_list_starty;
	int starty = day_win->r_task_list_starty;
	int list_rows = day_win->list_len;

	if (row < 0 || row > list_rows)
	{
		return 0;
	}

	*y = starty + (row * height) / list_rows + 1;

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
void populate_month_grid(MonthGridWin *month_win)
{
	WINDOW *grid = month_win->_month_grid;
	int height = month_win->grid_height;
	int width = month_win->grid_width;
	int grid_cols = month_win->grid_cols;
	int grid_rows = month_win->grid_rows;
	int starty = month_win->r_grid_starty;
	int startx = month_win->r_grid_startx;
	int month = month_win->month;
	int year = month_win->year;

	// find the length of the month in days
	int days_in_month = get_month_len_days(month, year);
	
	// get the first week day of the month
	int wday = get_first_wday_month(month, year);
	int day_num = 1;
	int available_height = height;

	for (int row = 0; row < grid_rows && day_num <= days_in_month; row++)
	{
		int y, x; 
		for (int col = 0; col < grid_cols && day_num <= days_in_month; col++)
		{
			grid_coords(month_win, row, col, &y, &x);
			// Skip cells for the first week until the start day
        		if (row == 0 && col < wday)
			{
            			continue;
        		}

		mvwprintw(grid, y, x, "%d", day_num);
		day_num++;
    		}
	}

	wrefresh(grid);
}


void redraw_cell(MonthGridWin *month_win, int row, int col, bool highlight)
{
	WINDOW *grid = month_win->_month_grid;
	int month = month_win->month;
	int year = month_win->year;

	// find the first day of the week
	int first_wday = get_first_wday_month(month, year);

	// calculate the day number of the cell
	int day_num = (row * 7 + col) - first_wday + 1;
	int days_in_month = get_month_len_days(month, year);

	// dont draw if cell is empty
	if (day_num < 1 || day_num > days_in_month)
	{
		return;
	}

	// find the y x coordinates of the cell
	int y, x;
	grid_coords(month_win, row, col, &y, &x);

	// apply hightlight if needed
	if (highlight)
	{
		wattron(grid, A_REVERSE);
	}

	// redraw the number in the cell
	mvwprintw(grid, y, x, "%d", day_num);

	// turn off highlight
	wattroff(grid, A_REVERSE);
}


void init_cursor(MonthGridWin *month_win, int row, int col)
{
	int first_wday = get_first_wday_month(month_win->month, month_win->year);
	month_win->cursor_row = row;
	month_win->cursor_col = col;

	month_win->cursor_cur_nday = (row * 7 + col) - first_wday + 1;

	redraw_cell(month_win, row, col, true);

	wrefresh(month_win->_month_grid);
}


void update_cursor(MonthGridWin *month_win, int row, int col)
{
	int first_wday = get_first_wday_month(month_win->month, month_win->year);
	int cur_day = (row * 7 + col) - first_wday + 1;
	if (cur_day > 0 && cur_day < get_month_len_days(month_win->month, month_win->year) + 1)
	{
		redraw_cell(month_win, month_win->cursor_row, month_win->cursor_col, false);
	
		month_win->cursor_row = row;
		month_win->cursor_col = col;
		month_win->cursor_cur_nday = cur_day;

		redraw_cell(month_win, month_win->cursor_row, month_win->cursor_col, true);
	}
	wrefresh(month_win->_month_grid);
}


void move_cursor(MonthGridWin *month_win, int ch)
{
	int cursor_row = month_win->cursor_row;
	int cursor_col = month_win->cursor_col;

	switch(ch)
	{
		case KEY_LEFT:
			if (cursor_col == 0 && cursor_row == 0)
			{
				// TODO add logic to shift change month
				break;
			}
			else if (cursor_col == 0)
			{
				// move the cursor up a row to the last col
				update_cursor(month_win, cursor_row - 1, month_win->grid_cols - 1);
			}
			else
			{
				// move the cursor back a col
				update_cursor(month_win, cursor_row, cursor_col - 1);
			}
			break;
		case KEY_RIGHT:
			if (cursor_col == month_win->grid_cols - 1 
				&& cursor_row == month_win->grid_rows - 1)
			{
				// TODO add logic to shift change month
				break;
			}
			else if (cursor_col == month_win->grid_cols - 1)
			{
				// move the cursor down a row to the first col
				update_cursor(month_win, cursor_row + 1, 0);
			}
			else
			{
				// move the cursor forward a col
				update_cursor(month_win, cursor_row, cursor_col + 1);
			}
			break;
	}	
}


void populate_day_task(DayTaskWin *day_win, int dday, int dmonth, int dyear,
		PlannerEvent *day_events, int event_count)
{
	// print the title of the event at each list block
	PlannerEvent *cur_event = day_events;
	WINDOW *day_task = day_win->_day_task;
	int list_rows = day_win->list_len;
	int y = 3;
	int x = 3;

	int max_ddate_width = 2 + 1 + 3 + 1 + 4; // in dd/mmm/yyyy representation
	// clear header before displaying date
	mvwhline(day_task, y, x, ' ', max_ddate_width);
	mvwprintw(day_task, y, x, "%d/%d/%d", dday, dmonth, dyear);

	for (int row = 0; row < list_rows && row < event_count; row++)
	{
		// TODO check for errors
		list_y(day_win, row, &y);
		mvwprintw(day_task, y, x, "%s" ,cur_event->title);
		cur_event++;
	}

	wrefresh(day_task);
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
