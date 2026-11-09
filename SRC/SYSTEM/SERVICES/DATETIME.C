//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    DateTime service.
*/

#include <time.h>
#include "../H/SERVICES/DATETIME.H"
#include "../H/SERVICES/LOGGER.H"
#include "../H/SERVICES/MEM.H"

#define CLOCKS_PER_MILLISECONDS CLOCKS_PER_SEC / 1000

typedef struct
{
    int seconds;
    int minutes;
    int hour;
    int day;
    int month;
    int year;
} _datetime_t;

typedef struct
{
    datetime_get_tick_count_f getTickCount;
    datetime_get_datetime_f getDateTime;
    datetime_get_datetime_not_alloc_f getDateTimeNotAlloc;
    datetime_datetime_to_string_f dateTimeToString;
} _datetime_service_t;

static const mem_service_t *memoryService;
static const logger_service_t *logger;

static _datetime_service_t service;

static void tm_to_datetime_t(const struct tm *src, _datetime_t *dest)
{
    dest->seconds = src->tm_sec;
    dest->minutes = src->tm_min;
    dest->hour = src->tm_hour;
    dest->day = src->tm_mday;
    dest->month = src->tm_mon + 1;    // Fix month value.
    dest->year = src->tm_year + 1900; // Fix year value.
}

static time_t datetime_t_to_tm(const _datetime_t *src, struct tm *dest)
{
    memoryService->clear(dest, sizeof(struct tm));

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
    const time_t currentTime = time(NULL);
    const struct tm *currentDateTime = localtime(&currentTime);

    tm_to_datetime_t(currentDateTime, (_datetime_t *)dateTime);
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
    time_t t = datetime_t_to_tm((_datetime_t *)dateTime, &dt);

    return ctime(&t);
}

void registerDateTimeService()
{
    logger = (logger_service_t *)getService(LOGGER_SERVICE);
    memoryService = (mem_service_t *)getService(MEM_SERVICE);

    logger->debug("Initializing DateTime service...");

    service.getTickCount = getTickCount;
    service.getDateTime = getDateTime;
    service.getDateTimeNotAlloc = getDateTimeNotAlloc;
    service.dateTimeToString = dateTimeToString;

    assert(addService(DATETIME_SERVICE, &service));

    logger->debug("DateTime service initialized.");
}
