//! DIV Games Studio 2 - Dinamic Link Library - Header File.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Modified DIV Games Studio 2 API header for TLSA98 Engine.
*/

#ifndef __DIV2_API_H_
#define __DIV2_API_H_

#include <stdio.h>

// ============================================================================
// Global constants.
// ============================================================================

/// @brief Null value.
#define NULL 0

/// @brief Default value for DIV "draw_z" variable.
#define DEFAULT_DRAW_Z -255

/// @brief Default value for DIV "text_z" variable.
#define DEFAULT_TEXT_Z -256

// ============================================================================
// Enumerations for common data in DIV Games Studio.
// ============================================================================

/// @brief DIV process states.
typedef enum
{
    /// @brief Process dead or not exists.
    DIV_PROCESS_STATUS_NOT_EXISTS = 0,
    /// @brief Process is alive.
    DIV_PROCESS_STATUS_KILLED = 1, // s_kill
    /// @brief Process is awake.
    DIV_PROCESS_STATUS_AWAKE = 2, // s_wakeup
    /// @brief Process is asleep.
    DIV_PROCESS_STATUS_ASLEEP = 3, // s_sleep
    /// @brief Process is frozen.
    DIV_PROCESS_STATUS_FROZEN = 4, // s_freeze
} E_DIV_PROCESS_STATUS;

/// @brief DIV coordinate types.
typedef enum
{
    /// @brief Screen space coordinates (default).
    DIV_CTYPE_SCREEN = 0,
    /// @brief Scroll space coordinates.
    DIV_CTYPE_SCROLL = 1,
    /// @brief Mode7 space coordinates.
    DIV_CTYPE_MODE7 = 2,
    /// @brief Mode8 space coordinates.
    DIV_CTYPE_MODE8 = 3,
} E_DIV_CTYPE;

/**
 * @brief DIV graphic flags.
 * @remarks DIV engine define this values as normal enum values instead of real flag values, can't be combined.
 */
typedef enum
{
    /// @brief Default state, not effects applied.
    DIV_GRAPHIC_FLAG_DEFAULT = 0,
    /// @brief Mirroring in horizontal axis.
    DIV_GRAPHIC_FLAG_MIRROR_HORIZONTAL = 1,
    /// @brief Mirroring in vertical axis.
    DIV_GRAPHIC_FLAG_MIRROR_VERTICAL = 2,
    /// @brief Mirroring in both axes (180º).
    DIV_GRAPHIC_FLAG_MIRROR_BOTH = 3,
    /// @brief Used ghost table to applied transparency.
    DIV_GRAPHIC_FLAG_GHOST = 4,
    /// @brief Transparency and mirroring in horizontal axis.
    DIV_GRAPHIC_FLAG_GHOST_MIRROR_HORIZONTAL = 5,
    /// @brief Transparency and mirroring in vertical axis.
    DIV_GRAPHIC_FLAG_GHOST_MIRROR_VERTICAL = 6,
    /// @brief Transparency and mirroring in both axes.
    DIV_GRAPHIC_FLAG_GHOST_MIRROR_BOTH = 7,
} E_DIV_GRAPHIC_FLAG;

/// @brief Supported sound cards by DIV engine.
typedef enum
{
    /// @brief No sound card.
    SOUND_CARD_NONE = 0,
    /// @brief Sound Blaster 1.5.
    SOUND_CARD_SOUND_BLASTER_V_1_5 = 1,
    /// @brief Sound Blaster 2.0.
    SOUND_CARD_SOUND_BLASTER_V_2_0 = 2,
    /// @brief Sound Blaster Pro.
    SOUND_CARD_SOUND_BLASTER_PRO = 3,
    /// @brief Sound Blaster 16.
    SOUND_CARD_SOUND_BLASTER_16 = 4,
    /// @brief Sound Blaster AWE.
    SOUND_CARD_SOUND_BLASTER_AWE = 5,
    /// @brief Gravis Ultra Sound.
    SOUND_CARD_GRAVIS_ULTRA_SOUN = 6,
    /// @brief Gravis Ultra Sound MAX.
    SOUND_CARD_GRAVIS_ULTRA_SOUND_MAX = 7,
} E_DIV_SOUND_CARD;

/// @brief Sound card ports.
typedef enum
{
    /// @brief Port 210.
    SOUND_CARD_PORT_0x210 = 0,
    /// @brief Port 220.
    SOUND_CARD_PORT_0x220 = 1,
    /// @brief Port 230.
    SOUND_CARD_PORT_0x230 = 2,
    /// @brief Port 240.
    SOUND_CARD_PORT_0x240 = 3,
    /// @brief Port 250.
    SOUND_CARD_PORT_0x250 = 4,
    /// @brief Port 260.
    SOUND_CARD_PORT_0x260 = 5,
} E_DIV_SOUND_CARD_PORT;

/// @brief Sound card required interruptions.
typedef enum
{
    /// @brief IRQ 2.
    SOUND_CARD_IRQ_2 = 0,
    /// @brief IRQ 3.
    SOUND_CARD_IRQ_3 = 1,
    /// @brief IRQ 5.
    SOUND_CARD_IRQ_5 = 2,
    /// @brief IRQ 7.
    SOUND_CARD_IRQ_7 = 3,
    /// @brief IRQ 10.
    SOUND_CARD_IRQ_10 = 4,
    /// @brief IRQ 11.
    SOUND_CARD_IRQ_11 = 5,
    /// @brief IRQ 12.
    SOUND_CARD_IRQ_12 = 6,
    /// @brief IRQ 13.
    SOUND_CARD_IRQ_13 = 7,
    /// @brief IRQ 14.
    SOUND_CARD_IRQ_14 = 8,
    /// @brief IRQ 15.
    SOUND_CARD_IRQ_15 = 9,
} E_DIV_SOUND_CARD_IRQ;

