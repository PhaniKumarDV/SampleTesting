#include <schedule.h>

ScheduleDayMaskEntry dayMask[SCHEDULE_DAY_MASK_SIZE] = {
    {0x1000000, "Mon"},
    {0x0100000, "Tue"},
    {0x0010000, "Wed"},
    {0x0001000, "Thu"},
    {0x0000100, "Fri"},
    {0x0000010, "Sat"},
    {0x0000001, "Sun"}
};
