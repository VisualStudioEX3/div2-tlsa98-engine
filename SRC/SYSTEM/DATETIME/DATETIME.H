//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Date and time functions.
*/

#ifndef __SYSTEM_DATETIME_
#define __SYSTEM_DATETIME_

#include "../../H/GLOBAL.H"

/// @brief Retrieves the number of milliseconds that have elapsed since the system was started.
/// @return Returns the number of milliseconds that have elapsed since the system was started.
ulong getTickCount();

/// @brief Get current date and time.
/// @param dateTime Pointer to variable to store the date and time values.
void getDateTime(datetime_t* dateTime);

/// @brief Get current date and time.
/// @return Returns the current system date and time.
/// @remarks This function creates a new #GLOBAL::datetime_t pointer to return the value.
datetime_t* getDateTimeAlloc();

#endif