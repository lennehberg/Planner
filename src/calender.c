#include "calender.h"
#include <stdlib.h>


calender_t *alloc_days_(calender_t *new_calen_)
{
    for (year_t year = 0; year < NUM_YEARS; ++year)
    {
        for (MONTH month = 0; month < NUM_MONTHS; ++month)
        {
            // TODO MALLOC ERROR
            (*new_calen_).calender_arr_[year][month] = calloc(DAYS_IN_MONTH(month, year), sizeof(event_t));
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
        (*calen).cur_day_->day_ = 0;
        (*calen).cur_day_->month_ = 0;
        (*calen).cur_day_->year_ = 0;
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

void add_calender_event(calender_t *calen, event_t *event)
{
    // check the date and time of the event and add to
    // calendar where relevant
    date_t date = event->date;
    calen->calender_arr_[date.year_][date.month_][date.day_] = malloc(sizeof(event_t));
    // TODO MALLOC ERROR
    // copy event to calender
}