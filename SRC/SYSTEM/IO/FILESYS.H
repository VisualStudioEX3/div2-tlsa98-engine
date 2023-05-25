//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    System file system functions.
*/

#ifndef __SYSTEM_FILE_SYSTEM_H_
#define __SYSTEM_FILE_SYSTEM_H_

#include "..\..\H\SYSTEM\GLOBALS.H"

/// @brief Gets current directory.
/// @return Returns a pointer to a new string that contains the current working path.
string getCurrentDirectory();

/// @brief Creates a new directory.
/// @param path Path for the new directory to creates.
/// @returns Returns #SYSTEM::true if the directory is created, #SYSTEM::false otherwise.
bool createDirectory(string path);

/// @brief Changes the current working directory.
/// @param path Path for the directory.
/// @returns Returns #SYSTEM::true if the path is valid, #SYSTEM::false otherwise.
bool changeDirectory(string path);

/// @brief Determines whether the given path refers to an existing directory on disk.
/// @param path Path to test.
/// @return Returns #SYSTEM::true if the directory exists, #SYSTEM::false otherwise.
bool directoryExists(const string path);

/// @brief Combines strings into a path.
/// @param count Number of elements of the argument list.
/// @param ... Argument list that contains the strings to concatenate.
/// @return Returns a new string with the combined paths, #DIV::NULL otherwise.
string combinePath(int count, ...);

/// @brief Combines strings into a path (Variadic version).
/// @param count Number of elements of the argument list.
/// @param args Argument list that contains the strings to concatenate.
/// @return Returns a new string with the combined paths, #DIV::NULL otherwise.
string combinePathArgs(int count, va_list args);

/// @brief Opens or created a file.
/// @param filename Filename and path of the file to open or created.
/// @param mode Mode to open or create the file.
/// @returns Returns the file handle or #DIV::NULL otherwise.
/// @remarks This functions always must use the built-in DIV.H #DIV::div_fopen() function in 
/// order to work properly with DIV Games Studio 2 runtime.
/// See the standard stdio.h fopen() C function documentation for more details.
FILE* openFile(string filename, string mode);

/// @brief Closes an opened file.
/// @param file File handle to close.
/// @remarks This functions always must use the built-in DIV.H #DIV::div_fclose() function in 
/// order to work properly with DIV Games Studio 2 runtime.
/// See the standard stdio.h fclose() C function documentation for more details.
void closeFile(FILE* file);

/// @brief Writes a string value to file.
/// @param file Pointer to a opened file.
/// @param str String value to write.
/// @param ... Optional list of arguments to format in the string. To see how to format the 
/// output see: https://cplusplus.com/reference/cstdio/printf/.
/// @returns Returns #SYSTEM::true if the string is sucessfully writen in the file, 
/// #SYSTEM::false otherwise.
bool writeStringToFile(FILE* file, string str, ...);

/// @brief Writes a string value to file (Variadic version).
/// @param file Pointer to a opened file.
/// @param str String value to write.
/// @param args List of arguments to format in the string. To see how to format the output 
/// see: https://cplusplus.com/reference/cstdio/printf/.
/// @returns Returns #SYSTEM::true if the string is sucessfully writen in the file, 
/// #SYSTEM::false otherwise.
bool writeStringToFileArgs(FILE* file, string str, va_list args);

#endif