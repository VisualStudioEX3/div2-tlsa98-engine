//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Math service.
*/

#ifndef __SYSTEM_MATH_SERVICE
#define __SYSTEM_MATH_SERVICE

#include "SYSTEM.H"

/// @brief Math service id.
#define MATH_SERVICE    1000

/// @brief WORD type in DIV Games Studio 2.
typedef unsigned short word;

/// @brief Unsigned integer alias.
typedef unsigned int uint;

typedef int     (*math_min_f)           (int a, int b);
typedef int     (*math_max_f)           (int a, int b);
typedef int     (*math_clamp_f)         (int v, int a, int b);
typedef bool    (*math_is_clamped_f)    (int v, int a, int b);
typedef int     (*math_lerp_f)          (int a, int b, int t);

/// @brief Math service interface.
typedef struct math_service_t
{
    /// @brief Gets the min value bewteen 2 values.
    /// @param a First value.
    /// @param b Second value.
    /// @return Returns the min value.
    math_min_f min;

    /// @brief Gets the max value bewteen 2 values.
    /// @param a First value.
    /// @param b Second value.
    /// @return Returns the max value.
    math_max_f max;

    /// @brief Gets the clamped value in a range.
    /// @param v Value to clamp.
    /// @param a Min value of the range.
    /// @param b Max value of the range.
    /// @return Returns the clamped value.
    math_clamp_f clamp;

    /// @brief Gets if a value is clamped into a range.
    /// @param v Value to check.
    /// @param a Min value of the range.
    /// @param b Max value of the range.
    /// @return Returns #SYSTEM::true if the value is clamped, #SYSTEM::false otherwise.
    math_is_clamped_f isClamped;

    /// @brief Interpolate linearly a value between two values.
    /// @param a Min value.
    /// @param b Max value.
    /// @param t The interpolation value between two integer values.
    /// @return Returns the interpolated integer result between the two values.
    math_lerp_f lerp;
} math_service_t;

/// @brief Register and initializes service.
void registerMathService();

/// @brief Exports service functions to DIV language.
/// @param service Pointer to the DIV Games Studio function exporter service.
void exportMathService(div_function_exporter_service_t* service);

#endif