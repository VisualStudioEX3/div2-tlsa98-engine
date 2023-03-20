//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    System file system functions.
*/

#include <direct.h> // DOS filesystem functions.
#include <sys/stat.h>
#include "FILESYS.H"

const int DOS_MAX_FILENAME = 12;    // Max length for a filename in MS-DOS (8:3 format).
const int DOS_MAX_PATH = 80;        // Max length for a path in MS-DOS.

string getCurrentDirectory()
{
    return getcwd(NULL, DOS_MAX_PATH); // NULL buffer autoallocates a new string with the enough length for the path.
}

bool createDirectory(string path)
{
    return mkdir(path) == 0;
}

bool changeDirectory(string path)
{
    return chdir(path) == 0;
}

bool directoryExists(const string path)
{
    struct stat stats;

    stat(path, &stats);

    return S_ISDIR(stats.st_mode);
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

bool writeStringToFile(FILE* file, string str, ...)
{
    va_list args;

    va_start(args, str);

    bool ret = writeStringToFileArgs(file, str, args);
    
    va_end(args);

    return ret;
}

bool writeStringToFileArgs(FILE* file, string str, va_list args)
{
    return vfprintf(file, str, args) >= 0;
}