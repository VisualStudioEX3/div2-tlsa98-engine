/* ----------------------------------------------------------------------------
 * SYSTEM.DLL - System library for DIV Games Studio.
 * (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
 * DIV Games Studio 2 (C) Hammer Technologies - 1998, 1999
 * ---------------------------------------------------------------------------- */

#ifndef _SYSTEM_DLL_
#define _SYSTEM_DLL_

#define GLOBALS                 // Required by DIV.H (before incluide it).
#include "..\DIV.H"             // DIV Games Studio 2 API header.

typedef unsigned char byte;     // BYTE type in DIV Games Studio 2.
typedef unsigned short word;    // WORD type in DIV Games Studio 2.
typedef char* string;           // STRING type in DIV Games Studio 2.

#define bool            int
#define true            1
#define false           0

#define RESULT_OK       0
#define RESULT_ERROR    -1

#define getstrparm()    (string)&mem[text_offset + getparm()]

#define malloc(size)    div_malloc(size)
#define free(ptr)       div_free(ptr)

#define arraylen(a)     sizeof(a) / sizeof(a[0])

#endif
