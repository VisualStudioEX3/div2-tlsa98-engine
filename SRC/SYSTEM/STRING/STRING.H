//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    String functions.
*/

#ifndef __SYSTEM_STRING_H_
#define __SYSTEM_STRING_H_

#include "..\..\H\GLOBAL.H"

/// @brief Allocates memory for a new string.
/// @param chars Number of chars. Not counting the null terminated char.
/// @return Returns a pointer to the new string created, filled with null chars, 
/// #DIV::NULL otherwise.
string stringAlloc(int chars);

/// @brief Gets the length of the string.
/// @param str String to measure.
/// @return Returns the number of characters until reach the first #DIV::NULL character.
int stringLength(const string str);

/// @brief Determines whether all characters of a string are equal to character model.
/// @param str String to check.
/// @param chr Character to compare.
/// @return Returns #SYSTEM::true if all characters are the character model,#SYSTEM::false
/// otherwise.
bool stringAll(const string str, const char chr);

/// @brief Determines whether any character of a string are equal to any character of the
/// string model.
/// @param str String to check.
/// @param chars String with characters to compare.
/// @return Returns #SYSTEM::true if any character is present in the string, 
/// #SYSTEM::false otherwise.
bool stringAny(const string str, const string chars);

/// @brief Determines if the string is null or empty.
/// @param str String to check.
/// @return Returns #SYSTEM::true if the string is #DIV::NULL, 0 length string or a string
/// full with #DIV::NULL characters.
bool stringIsEmpty(const string str);

/// @brief Determines if left string is equals to the right string.
/// @param lhs Left string to compare.
/// @param rhs Right string to compare.
/// @return Returns #SYSTEM::true if the left string is equal to right string.
/// @remarks The comparison method is case sensitive.
bool stringEquals(const string lhs, const string rhs);

/// @brief Creates a copy of the string.
/// @param str String to copy.
/// @return Returns the copied string.
string stringCopy(const string str);

/// @brief Convert all characters to lower case.
/// @param str String to convert.
/// @return Returns pointer to the converted string.
string stringToLowerCase(const string str);

/// @brief Convert all characters to upper case.
/// @param str String to convert.
/// @return Returns pointer to the converted string.
string stringToUpperCase(const string str);

/// @brief Formats a string using a list of values.
/// @param str Pointer to string where store the output formatted result.
/// @param format Format string model. To see how to format the output see: https://cplusplus.com/reference/cstdio/printf/.
/// @param ... List of arguments to use in formatted string.
/// @returns Returns #SYSTEM::true if string is sucessful formatted, #SYSTEM::false otherwise.
bool stringFormat(string str, const string format, ...);

#endif