/// @brief Sound card mixers.
typedef enum
{
    /// @brief Fast mixer (default).
    SOUND_CARD_MIXER_FAST = 1,
    /// @brief Quality mixer.
    SOUND_CARD_MIXER_QUALITY = 2,
} E_DIV_SOUND_CARD_MIXER;

/// @brief Sound card audio bit qualities.
typedef enum
{
    /// @brief 8 bits.
    SOUND_CARD_QUALITY_8_BITS = 8,
    /// @brief 16 bits.
    SOUND_CARD_QUALITY_16_BITS = 16,
} E_DIV_SOUND_CARD_QUALITY;

/// @brief DIV render restore types.
typedef enum
{
    /// @brief No restore.
    DIV_RESTORE_TYPE_NONE = -1,
    /// @brief Partial restore.
    DIV_RESTORE_TYPE_PARTIAL = 0,
    /// @brief Complete restore.
    DIV_RESTORE_TYPE_COMPLETE = 1,
} E_DIV_RESTORE_TYPE;

/// @brief DIV render dump types.
typedef enum
{
    /// @brief Partial dump.
    DIV_DUMP_TYPE_PARTIAL = 0,
    /// @brief Complete dump.
    DIV_DUMP_TYPE_COMPLETE = 1,
} E_DIV_DUMP_TYPE;

/**
 * @brief DIV keyboard key codes.
 * @remarks DIV Games Studio documented this key codes using a qwerty keyboard
 * with spanish layout.
 */
typedef enum
{
    /// @brief No key code.
    KEY_NONE = 0,

    /// @brief Key escape.
    KEY_ESC = 1,
    /// @brief Key function 1.
    KEY_F1 = 59,
    /// @brief Key function 2.
    KEY_F2 = 60,
    /// @brief Key function 3.
    KEY_F3 = 61,
    /// @brief Key function 4.
    KEY_F4 = 62,
    /// @brief Key function 5.
    KEY_F5 = 63,
    /// @brief Key function 6.
    KEY_F6 = 64,
    /// @brief Key function 7.
    KEY_F7 = 65,
    /// @brief Key function 8.
    KEY_F8 = 66,
    /// @brief Key function 9.
    KEY_F9 = 67,
    /// @brief Key function 10.
    KEY_F10 = 68,
    /// @brief Key function 11.
    KEY_F11 = 87,
    /// @brief Key function 12.
    KEY_F12 = 88,
    /// @brief Key print screen.
    KEY_PRN_SCR = 55,
    /// @brief Key scroll lock.
    KEY_SCROLL_LOCK = 70,

    /// @brief Key º.
    KEY_WAVE = 41,
    /// @brief Key 1.
    KEY_1 = 2,
    /// @brief Key 2.
    KEY_2 = 3,
    /// @brief Key 3.
    KEY_3 = 4,
    /// @brief Key 4.
    KEY_4 = 5,
    /// @brief Key 5.
    KEY_5 = 6,
    /// @brief Key 6.
    KEY_6 = 7,
    /// @brief Key 7.
    KEY_7 = 8,
    /// @brief Key 8.
    KEY_8 = 9,
    /// @brief Key 9.
    KEY_9 = 10,
    /// @brief Key 0.
    KEY_0 = 11,
    /// @brief Key ?
    KEY_MINUS = 12,
    /// @brief Key ¿
    KEY_PLUS = 13,
    /// @brief Key backspace.
    KEY_BACKSPACE = 14,

    /// @brief Key tab.
    KEY_TAB = 15,
    /// @brief Key Q.
    KEY_Q = 16,
    /// @brief Key W.
    KEY_W = 17,
    /// @brief Key E.
    KEY_E = 18,
    /// @brief Key R.
    KEY_R = 19,
    /// @brief Key T.
    KEY_T = 20,
    /// @brief Key Y.
    KEY_Y = 21,
    /// @brief Key U.
    KEY_U = 22,
    /// @brief Key I.
    KEY_I = 23,
    /// @brief Key O.
    KEY_O = 24,
    /// @brief Key P.
    KEY_P = 25,
    /// @brief Key [.
    KEY_L_BRACKET = 26,
    /// @brief Key ].
    KEY_R_BRACKET = 27,
    /// @brief Key enter.
    KEY_ENTER = 28,

    /// @brief Key cap lock.
    KEY_CAPS_LOCK = 58,
    /// @brief Key A.
    KEY_A = 30,
    /// @brief Key S.
    KEY_S = 31,
    /// @brief Key D.
    KEY_D = 32,
    /// @brief Key F.
    KEY_F = 33,
    /// @brief Key G.
    KEY_G = 34,
    /// @brief Key H.
    KEY_H = 35,
    /// @brief Key J.
    KEY_J = 36,
    /// @brief Key K.
    KEY_K = 37,
    /// @brief Key L.
    KEY_L = 38,
    /// @brief Key Ñ.
    KEY_SEMICOLON = 39,
    /// @brief Key {.
    KEY_APOSTROPHE = 40,
    /// @brief Key }.
    KEY_BACKSLASH = 43,

    /// @brief Key left shift.
    KEY_L_SHIFT = 42,
    /// @brief Key Z.
    KEY_Z = 44,
    /// @brief Key X.
    KEY_X = 45,
    /// @brief Key C.
    KEY_C = 46,
    /// @brief Key V.
    KEY_V = 47,
    /// @brief Key B.
    KEY_B = 48,
    /// @brief Key N.
    KEY_N = 49,
    /// @brief Key M.
    KEY_M = 50,
    /// @brief Key comma.
    KEY_COMMA = 51,
    /// @brief Key period.
    KEY_POINT = 51,
    /// @brief Key slash.
    KEY_SLASH = 51,
    /// @brief Key left shift.
    KEY_R_SHIFT = 54,

    /// @brief Control keys.
    KEY_CONTROL = 29,
    /// @brief Alt keys.
    KEY_ALT = 56,
    /// @brief Key space.
    KEY_SPACE = 57,

    /// @brief Key insert.
    KEY_INS = 82,
    /// @brief Key home.
    KEY_HOME = 71,
    /// @brief Key page up.
    KEY_PGUP = 73,
    /// @brief Key delete.
    KEY_DEL = 83,
    /// @brief Key end.
    KEY_END = 79,
    /// @brief Key page down.
    KEY_PGDN = 81,

    /// @brief Key up arrow.
    KEY_UP = 72,
    /// @brief Key down arrow.
    KEY_DOWN = 80,
    /// @brief Key left arrow.
    KEY_LEFT = 75,
    /// @brief Key right arrow.
    KEY_RIGHT = 77,

    /// @brief Key number block lock.
    KEY_NUM_LOCK = 69,
    /// @brief Key block fowardslash or division.
    KEY_C_BACKSLASH = 53,
    /// @brief Key number block asterik or multiplication.
    KEY_C_ASTERISK = 55,
    /// @brief Key number block slash or substract.
    KEY_C_MINUS = 74,
    /// @brief Key number block 7 or home.
    KEY_C_HOME = 71,
    /// @brief Key number block 8 or up arrow.
    KEY_C_UP = 72,
    /// @brief Key number block 9 or page up.
    KEY_C_PGUP = 73,
    /// @brief Key number block 4 or left arrow.
    KEY_C_LEFT = 75,
    /// @brief Key number block 5.
    KEY_C_CENTER = 76,
    /// @brief Key number block 6 or right arrow.
    KEY_C_RIGHT = 77,
    /// @brief Key number block 1 or end.
    KEY_C_END = 79,
    /// @brief Key number block 2 or down arrow.
    KEY_C_DOWN = 80,
    /// @brief Key number block 3 or page down.
    KEY_C_PGDN = 81,
    /// @brief Key number block 0 or insert.
    KEY_C_INS = 82,
    /// @brief Key number block period or delete.
    KEY_C_DEL = 83,
    /// @brief Key number block add.
    KEY_C_PLUS = 78,
    /// @brief Key number block enter.
    KEY_C_ENTER = 28,
} E_DIV_KEY_CODE;

