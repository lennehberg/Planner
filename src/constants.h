#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// calculate amount of days in month
#define START_YEAR 1977
#define DAYS_IN_MONTH(month, year) (month == FAB ? ((year % 4) == 0 ? 28 : 29) : ((month + 1) % 2) == 0 ? 30 : 31)
#define NUM_MONTHS 12
#define NUM_YEARS 50


// declarations of types used for managing time/date/events

typedef int second_t;
typedef int minute_t;
typedef int hour_t;
typedef int year_t;

typedef enum DAY{
    SUN = 0,
    MON = 1,
    TUE = 2,
    WED = 3,
    THU = 4,
    FRI = 5,
    SAT = 6
}DAY;

typedef enum MONTH{
    JAN = 0,
    FAB = 1,
    MAR = 2,
    APR = 3,
    MAY = 4,
    JUN = 5,
    JUL = 6,
    AUG = 7,
    SEP = 8,
    OCT = 9,
    NOV = 10,
    DEC = 11
} MONTH;

typedef struct time_t{
    second_t sec_;
    minute_t min_;
    hour_t hour_;
}time_t;

typedef struct date_t
{
    DAY day_;
    MONTH month_;
    year_t year_;
}date_t;


typedef struct event_t{
    const char *title_, *description_;
    time_t time_t;
    date_t date;
}event_t;

#endif // CONSTANTS_H_