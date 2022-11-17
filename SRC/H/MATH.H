//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Math service.
*/

#ifndef __SYSTEM_MATH_DLL_
#define __SYSTEM_MATH_DLL_

#include "SYSTEM.H"

/// @brief Math service id.
#define MATH_SERVICE    1000

typedef int     (*math_min_function)        (int, int);
typedef int     (*math_max_function)        (int, int);
typedef int     (*math_clamp_function)      (int, int, int);
typedef bool    (*math_is_clamped_function) (int, int, int);
typedef int     (*math_lerp_function)       (int, int, int);

/// @brief Math service interface.
typedef struct math_service_t
{
    /// @brief Gets the min value bewteen 2 values.
    /// @param a First value.
    /// @param b Second value.
    /// @return Returns the min value.
    math_min_function min;

    /// @brief Gets the max value bewteen 2 values.
    /// @param a First value.
    /// @param b Second value.
    /// @return Returns the max value.
    math_max_function max;

    /// @brief Gets the clamped value in a range.
    /// @param v Value to clamp.
    /// @param a Min value of the range.
    /// @param b Max value of the range.
    /// @return Returns the clamped value.
    math_clamp_function clamp;

    /// @brief Gets if a value is clamped into a range.
    /// @param v Value to check.
    /// @param a Min value of the range.
    /// @param b Max value of the range.
    /// @return Returns #SYSTEM::true if the value is clamped, #SYSTEM::false otherwise.
    math_is_clamped_function isClamped;

    /// @brief Interpolate linearly a value between two values.
    /// @param a Min value.
    /// @param b Max value.
    /// @param t The interpolation value between two integer values.
    /// @return Returns the interpolated integer result between the two values.
    math_lerp_function lerp;
} math_service_t;

/// @brief Register and initializes math service.
void registerMathService();

#endif