/// @brief DIV keyboard shift state flags.
typedef enum
{
    /// @brief Right shift key.
    KEY_SHIFT_STATUS_RIGHT_SHIFT = 1,
    /// @brief Left shift key.
    KEY_SHIFT_STATUS_LEFT_SHIFT = 2,
    /// @brief Controls shift keys.
    KEY_SHIFT_STATUS_CONTROL = 4,
    /// @brief Alt and AltGr shift keys.
    KEY_SHIFT_STATUS_ALT = 8,
    /// @brief Scroll lock shift key.
    KEY_SHIFT_STATUS_SCROLL_LOCK = 16,
    /// @brief Number block shift key.
    KEY_SHIFT_STATUS_NUMBER_BLOCK = 32,
    /// @brief Caps lock shift key.
    KEY_SHIFT_STATUS_CAPS_LOCK = 64,
    /// @brief Insert shift key.
    KEY_SHIFT_STATUS_INSERT = 128,
} E_DIV_SHIFT_STATUS;

/// @brief DIV joystick system states.
typedef enum
{
    /// @brief Joystick state disabled.
    DIV_JOYSTICK_STATUS_DISABLED = 0,
    /// @brief Joystick state enabled.
    DIV_JOYSTICK_STATUS_ENABLED = 1,
    /// @brief Force enable joystick system.
    DIV_JOYSTICK_STATUS_FORCE_ENABLED = 2,
} E_DIV_JOYSTICK_STATUS;

/**
 * @brief DIV file attributes.
 * @remarks This flag attributes are the same values as MS-DOS file attributes.
 */
typedef enum
{
    /// @brief Normal file.
    DIV_FILE_ATTRIBUTE_NORMAL = 0,
    /// @brief Readonly file.
    DIV_FILE_ATTRIBUTE_READONLY = 1,
    /// @brief Hidden file.
    DIV_FILE_ATTRIBUTE_HIDDEN = 2,
    /// @brief System file.
    DIV_FILE_ATTRIBUTE_SYSTEM = 4,
    /// @brief Volume label.
    DIV_FILE_ATTRIBUTE_VOLUMEID = 8,
    /// @brief Directory.
    DIV_FILE_ATTRIBUTE_DIRECTORY = 16,
    /// @brief Archive.
    DIV_FILE_ATTRIBUTE_ARCHIVE = 32,
} E_DIV_FILE_ATTRIBUTE;

