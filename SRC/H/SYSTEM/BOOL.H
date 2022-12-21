//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Boolean alias and constants.
*/

#ifndef __SYSTEM_BOOL_
#define __SYSTEM_BOOL_

/// @brief True constant value.
/// @remarks In DIV Games Studio, all odd values are considered as true value.
#define true            1

/// @brief False constant value.
/// @remarks In DIV Games Studio, all even values are considered as false value.
#define false           0

/// @brief Boolean alias.
/// @remarks In DIV Games Studio, like in C, a boolean value is an integer value.
typedef int bool;

#endif