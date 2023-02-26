//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    System file system functions.
*/

#include <direct.h> // DOS filesystem functions.
#include "FILESYS.H"

bool createDirectory(string path)
{
    return mkdir(path) == 0;
}

bool changeDirectory(string path)
{
    return chdir(path) == 0;
}

FILE* openFile(string filename, string mode)
{
    return div_fopen(filename, mode);
}

void closeFile(FILE* file)
{
    // TODO: Asserts NULL file handle.
    div_fclose(file);
}