// ============================================================================
// Definitions of basic language structures
// ============================================================================

/// @brief Point 2D.
typedef struct
{
    /// @brief X coordinate.
    int x;
    /// @brief Y coordinate.
    int y;
} point2_t;

/// @brief Point 3D.
typedef struct
{
    /// @brief X coordinate.
    int x;
    /// @brief Y coordinate.
    int y;
    /// @brief Z coordinate.
    int z;
} point3_t;

/// @brief Rectangle.
typedef struct
{
    /// @brief Left side X coordinate.
    int left; // x0
    /// @brief Top side Y coordinate.
    int top; // y0
    /// @brief Right side X coordinate.
    int right; // x1
    /// @brief Bottom side Y coordinate.
    int bottom; // y1
} rect_t;

/// @brief Internal DIV process data.
typedef struct __reserved
{
    /// @brief Process id.
    int id;

    /// @brief Id of the last process that collide with us.
    int idScan; // idscan

    /// @brief Process type.
    int processType; // block

    /// @brief The last get_id() value.
    int typeScan; // blscan

    /// @brief Current status.
    E_DIV_PROCESS_STATUS status;

    /**
     * @brief Address of the process parameters.
     * @remarks Computer memory address where the parameters received by the process are located.
     */
    int parametersOffset; // param_number

    /// @brief Pointer to process parameters.
    int parametersPointer; // param

    /**
     * @brief Program counter.
     * @remarks The computer memory address where the first instruction to be executed in the next frame by the process is located.
     */
    int programCounter; // ip

    /**
     * @brief Process stack pointer.
     * @remarks Each process’s local stack pointer, maintains the address of the stack at the time the process is entered, with the parameters pushed onto the stack.
     */
    int stackPointer; // sp

    /// @brief Gets if the process was executed.
    int isExecuted; // executed

    /// @brief Gets if the process was drawed.
    int isDrawed; // painted

    /**
     * @brief Object inside of Mode8 world.
     * @remarks An ordinal number corresponding to the sector map is indicated.
     */
    int mode8Object; // object

    /**
     * @brief Old coordinate type (ctype).
     * @remarks Previous value of the local variable "ctype", used to track scope changes in a process's coordinates.
     */
    E_DIV_CTYPE oldCType; // old_ctype

    /**
     * @brief Percent of frame complete.
     * @remarks This value will be useful when the FRAME statement is used with a specified percentage. Otherwise, it will simply be 0 (0%) when the process has not yet been executed, and 100 (100%) once it has been executed.
     */
    int framePercent; // frame

    /**
     * @brief Bounding box.
     * @remarks Is represented by the dimensions of the process graphic in screen. If the process has not graphic, the bounding box is an empty rect.
     */
    rect_t boundingBox;

    /// @brief Function nesting counter.
    int functionNestingCounter; // f_count

    /**
     * @brief Id code of the process or function that invoked this one.
     * @remarks The id is zero when the caller was the kernel.
     */
    int callerId; // caller_id
} div_process_internal_t;

/// @brief DIV process hierarchy.
typedef struct
{
    /// @brief Father's id.
    int father;
    /// @brief Son's id.
    int son;
    /// @brief Small brother's id.
    int smallBrother; // smallbro
    /// @brief Big brother's id.
    int bigBrother; // bigbro
} div_process_hierarchy_t;

/// @brief DIV process Mode8 data.
typedef struct
{
    /// @brief Radius for collision.
    int radius;
    /// @brief World wall.
    int wall;
    /// @brief World sector.
    int sector;
    /// @brief Next sector number.
    int nextSector; // nextsector
    /// @brief Height step.
    int step;
} div_process_m8_t;

/// @brief DIV process data.
typedef struct _process
{
    /// @brief Internal data.
    div_process_internal_t internal;
    /// @brief Process hierarchy.
    div_process_hierarchy_t hierarchy;
    /// @brief Process priority.
    int priority;
    /// @brief Type of coordinates.
    E_DIV_CTYPE cType;
    point3_t position;
    /// @brief Process graphic id.
    int graph;
    /// @brief Process flags.
    E_DIV_GRAPHIC_FLAG flags;
    /// @brief Process scale.
    int size;
    /// @brief Process angle.
    int angle;
    /// @brief Process region.
    int region;
    /// @brief Process FPG id.
    int file;
    /// @brief Pointer to angular graphic table.
    int xGraph;
    /// @brief Height of process in mode 7.
    int height;
    /// @brief Scroll or mode 7 window for that process.
    int cNumber;
    /// @brief Coordinates resolution of process.
    int resolution;
    /// @brief Mode8 data.
    div_process_m8_t mode8;
} div_process_t;

/// @brief DIV mouse data.
typedef struct __mouse
{
    /// @brief Mouse coordinates.
    point3_t position;
    /// @brief Mouse FPG id.
    int file;
    /// @brief Mouse graphic id.
    int graph;
    /// @brief Mouse pointer angle.
    int angle;
    /// @brief Mouse pointer scale.
    int size;
    /// @brief Mouse flags.
    E_DIV_GRAPHIC_FLAG flags;
    /// @brief Mouse region.
    int region;
    /// @brief Left mouse button state.
    int left;
    /// @brief Middle mouse button state.
    int middle;
    /// @brief Right mouse button state.
    int right;
    /// @brief Cursor emulation state.
    int cursor;
    /// @brief Mouse pointer speed.
    int speed;
} div_mouse_t;

