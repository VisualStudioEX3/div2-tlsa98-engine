//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Global members.
*/

#ifndef __SYSTEM_GLOBAL_
#define __SYSTEM_GLOBAL_

/// @brief Default function success result.
#define RESULT_OK       0

/// @brief Default function error result.
#define RESULT_ERROR    -1

/// @brief Gets the size of an array.
/// @param a Array to measure.
/// @return Returns the array size.
#define arraylen(a)     sizeof(a) / sizeof(a[0])

#endif