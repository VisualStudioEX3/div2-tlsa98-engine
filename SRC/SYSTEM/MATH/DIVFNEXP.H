//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Math service functions exported to DIV language.
*/

#ifndef __SYSTEM_MATH_DLL_DIV_FUNCTION_EXPORT_
#define __SYSTEM_MATH_DLL_DIV_FUNCTION_EXPORT_

#include "MATH.H"

/// @brief Exports math service functions to DIV language. 
void exportMathService(LIBRARY_PARAMS);

/// @brief Gets the min value bewteen 2 values.
/// @param a First value.
/// @param b Second value.
/// @return Returns the min value.
void min();
#define DIV_MATH_FUNC_MIN_NAME              "min"
#define DIV_MATH_FUNC_MIN_PARAMS            2

/// @brief Gets the max value bewteen 2 values.
/// @param a First value.
/// @param b Second value.
/// @return Returns the max value.
void max();
#define DIV_MATH_FUNC_MAX_NAME              "max"
#define DIV_MATH_FUNC_MAX_PARAMS            2

/// @brief Gets the clamped value in a range.
/// @param v Value to clamp.
/// @param a Min value of the range.
/// @param b Max value of the range.
/// @return Returns the clamped value.
void clamp();
#define DIV_MATH_FUNC_CLAMP_NAME            "clamp"
#define DIV_MATH_FUNC_CLAMP_PARAMS          3

/// @brief Gets if a value is clamped into a range.
/// @param v Value to check.
/// @param a Min value of the range.
/// @param b Max value of the range.
/// @return Returns #SYSTEM::true if the value is clamped, #SYSTEM::false otherwise.
void isClamped();
#define DIV_MATH_FUNC_IS_CLAMPED_NAME       "is_clamped"
#define DIV_MATH_FUNC_IS_CLAMPED_PARAMS     3

/// @brief Interpolate linearly a value between two values.
/// @param a Min value.
/// @param b Max value.
/// @param t The interpolation value between two integer values.
/// @return Returns the interpolated integer result between the two values.
void lerp();
#define DIV_MATH_FUNC_LERP_NAME             "lerp"
#define DIV_MATH_FUNC_LERP_PARAMS           3

#endif