//! DIV Games Studio 2 - Dinamic Link Library - Header File.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Modified DIV Games Studio 2 API header for TLSA98 Engine.
*/

#include "DIV2API.H"

// long_header macro lenght from DIV.H:
#define DIV_H_LONG_HEADER 9
// _net struct in DIV.H, used now to store the TLSA98 Engine interface pointer:
#define DIV_H_NET_STRUCT_LENGTH 9
#define DIV_H_TEXT_OFFSET 0

#define MAX_TIMERS 10
#define MAX_ARGUMENT_VALUES 10
#define MAX_SOUND_CHANNELS 32
#define MAX_SCROLL_WINDOWS 10
#define MAX_MODE7_WINDOWS 10
#define MAX_MODE8_CAMERAS 10
#define MAX_VIDEO_MODES 32

// Replaces DIV.H _net struct with the same size in int units.
typedef struct
{
    int buffer[DIV_H_NET_STRUCT_LENGTH];
} tlsa98_engine_interface_t;

typedef struct
{
    int timer[MAX_TIMERS];
    int textZ; // text_z
    int fading;
    int shiftStatus; // shift_status
    int ascii;
    E_DIV_KEY_CODE scanCode;         // scan_code
    int joyFilter;                   // joy_filter
    E_DIV_JOYSTICK_STATUS joyStatus; // joy_status
    E_DIV_RESTORE_TYPE restoreType;  // restore_type
    E_DIV_DUMP_TYPE dumpType;        // dump_type
    int maxProcessTime;              // max_process_time
    int fps;
    int programArgumentsCount;                     // _argc
    int programArgumentValue[MAX_ARGUMENT_VALUES]; // _argv
    int soundChannel[MAX_SOUND_CHANNELS];          // channel
    int vsync;
    int drawZ;           // draw_z
    int videoModesCount; // num_video_modes
    int unitSize;        // unit_size
} div_exported_vars_t;

// This struct maps the entire mem[] array, including the exported variables and except the process instances.
typedef struct
{
    int reserved[DIV_H_LONG_HEADER];
    div_mouse_t mouse;
    div_scroll_t scroll[MAX_SCROLL_WINDOWS];
    div_mode7_t mode7[MAX_MODE7_WINDOWS];
    div_joystick_t joystick;
    div_sound_card_setup_t soundCardSetup;
    tlsa98_engine_interface_t tlsa98Engine;
    div_mode8_t mode8[MAX_MODE8_CAMERAS];
    div_directory_info_t directoryInfo;
    int reserved2; // This field is used to fit the DIV.H defined 1026 int units lenght for _dirinfo struct in mem[] array (_dirinfo struct is 1025 int units length).
    div_file_info_t fileInfo;
    div_video_mode_t videoModes[MAX_VIDEO_MODES];
    div_exported_vars_t exportedVars;
} div_runtime_state_t;

typedef struct
{
    int *offset;  // mem[] index of stack.
    int *pointer; // Stack pointer (as a mem[] index).
} div_runtime_stack_t;

typedef struct
{
    char *palette;            // Pointer to game palette.
    unsigned long ghostTable; // Pointer to ghost-layering table.
    char *activePalette;      // Pointer to active palette (fadings).
    int *setPalette;          // Set to 1 to activate a new palette, set to 2 to activate it twice, etc.
} div_game_palette_t;

typedef struct
{
    int *width;               // Screen width.
    int *height;              // Screen height.
    unsigned long buffer;     // Pointer to video buffer.
    unsigned long background; // Pointer to video background.
} div_screen_t;

typedef struct
{
    div_screen_t screen;        // Screen data.
    div_game_palette_t palette; // Game palette data.
} div_graphic_engine_t;

typedef struct
{
    int *processSize;  // Size of every process (on mem[], number of ints).
    int *root;         // mem[] index of main process.
    int *first;        // mem[] index of first process.
    int *last;         // mem[] index of last process.
    int *lastExecuted; // mem[] index of last executed process.
} div_process_array_t;