/// @brief Max number of regions for scrolls.
#define DIV_SCROLL_MAX_REGIONS 2

/// @brief Default value for [div_scroll_t] region fields.
#define DIV_SCROLL_REGION_NONE -1

/// @brief DIV scroll data.
typedef struct __scroll
{
    /// @brief Scroll Z coordinate.
    int z;
    /// @brief Process identifier code followed by the camera.
    int camera;
    /// @brief Background speed ratio.
    int ratio;
    /// @brief Maximum scrolling speed.
    int speed;
    /**
     * @brief Scroll regions.
     * @remarks Values setup by define_region() DIV function.
     */
    int region[DIV_SCROLL_MAX_REGIONS];
    /// @brief Foreground layer position.
    point2_t frontLayerOffset;
    /// @brief Background layer position.
    point2_t backgroundLayerOffset;
} div_scroll_t;

/// @brief DIV Mode7 data.
typedef struct __m7
{
    /// @brief Mode7 Z coordinate.
    int z;
    /// @brief Process identifier code.
    int camera;
    /// @brief Camera height.
    int height;
    /// @brief Distance between process and camera.
    int distance;
    /// @brief Horizon position.
    int horizon;
    /// @brief Camera focus.
    int focus;
    /// @brief Background colour.
    int color;
} div_mode7_t;

/// @brief Max number of buttons for joysticks and gamepads.
#define MAX_JOYSTICK_BUTTONS 4

/// @brief DIV joystick data.
typedef struct __joy
{
    /// @brief Button states.
    const int button[MAX_JOYSTICK_BUTTONS];
    /// @brief Cross direction left state.
    const int left;
    /// @brief Cross direction right state.
    const int right;
    /// @brief Cross direction up state.
    const int up;
    /// @brief Cross direction up state.
    const int down;
} div_joystick_t;

/// @brief Sound card min volume value.
#define SOUND_CARD_MIN_VOLUME 0

/// @brief Sound card max volume value.
#define SOUND_CARD_MAX_VOLUME 15

/// @brief Sound volume parameters.
typedef struct
{
    /**
     * @brief Master volume.
     * @remarks A value between [SOUND_CARD_MIN_VOLUME] and [SOUND_CARD_MAX_VOLUME].
     */
    int master;

    /**
     * @brief Sound effects volume.
     * @remarks A value between [SOUND_CARD_MIN_VOLUME] and [SOUND_CARD_MAX_VOLUME].
     */
    int soundFx; // sound_fx

    /**
     * @brief Music CD volume.
     * @remarks A value between [SOUND_CARD_MIN_VOLUME] and [SOUND_CARD_MAX_VOLUME].
     */
    int cdAudio; // cd_audio
} div_sound_volume_t;

/// @brief Sound card min DMA value.
#define SOUND_CARD_MIN_DMA 0

/// @brief Sound card max DMA value.
#define SOUND_CARD_MAX_DMA 10

/// @brief Sound card min bitrate.
#define SOUND_CARD_MIN_BITRATE 11025

/// @brief Sound card max bitrate.
#define SOUND_CARD_MAX_BITRATE 44100

/// @brief DIV sound card setup data.
typedef struct __setup
{
    /// @brief Card type.
    E_DIV_SOUND_CARD card;

    /// @brief Access port.
    E_DIV_SOUND_CARD_PORT port;

    /// @brief Required interruption.
    E_DIV_SOUND_CARD_IRQ irq;

    /**
     * @brief Access memory channel.
     * @remarks A value between [SOUND_CARD_MIN_DMA] and [SOUND_CARD_MAX_DMA].
     */
    int dma;

    /**
     * @brief Access 16 bit memory channel (a.k.a. HDMA, DMA2 or DMA16).
     * @remarks A value between [SOUND_CARD_MIN_DMA] and [SOUND_CARD_MAX_DMA].
     */
    int dma2;

    /// @brief Volume parameters.
    div_sound_volume_t volume;

    /// @brief Mixer type.
    E_DIV_SOUND_CARD_MIXER mixer;

    /**
     * @brief Bitrate.
     * @remarks A value between [SOUND_CARD_MIN_BITRATE] and [SOUND_CARD_MAX_BITRATE].
     */
    int rate;

    /// @brief Sound quality.
    E_DIV_SOUND_CARD_QUALITY bits;
} div_sound_card_setup_t;

/// @brief DIV Mode8 data.
typedef struct __m8
{
    /// @brief Z coordinate.
    int z;
    /// @brief Process id to attach the camera.
    int camera;
    /// @brief Camera height.
    int height;
    /// @brief Camera vertical angle.
    int angle;
} div_mode8_t;

/// @brief Max number of filenames retrieved in [div_directory_info_t].
#define MAX_DIRECTORY_INFO_FILENAMES 1024

/**
 * @brief DIV directory information data.
 * @remarks This struct is filled by DIV get_dirinfo() function.
 */
typedef struct __dirinfo
{
    /// @brief Number of files in the directory.
    const int files;
    /// @brief List of filenames.
    const int name[MAX_DIRECTORY_INFO_FILENAMES];
} div_directory_info_t;

/// @brief Max filename path length.
#define MAX_PATH 256

/// @brief Max directory name lenght.
#define MAX_DIRECTORY_NAME 256

/// @brief Max filename lenght.
#define MAX_FILE_NAME 12

