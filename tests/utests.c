#include "../src/calender.c"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int test_calender_init_null_date();
int main()
{
    assert (test_calender_init_null_date() == 0);
    printf("Null date init passed Successfully!\n");
}

int test_calender_init_null_date()
{
    calender_t *calen = init_calender_(NULL);

    if (calen)
    {
        if (calen->calender_arr_ || calen->cur_day_)
        {
            if (calen->cur_day_->day_ == 0 && calen->cur_day_->month_ == 0 && calen->cur_day_->year_ == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}