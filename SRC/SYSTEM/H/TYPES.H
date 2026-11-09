//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Engine types and aliases.
*/

#ifndef __SYSTEM_DLL_TYPES_H_
#define __SYSTEM_DLL_TYPES_H_

/**
 * @brief Boolean alias.
 * @remarks In DIV Games Studio, like in C, a boolean value is an integer
 * value.
 */
typedef int bool;

/**
 * @brief True constant value.
 * @remarks In DIV Games Studio, all odd values are considered as true value.
 */
#define true 1

/**
 * @brief False constant value.
 * @remarks In DIV Games Studio, all even values are considered as false value.
 */
#define false 0

/**
 * @brief BYTE type in DIV Games Studio.
 * @remarks You can use this alias instead of normal char (-127 to 127) to
 * manage memory stream data, ensuring that all values are valid byte values (0
 * to 255).
 */
typedef unsigned char byte;

/// @brief WORD type in DIV Games Studio.
typedef unsigned short word;

/// @brief Unsigned integer alias.
typedef unsigned int uint;

/// @brief Unsigned long alias.
typedef unsigned long ulong;

/**
 * @brief STRING type in DIV Games Studio 2.
 * @remarks An alias for char pointer type. All DIV parameters, even the string
 * values, are received as integer values as a position in DIV managed memory
 * of the parameter is stored.
 */
typedef char *string;

/**
 * @brief Version value.
 * @remarks This struct is shaped as 4 byte values, 3 for the version value, 1
 * reserved to complete the 4 bytes. This is intended to be convertible as
 * integer value.
 */
typedef struct
{
    /**
     * @brief Major version. Represents major changes on API.
     * @remarks This number must be updated when the API implements a major
     * changes, like a new main service or third party libraries, or even a
     * broken compatibility with previous versions. When a major version is
     * updated, minor version an revision number must be set to zero.
     */
    byte major;

    /**
     * @brief Minor version. Represents a feature changes on the current major
     * version of the API.
     * @remarks This number must be updated when, in the current major version,
     * the API upgrade an existing service, add a new services as dependency of
     * main ones (a service that not should be a main service) and minor
     * changes that not broken compatibility with previous versions. When a
     * minor version is updated, revision number must be set to zero.
     */
    byte minor;

    /**
     * @brief Revision number. Represents a patch or bugfix applied on current
     * minor version of the API.
     * @remarks This number must be updated only when, on a current minor
     * version, it required apply a bugfix or patch to solve problems whitout
     * require make changes on API or current behaviours. If the fix implies
     * implement new features, new top services or change any current expected
     * behaviour, this should be considered as new minor version. If the fix
     * implies remove or create new feature that broken the API compatibility,
     * must be considered as new major version.
     */
    byte revision;

    /// @brief Value reserved for future purposes.
    byte reserved;
} version_t;

#endif