/// @brief Max filename extension length.
#define MAX_FILE_EXTENSION 8

/**
 * @brief DIV file information data.
 * @remarks This struct is filled by DIV get_fileinfo() function.
 */
typedef struct __fileinfo
{
    /// @brief Filename string lenght.
    const int filenameLength; // fullpath_fix

    /// @brief Full path filename.
    const char filename[MAX_PATH]; // fullpath

    /**
     * @brief Drive index.
     * @remarks Drive letter is returned as integer value (1..26): 1 = A, 2 = B, 3 = C...
     */
    const int drive;

    /// @brief Directory string lenght.
    const int directoryLenght; // dir_fix

    /// @brief Directory name where the file is stored.
    const char directory[MAX_DIRECTORY_NAME]; // dir

    /// @brief Filename string lenght.
    const int nameLenght; // name_fix

    /// @brief Filename, without the extension.
    const char name[MAX_FILE_NAME];

    /// @brief Filename extension string lenght.
    const int extensionLenght; // ext_fix

    /// @brief Filename extension.
    const char extension[MAX_FILE_EXTENSION]; // ext

    /**
     * @brief File size.
     * @remarks By default the size is returned in int units. This unit can be changed using the DIV variable "unit_size". See DIV documentation for more information.
     *
     * For directories, this value is always zero.
     */
    const int size;

    /// @brief Day of the last update.
    const int day;

    /// @brief Month of the last update.
    const int month;

    /// @brief Year of the last update.
    const int year;

    /// @brief Hour of the last update.
    const int hour;

    /// @brief Minute of the last update.
    const int minute; // min

    /// @brief Second of the last update.
    const int second; // sec

    /// @brief File attributes.
    const E_DIV_FILE_ATTRIBUTE attributes; // attrib
} div_file_info_t;

/// @brief DIV video mode data.
typedef struct __video_modes
{
    /// @brief Screen width.
    const int width; // wide
    /// @brief Screen height.
    const int height;
    /// @brief // Video mode value to pass to DIV set_mode() function.
    const int mode;
} div_video_mode_t;

/**
 * @brief DIV keyboard state.
 * @remarks This struct mapped each position of the DIV runtime key array (the 88 documented keycodes).
 */
