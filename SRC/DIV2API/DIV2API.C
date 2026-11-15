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

/*
  This struct maps the entire mem[] array, including the exported variables and
  except the process instances.
 */
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
    int reserved2; // This field is used to fit the DIV.H defined 1026 int
    // units lenght for _dirinfo struct in mem[] array (_dirinfo struct is
    // 1025 int units length).
    div_file_info_t fileInfo;
    div_video_mode_t videoModes[MAX_VIDEO_MODES];
    div_exported_vars_t exportedVars;
} div_runtime_state_t;

static int *_stack;
static int *_mem;
static char *_palette;
static char *_active_palette;
static char *_key;
static int *_sp;
static int *_wide;
static int *_height;
static int *_ss_time;
static int *_ss_status;
static int *_ss_exit;
static int *_process_size;
static int *_id_offset;
static int *_id_init_offset;
static int *_id_start_offset;
static int *_id_end_offset;
static int *_set_palette;
static unsigned long _buffer;
static unsigned long _background;
static unsigned long _ghost;

div_mouse_t *divMouse()
{
}
