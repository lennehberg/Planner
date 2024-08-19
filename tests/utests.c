#include "../src/calender.c"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int test_calender_init_null_date();
int test_calender_init_nonnull_date();
int test_add_1_calender_event();
int test_add_2_events_different_dates();
int test_add_2_events_same_date();
int test_sort_events();
int test_get_events();
int test_print();
int main()
{
    assert (test_calender_init_null_date() == 0);
    printf("Null date init passed Successfully!\n");
	assert (test_calender_init_nonnull_date() == 0);
	printf("Nonnull date init passed successfully!\n");
	assert(test_add_1_calender_event() == 0);
	printf("Event added successfully!");
	assert(test_add_2_events_different_dates() == 0);
	printf("2 Events added successfully!\n");
	assert(test_add_2_events_same_date() == 0);
  	printf("2 Events added successfully to the same date!\n");
  	assert(test_sort_events() == 0);
	printf("Events successfully sorted!\n");
	assert(test_get_events() == 0);
	printf("Events got successfully!\n");
	assert(test_print() == 0);
  	printf("Calender print successful!\n");
}

int test_calender_init_null_date()
{
    calender_t *calen = init_calender_(NULL);

    if (calen)
    {
        if (calen->calender_arr_ || calen->cur_day_)
        {
            if (calen->cur_day_->day_ == 1 && calen->cur_day_->month_ == JAN
			&& calen->cur_day_->year_ == START_YEAR)
            {
                return 0;
            }
        }
    }

    return 1;
}

int test_calender_init_nonnull_date()
{
  date_t date = {3, APR, 2012};
  calender_t *calen = init_calender_ (&date);

  if (calen)
  {
	if (calen->cur_day_)
	{
	  if (calen->cur_day_->day_ == date.day_ &&
	  calen->cur_day_->month_ == date.month_ &&
	  calen->cur_day_->year_ == date.year_)
	  {
		return 0;
	  }
	}
  }
  return 1;
}

int test_add_1_calender_event()
{
  date_t event_date = {3, APR, 2012};
  time_struct event_time = {0, 0, 13};
  event_t event = {"Test event", "event for testing",
				   event_time, event_date};

  calender_t *calen = init_calender_ (NULL);
  add_calender_event_ (calen, &event);
  if (calen->calender_arr_[event_date.year_ - START_YEAR][event_date.month_]
  								[event_date.day_].head_ptr_)
  {
	event_t *event_ptr = calen->calender_arr_[event_date.year_ - START_YEAR]
		[event_date.month_][event_date.day_].head_ptr_;
	printf ("title: %s\n description: %s\n date: %d, %d, %d\n",
			event_ptr->title_, event_ptr->description_, event_ptr->date.day_,
			event_ptr->date.month_, event_ptr->date.year_);
	return 0;
  }
  return 1;
}

int test_add_2_events_different_dates()
{
  date_t event1_date = {3, APR, 2012};
  time_struct event1_time = {0, 0, 13};
  event_t event1 = {"Test event 1", "event for testing",
				   event1_time, event1_date};

  date_t event2_date = {2, APR, 2012};
  time_struct event2_time = {0, 0, 13};
  event_t event2 = {"Test event 2", "event for testing",
					event2_time, event2_date};

  calender_t *calen = init_calender_ (NULL);
  add_calender_event_ (calen, &event1);
  add_calender_event_ (calen, &event2);
  if (calen->calender_arr_[event1_date.year_ - START_YEAR][event1_date.month_]
  [event1_date.day_].head_ptr_ && calen->calender_arr_[event2_date.year_ -
  START_YEAR][event2_date.month_]
  [event2_date.day_].head_ptr_)
  {
	event_t *event_ptr = calen->calender_arr_[event1_date.year_ - START_YEAR]
	[event1_date.month_][event1_date.day_].head_ptr_;
	printf ("title: %s\n description: %s\n date: %d, %d, %d\n",
			event_ptr->title_, event_ptr->description_, event_ptr->date.day_,
			event_ptr->date.month_, event_ptr->date.year_);

	event_ptr = calen->calender_arr_[event2_date.year_ - START_YEAR]
	[event2_date.month_][event2_date.day_].head_ptr_;
	printf ("title: %s\n description: %s\n date: %d, %d, %d\n",
			event_ptr->title_, event_ptr->description_, event_ptr->date.day_,
			event_ptr->date.month_, event_ptr->date.year_);
	return 0;
  }
  return 1;
}

