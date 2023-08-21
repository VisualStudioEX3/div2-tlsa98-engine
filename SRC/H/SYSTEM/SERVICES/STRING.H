//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    String service.
*/

#ifndef __SYSTEM_DLL_SERVICE_SERVICE_H_
#define __SYSTEM_DLL_SERVICE_SERVICE_H_

#include "..\GLOBALS.H"

/// @brief String service id.
#define STRING_SERVICE 1001

typedef string (*string_create_f)(int chars);
typedef string (*string_resize_f)(string str, int chars);
typedef void (*string_clear_f)(string str);
typedef int (*string_len_f)(const string str);
typedef bool (*string_all_f)(const string str, const char chr);
typedef bool (*string_any_f)(const string str, const string chars);
typedef bool (*string_empty_f)(const string str);
typedef bool (*string_equals_f)(const string lhs, const string rhs);
typedef string (*string_copy_f)(const string str);
typedef string (*string_to_lower_f)(const string str);
typedef string (*string_to_upper_f)(const string str);
typedef bool (*string_format_f)(string, const string, ...);
typedef bool (*string_format_args_f)(string, const string, va_list);
typedef string (*string_join_f)(const string separator, int count, ...);
typedef string (*string_join_args_f)(const string separator, int count, va_list);

/// @brief String service interface.
typedef struct
{
    /// @brief Creates a new string.
    /// @param chars Number of chars. Not counting the null terminated char.
    /// @return Returns a pointer to the new string created, filled with null chars,
    /// #NULL otherwise.
    string_create_f create;

    /// @brief Resizes a string.
    /// @param str Pointer to a string to resize.
    /// @param chars Number of chars. Not counting the null terminated char.
    /// @return Returns a pointer to the resized string, #NULL otherwise.
    /// If the size is major than original string size, the new chars are filled with null
    /// chars.
    string_resize_f resize;

    /// @brief Puts all characters of the string to null char.
    /// @param str String to clear.
    string_clear_f clear;

    /// @brief Gets the length of the string.
    /// @param str String to measure.
    /// @return Returns the number of characters until reach the first null character.
    string_len_f len;

    /// @brief Determines whether all characters of a string are equal to character model.
    /// @param str String to check.
    /// @param chr Character to compare.
    /// @return Returns #true if all characters are the character model, #false otherwise.
    string_all_f all;

    /// @brief Determines whether any character of a string are equal to any character of the
    /// string model.
    /// @param str String to check.
    /// @param chars String with characters to compare.
    /// @return Returns #true if any character is present in the string, #false otherwise.
    string_any_f any;

    /// @brief Determines if the string is null or empty.
    /// @param str String to check.
    /// @return Returns #true if the string is #NULL, 0 length string or a string full with 
    /// null characters.
    string_empty_f isEmpty;

    /// @brief Determines if left string is equals to the right string.
    /// @param lhs Left string to compare.
    /// @param rhs Right string to compare.
    /// @return Returns #true if the left string is equal to right string.
    /// @remarks The comparison method is case sensitive.
    string_equals_f equals;

    /// @brief Creates a copy of the string.
    /// @param str String to copy.
    /// @return Returns the copied string.
    string_copy_f copy;

    /// @brief Convert all characters to lower case.
    /// @param str String to convert.
    /// @return Returns pointer to the converted string.
    string_to_lower_f toLower;

    /// @brief Convert all characters to upper case.
    /// @param str String to convert.
    /// @return Returns pointer to the converted string.
    string_to_upper_f toUpper;

    /// @brief Formats a string using a list of values.
    /// @param str Pointer to string where store the output formatted restult.
    /// @param format Format string model. To see how to format the output see:
    /// https://cplusplus.com/reference/cstdio/printf/.
    /// @param ... List of arguments to use in formatted string.
    /// @returns Returns #true if string is sucessful formatted, #false otherwise.
    string_format_f format;

    /// @brief Formats a string using a list of values (Variadic version).
    /// @param str Pointer to string where store the output formatted restult.
    /// @param format Format string model. To see how to format the output see:
    /// https://cplusplus.com/reference/cstdio/printf/.
    /// @param args List of arguments to use in formatted string.
    /// @returns Returns #true if string is sucessful formatted, #false otherwise.
    string_format_args_f vformat;

    /// @brief Concatenates the elements of the argument list using the specified separator.
    /// @param separator The string to use as a separator. Separator is included in the
    /// returned string only if values has more than one element.
    /// @param count Number of elements of the argument list.
    /// @param ... Argument list that contains the strings to concatenate.
    /// @return Returns a new string that consists of the elements of the argument list
    /// delimited by the separator string.
    string_join_f join;

    /// @brief Concatenates the elements of the argument list using the specified separator
    /// (Variadic version).
    /// @param separator The string to use as a separator. Separator is included in the
    /// returned string only if values has more than one element.
    /// @param count Number of elements of the argument list.
    /// @param args Argument list that contains the strings to concatenate.
    /// @return Returns a new string that consists of the elements of the argument list
    /// delimited by the separator string.
    string_join_args_f vjoin;
} string_service_t;

/// @brief Register and initializes the service.
void registerStringService();

#endif