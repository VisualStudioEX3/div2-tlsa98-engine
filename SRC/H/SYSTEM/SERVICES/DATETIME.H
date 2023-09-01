//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    DateTime service.
*/

#ifndef __SYSTEM_DATETIME_H_
#define __SYSTEM_DATETIME_H_

#include "..\GLOBALS.H"

/// @brief DateTime service id.
#define DATETIME_SERVICE 1002

typedef ulong (*datetime_getTickCount_f)();
typedef datetime_t *(*datetime_getDateTime_f)();
typedef void (*datetime_getDateTimeNotAlloc_f)(datetime_t *);
typedef string (*datetime_dateTimeToString_f)(const datetime_t*);

/// @brief DateTime service interface.
typedef struct
{
    /// @brief Retrieves the number of milliseconds that have elapsed since the system was started.
    /// @return Returns the number of milliseconds that have elapsed since the system was started.
    datetime_getTickCount_f getTickCount;

    /// @brief Get current date and time.
    /// @return Returns the current system date and time.
    datetime_getDateTime_f getDateTime;

    /// @brief Get current date and time.
    /// @param dateTime Pointer to variable to store the date and time values.
    datetime_getDateTimeNotAlloc_f getDateTimeNotAlloc;

    /// @brief Converts date time value to string representation.
    /// @param dateTime Pointer to date time value to converts.
    /// @return Returns the string rerpresentation of the date time value.
    datetime_dateTimeToString_f dateTimeToString;
} datetime_service_t;

/// @brief Register and initializes the service.
void registerDateTimeService();

#endif