typedef struct
{
    /// @brief Key escape.
    /// @enum [KEY_ESC]
    const char escape;

    /// @brief Key 1.
    /// @enum [KEY_1]
    const char key1;

    /// @brief Key 2.
    /// @enum [KEY_2]
    const char key2;

    /// @brief Key 3.
    /// @enum [KEY_3]
    const char key3;

    /// @brief Key 4.
    /// @enum [KEY_4]
    const char key4;

    /// @brief Key 5.
    /// @enum [KEY_5]
    const char key5;

    /// @brief Key 6.
    /// @enum [KEY_6]
    const char key6;

    /// @brief Key 7.
    /// @enum [KEY_7]
    const char key7;

    /// @brief Key 8.
    /// @enum [KEY_8]
    const char key8;

    /// @brief Key 9.
    /// @enum [KEY_9]
    const char key9;

    /// @brief Key 0.
    /// @enum [KEY_0]
    const char key0;

    /// @brief Key ?
    /// @enum [KEY_MINUS]
    const char minus;

    /// @brief Key ¿
    /// @enum [KEY_PLUS]
    const char plus;

    /// @brief Key backspace.
    /// @enum [KEY_BACKSPACE]
    const char backSpace;

    /// @brief Key tab.
    /// @enum [KEY_TAB]
    const char tab;

    /// @brief Key Q.
    /// @enum [KEY_Q]
    const char q;

    /// @brief Key W.
    /// @enum [KEY_W]
    const char w;

    /// @brief Key E.
    /// @enum [KEY_E]
    const char e;

    /// @brief Key R.
    /// @enum [KEY_R]
    const char r;

    /// @brief Key T.
    /// @enum [KEY_T]
    const char t;

    /// @brief Key Y.
    /// @enum [KEY_Y]
    const char y;

    /// @brief Key U.
    /// @enum [KEY_U]
    const char u;

    /// @brief Key I.
    /// @enum [KEY_I]
    const char i;

    /// @brief Key O.
    /// @enum [KEY_O]
    const char o;

    /// @brief Key P.
    /// @enum [KEY_P]
    const char p;

    /// @brief Key [.
    /// @enum [KEY_L_BRACKET]
    const char leftBracket;

    /// @brief Key ].
    /// @enum [KEY_R_BRACKET]
    const char rightBracket;

    /// @brief Key enter.
    /// @enum [KEY_ENTER]
    const char enter;

    /// @brief Control keys.
    /// @enum [KEY_CONTROL]
    const char control;

    /// @brief Key A.
    /// @enum [KEY_A]
    const char a;

    /// @brief Key S.
    /// @enum [KEY_S]
    const char s;

    /// @brief Key D.
    /// @enum [KEY_D]
    const char d;

    /// @brief Key F.
    /// @enum [KEY_E]
    const char f;

    /// @brief Key G.
    /// @enum [KEY_G]
    const char g;

    /// @brief Key H.
    /// @enum [KEY_H]
    const char h;

    /// @brief Key J.
    /// @enum [KEY_J]
    const char j;

    /// @brief Key K.
    /// @enum [KEY_K]
    const char k;

    /// @brief Key L.
    /// @enum [KEY_L]
    const char l;

    /// @brief Key Ñ.
    /// @enum [KEY_SEMICOLON]
    const char semiColon;

    /// @brief Key {.
    /// @enum [KEY_APOSTROPHE]
    const char apostrophe;

    /// @brief Key º.
    /// @enum [KEY_WAVE]
    const char wave;

    /// @brief Key left shift.
    /// @enum [KEY_L_SHIFT]
    const char leftShift;

    /// @brief Key }.
    /// @enum [KEY_BACKSLASH]
    const char backSlash;

    /// @brief Key Z.
    /// @enum [KEY_Z]
    const char z;

    /// @brief Key X.
    /// @enum [KEY_X]
    const char x;

    /// @brief Key C.
    /// @enum [KEY_C]
    const char c;

    /// @brief Key V.
    /// @enum [KEY_V]
    const char v;

    /// @brief Key B.
    /// @enum [KEY_B]
    const char b;

    /// @brief Key N.
    /// @enum [KEY_N]
    const char n;

    /// @brief Key M.
    /// @enum [KEY_M]
    const char m;

    /// @brief Key period.
    /// @enum [KEY_COMMA], [KEY_POINT], [KEY_SLASH]
    const char period;

    /// @brief Key block fowardslash or division.
    /// @enum [KEY_C_BACKSLASH]
    const char forwardSlash;

    /// @brief Key right shift.
    /// @enum [KEY_R_SHIFT]
    const char rightShift;

    /// @brief Key print screen.
    /// @enum [KEY_PRN_SCR]
    const char printScreen;

    /// @brief Alt keys.
    /// @enum [KEY_ALT]
    const char alt;

    /// @brief Key space.
    /// @enum [KEY_SPACE]
    const char space;

    /// @brief Key cap lock.
    /// @enum [KEY_CAPS_LOCK]
    const char capsLock;

    /// @brief Key function 1.
    /// @enum [KEY_F1]
    const char f1;

    /// @brief Key function 2.
    /// @enum [KEY_F2]
    const char f2;

    /// @brief Key function 3.
    /// @enum [KEY_F3]
    const char f3;

    /// @brief Key function 4.
    /// @enum [KEY_F4]
    const char f4;

    /// @brief Key function 5.
    /// @enum [KEY_F5]
    const char f5;

    /// @brief Key function 6.
    /// @enum [KEY_F6]
    const char f6;

    /// @brief Key function 7.
    /// @enum [KEY_F7]
    const char f7;

    /// @brief Key function 8.
    /// @enum [KEY_F8]
    const char f8;

    /// @brief Key function 9.
    /// @enum [KEY_F9]
    const char f9;

    /// @brief Key function 10.
    /// @enum [KEY_F10]
    const char f10;

    /// @brief Key number block lock.
    /// @enum [KEY_NUM_LOCK]
    const char numLock;

    /// @brief Key scroll lock.
    /// @enum [KEY_SCROLL_LOCK]
    const char scrollLock;

    /// @brief Key home.
    /// @enum [KEY_HOME], [KEY_C_HOME]
    const char home;

    /// @brief Key up arrow.
    /// @enum [KEY_UP], [KEY_C_UP]
    const char up;

    /// @brief Key page up.
    /// @enum [KEY_PGUP], [KEY_C_PGUP]
    const char pageUp;

    /// @brief Key number block slash or substract.
    /// @enum [KEY_C_MINUS]
    const char numMinus;

    /// @brief Key left arrow.
    /// @enum [KEY_LEFT], [KEY_C_LEFT]
    const char left;

    /// @brief Key number block 5.
    /// @enum [KEY_C_CENTER]
    const char numCenter;

    /// @brief Key right arrow.
    /// @enum [KEY_RIGHT], [KEY_C_RIGHT]
    const char right;

    /// @brief Key number block add.
    /// @enum [KEY_C_PLUS]
    const char numPlus;

    /// @brief Key end.
    /// @enum [KEY_END], [KEY_C_END]
    const char end;

    /// @brief Key down arrow.
    /// @enum [KEY_DOWN], [KEY_C_DOWN]
    const char down;

    /// @brief Key page down.
    /// @enum [KEY_PGDN], [KEY_C_PGDN]
    const char pageDown;

    /// @brief Key insert.
    /// @enum [KEY_INS], [KEY_C_INS]
    const char insert;

    /// @brief Key delete.
    /// @enum [KEY_DEL], [KEY_C_DEL]
    const char delete;

    /// @brief Undocumented keycode 84.
    const char keyCode84;

    /// @brief Undocumented keycode 85.
    const char keyCode85;

    /// @brief Undocumented keycode 86.
    const char keyCode86;

    /// @brief Key function 11.
    /// @enum [KEY_F11]
    const char f11;

    /// @brief Key function 12.
    /// @enum [KEY_F12]
    const char f12;
} div_keyboard_t;

// ============================================================================
// Description of some basic DIV archives (for modifying them once loaded)
// ============================================================================

/// @brief DIV FPG file header length.
#define DIV_FPG_FILE_HEADER_LENGTH 8

/// @brief DIV FPG file palette length.
#define DIV_FPG_PALETTE_LENGTH 768

/// @brief DIV FPG file color range total count.
#define DIV_FPG_COLOR_RANGE_COUNT 16

/// @brief DIV FPG file color range data length.
#define DIV_FPG_COLOR_RANGE_DATA_LENGTH 36

