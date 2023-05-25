//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    System file system functions.
*/

#include <direct.h> // DOS filesystem functions.
#include <stdlib.h>
#include <sys\stat.h>
#include "..\STRING\STRING.H"
#include "FILESYS.H"

const int MAX_FILENAME = _MAX_NAME;     // Max length for a filename in MS-DOS (8:3 format).
const int MAX_PATH = _MAX_PATH;         // Max length for a path in MS-DOS.
const string PATH_SEPARATOR = "\\";     // DOS-WINDOWS path separator char.

string getCurrentDirectory()
{
    string path = getcwd(NULL, MAX_PATH);
    int len = stringLength(path);

    path[len] = PATH_SEPARATOR[0]; // Add path terminator.

    string ret = stringCopy(path);

    free(path);

    return ret;
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

string combinePath(int count, ...)
{
    va_list args;

    va_start(args, count);

    string path = combinePathArgs(count, args);

    va_end(args);

    return path;
}

string combinePathArgs(int count, va_list args)
{
    return stringJoinArgs(PATH_SEPARATOR, count, args);
}

FILE* openFile(string filename, string mode)
{
    return fopen(filename, mode);
}

void closeFile(FILE* file)
{
    // TODO: Asserts NULL file handle.
    fclose(file);
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
