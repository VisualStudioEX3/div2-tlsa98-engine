//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    String service.
*/

#ifndef __SYSTEM_STRING_SERVICE
#define __SYSTEM_STRING_SERVICE

#include "BOOL.H"

/// @brief String service id.
#define STRING_SERVICE    1010

/// @brief STRING type in DIV Games Studio 2.
/// @remarks An alias for char pointer type.
typedef char* string;

typedef string  (*string_stralloc_f)    (int chars);
typedef int     (*string_len_f)         (const string str);
typedef bool    (*string_all_f)         (const string str, const char chr);
typedef bool    (*string_any_f)         (const string str, const string chars);
typedef bool    (*string_empty_f)       (const string str);
typedef bool    (*string_equals_f)      (const string lhs, const string rhs);
typedef string  (*string_copy_f)        (const string str);
typedef string  (*string_to_lower_f)    (const string str);
typedef string  (*string_to_upper_f)    (const string str);

/// @brief String service interface.
typedef struct string_service_t
{
    /// @brief Allocates memory for a new string.
    /// @param chars Number of chars. Not counting the null terminated char.
    /// @return Returns a pointer to the new string created, filled with null chars, 
    /// #DIV::NULL otherwise.
    string_stralloc_f strAlloc;

    /// @brief Gets the length of the string.
    /// @param str String to measure.
    /// @return Returns the number of characters until reach the first #DIV::NULL character.
    string_len_f len;

    /// @brief Determines whether all characters of a string are equal to character model.
    /// @param str String to check.
    /// @param chr Character to compare.
    /// @return Returns #SYSTEM::true if all characters are the character model,#SYSTEM::false
    /// otherwise.
    string_all_f all;

    /// @brief Determines whether any character of a string are equal to any character of the
    /// string model.
    /// @param str String to check.
    /// @param chars String with characters to compare.
    /// @return Returns #SYSTEM::true if any character is present in the string, 
    /// #SYSTEM::false otherwise.
    string_any_f any;

    /// @brief Determines if the string is null or empty.
    /// @param str String to check.
    /// @return Returns #SYSTEM::true if the string is #DIV::NULL, 0 length string or a string
    /// full with #DIV::NULL characters.
    string_empty_f isEmpty;

    /// @brief Determines if left string is equals to the right string.
    /// @param lhs Left string to compare.
    /// @param rhs Right string to compare.
    /// @return Returns #SYSTEM::true if the left string is equal to right string.
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
} string_service_t;

/// @brief Register and initializes service service.
void registerStringService();

#endif