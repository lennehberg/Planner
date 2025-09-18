#ifndef PCALENDAR_H
#define PCALENDAR_H

#include "utils.h"

void get_month_time_t(time_t *month_start_t, time_t *month_end_t, int month, int year);

int get_month_len_days(int month, int year);

#endif // PCALENDAR_H
