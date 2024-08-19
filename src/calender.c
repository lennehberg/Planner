#include "calender.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


calender_t *alloc_days_(calender_t *new_calen_)
{
    for (year_t year = 0; year < NUM_YEARS; ++year)
    {
        for (MONTH month = 0; month < NUM_MONTHS; ++month)
        {
            // TODO MALLOC ERROR
            (*new_calen_).calender_arr_[year][month] = calloc(DAYS_IN_MONTH
				(month, year), sizeof(event_list));
        }
    }
    return new_calen_;
}

void set_cur_day_(calender_t *calen, date_t *date)
{
    // TODO MALLOC ERROR
    (*calen).cur_day_ = malloc(sizeof(date_t));
    // set the calenders current day to a given date, if one is given
    // else default to january first of START_YEAR
    if (!date)
    {
        (*calen).cur_day_->day_ = 1;
        (*calen).cur_day_->month_ = JAN;
        (*calen).cur_day_->year_ = START_YEAR;
    }
    else
    {
        (*calen).cur_day_->day_ = date->day_;
        (*calen).cur_day_->month_ = date->month_;
        (*calen).cur_day_->year_ = date->year_;
    }
}

calender_t *init_calender_(date_t *date)
{
    // TODO MALLOC ERROR
    calender_t *new_calen_ = malloc(sizeof(calender_t));
    // as the months and years are statically allocated, 
    // only need to allocate an array for all the days, whih
    // will have an array of events
    new_calen_ = alloc_days_(new_calen_);
    // set the current day to be januray 1st of START_YEAR
    set_cur_day_(new_calen_, date);
    return new_calen_;
}

int comp_events(const void *lhs, const void *rhs)
{
  event_t *lhs_event = (event_t *)lhs;
  event_t *rhs_event = (event_t *)rhs;
  int ret;

  if (lhs_event->time_.hour_ < rhs_event->time_.hour_)
  {
	ret = -1;
  }
  else if (lhs_event->time_.hour_ > rhs_event->time_.hour_)
  {
	ret = 1;
  }
  else
  {
	if (lhs_event->time_.min_ < rhs_event->time_.min_)
	{
	  ret = -1;
	}
	else if (lhs_event->time_.min_ > rhs_event->time_.min_)
	{
	  ret = 1;
	}
	else
	{
	  if (lhs_event->time_.sec_ > rhs_event->time_.sec_)
	  {
		ret = -1;
	  }
	  else if (lhs_event->time_.sec_ > rhs_event->time_.sec_)
	  {
		ret = 1;
	  }
	  else
	  {
		ret = 0;
	  }
	}
  }
  return ret;
}

void add_calender_event_(calender_t *calen, event_t *event)
{
    // check the date and time of the event and add to
    // calendar where relevant
    date_t date = event->date;
	event_list *cur_list = &(calen->calender_arr_[date.year_ - START_YEAR]
										[date.month_][date.day_]);
	// if the event list of the day is empty, allocate a new event list
	// for that day
	// TODO allocation errors
  	if (!cur_list->head_ptr_)
	{
	  cur_list->size = 1;
	  cur_list->head_ptr_ = malloc(sizeof(event_t));
	  memcpy (cur_list->head_ptr_, event, sizeof(event_t));
  	}
  	else
	{
	  ++cur_list->size;
	  cur_list->head_ptr_ = realloc(cur_list->head_ptr_,
									cur_list->size * sizeof(event_t));
	  memcpy (&cur_list->head_ptr_[cur_list->size - 1], event,
			  sizeof(event_t));
	}
	// TODO sort events of date
	qsort(cur_list->head_ptr_, cur_list->size,
		  sizeof(event_t), &comp_events);
}

event_list *get_events_(calender_t *calen, const date_t date)
{
  event_list *ret_list = &calen->calender_arr_[date.year_ - START_YEAR]
											  [date.month_][date.day_];
  return ret_list;
}

void print_calender_(calender_t *calen)
{
  for (year_t year = 0; year < NUM_YEARS; ++year)
  {
	for (MONTH month = JAN; month < NUM_MONTHS; ++month)
	{
	  for (day_t day = 0; day < DAYS_IN_MONTH(month, year); ++day)
	  {
		if (calen->calender_arr_[year][month][day].size > 0)
		{
		  printf("DATE: %d/%d/%d\n", day, month, year + START_YEAR);
		  printf("Events:\n");
		  for (int i = 0; i < calen->calender_arr_[year][month][day].size; ++i)
		  {
			printf (" Title: %s\n Description: %s\n Time: %d:%d:%d\n",
					calen->calender_arr_[year][month][day].head_ptr_[i].title_,
					calen->calender_arr_[year][month][day].head_ptr_[i]
						.description_,
					calen->calender_arr_[year][month][day].head_ptr_[i].time_
						.hour_,
					calen->calender_arr_[year][month][day].head_ptr_[i].time_
						.min_,
					calen->calender_arr_[year][month][day].head_ptr_[i].time_
						.sec_);
		  }
		}
	  }
	}
  }
}