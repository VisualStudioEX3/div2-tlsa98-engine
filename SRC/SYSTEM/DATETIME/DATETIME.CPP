//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Date and time functions.
*/

#include <time.h>
#include "DATETIME.H"

const int CLOCKS_PER_MILLISECONDS = CLOCKS_PER_SEC / 1000;

tm* dt;
time_t now;

ulong getTickCount()
{
    return clock() * CLOCKS_PER_MILLISECONDS;
}

void getDateTime(datetime_t* dateTime)
{
    time(&now);
    dt = localtime(&now);
    dt->tm_mon++;           // Fix month value.
    dt->tm_year += 1900;    // Fix year value.

    dateTime->seconds   = dt->tm_sec;
    dateTime->minutes   = dt->tm_min;
    dateTime->hour      = dt->tm_hour;
    dateTime->day       = dt->tm_mday;
    dateTime->month     = dt->tm_mon;
    dateTime->year      = dt->tm_year;
}

datetime_t* getDateTimeAlloc()
{
    datetime_t* dateTime = (datetime_t*)malloc(sizeof(datetime_t));

    getDateTime(dateTime);

    return dateTime;
}