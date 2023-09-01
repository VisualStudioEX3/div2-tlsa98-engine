//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    DateTime service.
*/

#include <assert.h>
#include <time.h>
#include "..\..\H\SYSTEM\SERVICES\DATETIME.H"
#include "..\..\H\SYSTEM\SERVICES\MEM.H"

const int CLOCKS_PER_MILLISECONDS = CLOCKS_PER_SEC / 1000;

datetime_service_t service;

static mem_service_t *memoryService;

static void tm_to_datetime_t(const tm *src, datetime_t *dest)
{
    dest->seconds = src->tm_sec;
    dest->minutes = src->tm_min;
    dest->hour = src->tm_hour;
    dest->day = src->tm_mday;
    dest->month = src->tm_mon + 1;    // Fix month value.
    dest->year = src->tm_year + 1900; // Fix year value.
}

static time_t datetime_t_to_tm(const datetime_t *src, tm *dest)
{
    memoryService->clear(dest, sizeof(tm));

    dest->tm_sec = src->seconds;
    dest->tm_min = src->minutes;
    dest->tm_hour = src->hour;
    dest->tm_mday = src->day;
    dest->tm_mon = src->month - 1;
    dest->tm_year = src->year - 1900;

    dest->tm_isdst = -1; // Unknown daylight savings time.

    return mktime(dest); // Resolve tm_wday and tm_yday values on dest argument, and returns the time_t value.
}

static ulong getTickCount()
{
    return clock() * CLOCKS_PER_MILLISECONDS;
}

static void getDateTimeNotAlloc(datetime_t *dateTime)
{
    time_t now;
    struct tm *dt;

    time(&now);
    dt = localtime(&now);
    tm_to_datetime_t(dt, dateTime);
}

static datetime_t *getDateTime()
{
    datetime_t *dateTime = (datetime_t *)malloc(sizeof(datetime_t));

    getDateTimeNotAlloc(dateTime);

    return dateTime;
}

static string dateTimeToString(const datetime_t *dateTime)
{
    struct tm dt;
    time_t t = datetime_t_to_tm(dateTime, &dt);

    return ctime(&t);
}

void registerDateTimeService()
{
    engine->fileLogger->log("Initializing DateTime service...");

    memoryService = (mem_service_t *)getService(MEM_SERVICE);

    service.getTickCount = getTickCount;
    service.getDateTime = getDateTime;
    service.getDateTimeNotAlloc = getDateTimeNotAlloc;
    service.dateTimeToString = dateTimeToString;

    int result = engine->services->registerService(DATETIME_SERVICE, &service);

    assert(result == RESULT_OK);

    engine->fileLogger->log("DateTime service initialized.");
}