/// @brief DIV file color ranges total length.
#define DIV_FPG_COLOR_RANGES_LENGTH (DIV_FPG_COLOR_RANGE_COUNT * DIV_FPG_COLOR_RANGE_DATA_LENGTH)

/// @brief DIV FPG file header.
typedef struct _FPGHEADER
{
    /// @brief File header.
    char header[DIV_FPG_FILE_HEADER_LENGTH];
    /// @brief Palette colors.
    char palette[DIV_FPG_PALETTE_LENGTH];
    /// @brief Color ranges.
    char colorRanges[DIV_FPG_COLOR_RANGES_LENGTH]; // colorbars
} div_fpg_file_header_t;

/// @brief DIV FPG file map description max length.
#define DIV_FPG_BODY_DESCRIPTION_MAX_LENGTH 32

/// @brief DIV FPG file map filename max length.
#define DIV_FPG_BODY_FILENAME_MAX_LENGTH 12

/**
 * @brief DIV FPG file graphic map metadata.
 * @remarks This struct only contains the metadata information. Control points and graphic data are excluded. To read these data use the follow map in the strict order after the metadata:
 * ```
 * short *controlPoints; // 2 short units x total number of control points.
 * char *graphic; // width x height.
 * ```
 */
typedef struct _FPGBODY
{
    /// @brief Graphic code.
    int code;
    /// @brief Graphic size.
    int lenght;
    /// @brief Graphic description.
    char description[DIV_FPG_BODY_DESCRIPTION_MAX_LENGTH];
    /// @brief Graphic filename.
    char filename[DIV_FPG_BODY_FILENAME_MAX_LENGTH];
    /// @brief Graphic width.
    int width; // wide
    /// @brief Graphic height.
    int height;
    /// @brief Number of control points defined in the graphic.
    int controlPointsCount; // number_of_points
} div_fpg_file_map_metadata_t;

/// @brief DIV FNT file header length.
#define DIV_FNT_FILE_HEADER_LENGHT 8

/// @brief DIV FNT file header.
typedef struct _FNTHEADER
{
    /// @brief File header.
    char header[DIV_FNT_FILE_HEADER_LENGHT];
} div_font_file_header_t;

/// @brief DIV FNT character metadata.
typedef struct _FNTBODY
{
    /// @brief Character width.
    int width; // wide
    /// @brief Character height.
    int height;
    /// @brief Character screen offset.
    int screenOffset; // screen_offset
    /// @brief Graphic data offset in the file.
    int fileOffset; // file_offset
} div_font_file_character_metadata_t;

// ============================================================================
// DIV exported functions
// ============================================================================

/**
 * @brief DIV version of stdlib.h malloc function.
 * @param size Size in bytes to allocate.
 * @returns Returns a pointer to the new allocated memory region.
 * @remarks You must use this function instead of stdlib.h version, otherwise, the program will be crash.
 */
void *malloc(const size_t size);

/**
 * @brief DIV version of stdlib.h free function.
 * @param ptr Pointer to memory region to release.
 * @remarks You must use this function instead of stdlib.h version, otherwise, the program will be crash.
 */
void free(void *ptr);

/**
 * @brief DIV version of stdio.h fopen function.
 * @param filename Filename to create.
 * @param mode File mode creation.
 * @returns Returns a [FILE] pointer for the new created file, [NULL] otherwise.
 * @remarks You must use this function instead of stdio.h version, otherwise, the program will be crash.otherwise.
 */
FILE *fopen(const char *filename, const char *mode);

/**
 * @brief DIV version of stdio.h fclose function.
 * @param file Pointer to the file to close.
 * @returns Returns 0 if the file is successfully closed. It returns [EOF] (typically -1) if an error occurs while closing the file.
 * @remarks You must use this function instead of stdio.h version, otherwise, the program will be crash.
 */
int fclose(FILE *file);

/**
 * @brief DIV runtime random number.
 * @param min Min value.
 * @param max Max value.
 * @returns Returns a random value between [min] and [max] values, both included.
 * @remarks This function used the seed managed from DIV runtime using rand_seed() DIV function.
 */
int divRand(const int min, const int max);

/**
 * @brief DIV print text on screen.
 * @param text Text to render in screen.
 * @param x X coordinate.
 * @param x Y coordinate.
 * @remarks This method allow to print text on screen using a default 10pt font with white color (or the nearest color in current palette).
 *
 * IMPORTANT: Call this method only from post_process_buffer() DIV callback. Otherwise, the program will be crash.
 */
void divPrint(const char *text, const int x, const int y);

// ============================================================================
// DIV functions to interact with DIV language functions from C
// ============================================================================

/**
 * @brief Reads DIV function parameter as int value.
 * @returns Returns the next function parameter in the stack as int value.
 * @remarks Remember that parameters are readed from a stack, from last to first.
 */
int divReadIntParameter();

/**
 * @brief Reads DIV function parameter as string value.
 * @returns Returns the next function parameter in the stack as char pointer value.
 * @remarks Remember that parameters are readed from a stack, from last to first.
 */
char *divReadStringParameter();

/**
 * @brief Reads DIV function parameter as struct value.
 * @returns Returns the next function parameter in the stack as void pointer value.
 * @remarks Remember that parameters are readed from a stack, from last to first.
 */
void *divReadStructParameter();

/**
 * @brief Returns DIV function value.
 * @param value Value returned to DIV function.
 * @remarks This functions must be called always to end a DIV function scope (returns zero for no value to return).
 */
void divReturn(const int value);

#endif