int test_add_2_events_same_date()
{
  date_t event1_date = {3, APR, 2012};
  time_struct event1_time = {0, 0, 13};
  event_t event1 = {"Test event 1", "event for testing",
					event1_time, event1_date};

  date_t event2_date = {3, APR, 2012};
  time_struct event2_time = {0, 0, 13};
  event_t event2 = {"Test event 2", "event for testing",
					event2_time, event2_date};

  calender_t *calen = init_calender_ (NULL);
  add_calender_event_ (calen, &event1);
  add_calender_event_ (calen, &event2);
  if (calen->calender_arr_[event1_date.year_ - START_YEAR][event1_date.month_]
	  [event1_date.day_].head_ptr_ && calen->calender_arr_[event2_date.year_ -
														   START_YEAR][event2_date.month_]
	  [event2_date.day_].head_ptr_)
  {
	event_t *event_ptr = &calen->calender_arr_[event1_date.year_ - START_YEAR]
	[event1_date.month_][event1_date.day_].head_ptr_[0];
	printf ("title: %s\n description: %s\n date: %d, %d, %d\n",
			event_ptr->title_, event_ptr->description_, event_ptr->date.day_,
			event_ptr->date.month_, event_ptr->date.year_);

	event_ptr = &calen->calender_arr_[event2_date.year_ - START_YEAR]
	[event2_date.month_][event2_date.day_].head_ptr_[1];
	printf ("title: %s\n description: %s\n date: %d, %d, %d\n",
			event_ptr->title_, event_ptr->description_, event_ptr->date.day_,
			event_ptr->date.month_, event_ptr->date.year_);
	return 0;
  }
  return 1;
}

int test_sort_events()
{
  date_t event1_date = {3, APR, 2012};
  time_struct event1_time = {0, 0, 13};
  event_t event1 = {"Test event 1", "event for testing",
					event1_time, event1_date};

  date_t event2_date = {3, APR, 2012};
  time_struct event2_time = {0, 0, 12};
  event_t event2 = {"Test event 2", "event for testing",
					event2_time, event2_date};

  calender_t *calen = init_calender_ (NULL);
  add_calender_event_ (calen, &event1);
  add_calender_event_ (calen, &event2);
  if (calen->calender_arr_[event1_date.year_ - START_YEAR][event1_date.month_]
	  [event1_date.day_].head_ptr_ && calen->calender_arr_[event2_date.year_ -
														   START_YEAR][event2_date.month_]
	  [event2_date.day_].head_ptr_)
  {
	event_t *event_ptr = &calen->calender_arr_[event1_date.year_ - START_YEAR]
	[event1_date.month_][event1_date.day_].head_ptr_[0];
	printf ("title: %s\n description: %s\n date: %d, %d, %d\n",
			event_ptr->title_, event_ptr->description_, event_ptr->date.day_,
			event_ptr->date.month_, event_ptr->date.year_);

	event_ptr = &calen->calender_arr_[event2_date.year_ - START_YEAR]
	[event2_date.month_][event2_date.day_].head_ptr_[1];
	printf ("title: %s\n description: %s\n date: %d, %d, %d\n",
			event_ptr->title_, event_ptr->description_, event_ptr->date.day_,
			event_ptr->date.month_, event_ptr->date.year_);
	return 0;
  }
  return 1;
}

int test_get_events()
{
  date_t event1_date = {3, APR, 2012};
  time_struct event1_time = {0, 0, 13};
  event_t event1 = {"Test event 1", "event for testing",
					event1_time, event1_date};

  date_t event2_date = {3, APR, 2012};
  time_struct event2_time = {0, 0, 12};
  event_t event2 = {"Test event 2", "event for testing",
					event2_time, event2_date};

  calender_t *calen = init_calender_ (NULL);
  add_calender_event_ (calen, &event1);
  add_calender_event_ (calen, &event2);
  event_list *ret_list = get_events_ (calen, event1_date);
  if (!ret_list)
  {
	return 1;
  }
  for (int i = 0; i < ret_list->size; ++i)
  {
	printf("title: %s\n", ret_list->head_ptr_[i].title_);
  }
  return 0;
}

int test_print()
{
  date_t event1_date = {3, APR, 2012};
  time_struct event1_time = {0, 0, 13};
  event_t event1 = {"Test event 1", "event for testing",
					event1_time, event1_date};

  date_t event2_date = {3, APR, 2012};
  time_struct event2_time = {0, 0, 12};
  event_t event2 = {"Test event 2", "event for testing",
					event2_time, event2_date};

  calender_t *calen = init_calender_ (NULL);
  add_calender_event_ (calen, &event1);
  add_calender_event_ (calen, &event2);
  print_calender_(calen);
  return 0;
}