typedef void *(*div_malloc_f)(const size_t);
typedef void (*div_free_f)(void *);
typedef FILE *(*div_fopen_f)(const char *, const char *);
typedef int (*div_fclose_f)(FILE *);
typedef int (*div_rand_f)(const int, const int);
typedef void (*div_text_out_f)(char *, const int, const int); // Screen print function.

typedef struct
{
    div_malloc_f malloc;
    div_free_f free;
    div_fopen_f fopen;
    div_fclose_f fclose;
    div_rand_f rand;
    div_text_out_f print; // Screen print function.
} div_exported_functions_t;

static int *runtimeMemory; // Memory of all programs (mem[], int array).
static char *keyboard;
static div_runtime_stack_t stack;
static div_graphic_engine_t graphicEngine;
static div_process_array_t processArray;
static div_exported_functions_t exportedFunctions;

void *(*DIV_import)(char *);

static void initialize()
{
    runtimeMemory = (int *)DIV_import("mem");
    keyboard = (char *)DIV_import("key");

    stack.offset = (int *)DIV_import("stack");
    stack.pointer = (int *)DIV_import("sp");

    graphicEngine.screen.width = (int *)DIV_import("wide");
    graphicEngine.screen.height = (int *)DIV_import("height");
    graphicEngine.screen.buffer = (unsigned long)DIV_import("buffer");
    graphicEngine.screen.background = (unsigned long)DIV_import("background");

    graphicEngine.palette.palette = (char *)DIV_import("palette");
    graphicEngine.palette.ghostTable = (unsigned long)DIV_import("ghost");
    graphicEngine.palette.activePalette = (char *)DIV_import("active_palette");
    graphicEngine.palette.setPalette = (int *)DIV_import("set_palette");

    processArray.processSize = (int *)DIV_import("process_size");
    processArray.root = (int *)DIV_import("id_init_offset");
    processArray.first = (int *)DIV_import("id_start_offset");
    processArray.last = (int *)DIV_import("id_end_offset");
    processArray.lastExecuted = (int *)DIV_import("id_offset");

    exportedFunctions.malloc = (div_malloc_f)DIV_import("div_malloc");
    exportedFunctions.free = (div_free_f)DIV_import("div_free");
    exportedFunctions.fopen = (div_fopen_f)DIV_import("div_fopen");
    exportedFunctions.fclose = (div_fclose_f)DIV_import("div_fclose");
    exportedFunctions.rand = (div_rand_f)DIV_import("div_rand");
    exportedFunctions.print = (div_text_out_f)DIV_import("div_text_out");
}

static div_runtime_state_t *getRuntimeState()
{
    return (div_runtime_state_t *)&runtimeMemory;
}

static div_exported_vars_t *getExportedVariables()
{
    return (div_exported_vars_t *)(&getRuntimeState()->exportedVars);
}

void *malloc(const size_t size)
{
    return exportedFunctions.malloc(size);
}

void free(void *ptr)
{
    exportedFunctions.free(ptr);
}

FILE *fopen(const char *filename, const char *mode)
{
    return exportedFunctions.fopen(filename, mode);
}

int fclose(FILE *file)
{
    return exportedFunctions.fclose(file);
}

int divRand(const int min, const int max)
{
    return exportedFunctions.rand(min, max);
}

void divPrint(const char *text, const int x, const int y)
{
    exportedFunctions.print((char *)text, x, y);
}

int divReadIntParameter()
{
    return stack.offset[(int)stack.pointer--];
}

char *divReadStringParameter()
{
    return (char *)&runtimeMemory[DIV_H_TEXT_OFFSET + divReadIntParameter()];
}

void *divReadStructParameter()
{
    return (void *)&runtimeMemory[divReadIntParameter()];
}

void divReturn(const int value)
{
    stack.offset[(int)(++stack.pointer)] = value;
}
