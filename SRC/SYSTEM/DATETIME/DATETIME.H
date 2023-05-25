//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Date and time functions.
*/

#ifndef __SYSTEM_DATETIME_H_
#define __SYSTEM_DATETIME_H_

#include "..\..\H\SYSTEM\GLOBALS.H"

/// @brief Retrieves the number of milliseconds that have elapsed since the system was started.
/// @return Returns the number of milliseconds that have elapsed since the system was started.
ulong getTickCount();

/// @brief Get current date and time.
/// @return Returns the current system date and time.
datetime_t* getDateTime();

/// @brief Get current date and time.
/// @param dateTime Pointer to variable to store the date and time values.
void getDateTimeNotAlloc(datetime_t* dateTime);

/// @brief Converts date time value to string representation.
/// @param dateTime Pointer to date time value to converts.
/// @return Returns the string rerpresentation of the date time value.
string dateTimeToString(const datetime_t* dateTime);

#endif