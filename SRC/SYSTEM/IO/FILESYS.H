//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    System file system functions.
*/

#ifndef __SYSTEM_FILE_SYSTEM_
#define __SYSTEM_FILE_SYSTEM_

#include "..\..\H\GLOBAL.H"

/// @brief Creates a new directory.
/// @param path Path for the new directory to creates.
/// @returns Returns #SYSTEM::true if the directory is created, #SYSTEM::false otherwise.
bool createDirectory(string path);

/// @brief Changes the current working directory.
/// @param path Path for the directory.
/// @returns Returns #SYSTEM::true if the path is valid, #SYSTEM::false otherwise.
bool changeDirectory(string path);

/// @brief Opens or created a file.
/// @param filename Filename and path of the file to open or created.
/// @param mode Mode to open or create the file.
/// @returns Returns the file handle or #DIV::NULL otherwise.
/// @remarks This functions always must use the built-in DIV.H div_fopen() function in 
/// order to work properly with DIV Games Studio 2 runtime.
/// See the standard stdio.h fopen() C function documentation for more details.
FILE* openFile(string filename, string mode);

/// @brief Close an opened file.
/// @param file File handle to close.
/// @remarks This functions always must use the built-in DIV.H div_fclose() function in 
/// order to work properly with DIV Games Studio 2 runtime.
/// See the standard stdio.h fclose() C function documentation for more details.
void closeFile(FILE* file);

#endif