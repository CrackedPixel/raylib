/**********************************************************************************************
*
*   rcore_desktop_glfw - Functions to manage window, graphics device and inputs
*
*   PLATFORM: DESKTOP: GLFW
*       - Windows (Win32, Win64)
*       - Linux (X11/Wayland desktop mode)
*       - FreeBSD, OpenBSD, NetBSD, DragonFly (X11 desktop)
*       - OSX/macOS (x64, arm64)
*
*   LIMITATIONS:
*       - Limitation 01
*       - Limitation 02
*
*   POSSIBLE IMPROVEMENTS:
*       - Improvement 01
*       - Improvement 02
*
*   ADDITIONAL NOTES:
*       - TRACELOG() function is located in raylib [utils] module
*
*   CONFIGURATION:
*       #define RCORE_PLATFORM_CUSTOM_FLAG
*           Custom flag for rcore on target platform -not used-
*
*   DEPENDENCIES:
*       - rglfw: Manage graphic device, OpenGL context and inputs (Windows, Linux, OSX/macOS, FreeBSD...)
*       - gestures: Gestures system for touch-ready devices (or simulated from mouse inputs)
*
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2013-2025 Ramon Santamaria (@raysan5) and contributors
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include <stddef.h>  // Required for: size_t

// #define KEY_A RAYLIB_KEY_A
// #define KEY_B RAYLIB_KEY_B
// #define KEY_R RAYLIB_KEY_R
// #define KEY_L RAYLIB_KEY_L
// #define KEY_X RAYLIB_KEY_X
// #define KEY_Y RAYLIB_KEY_Y

// #define KEY_UP RAYLIB_KEY_UP
// #define KEY_DOWN RAYLIB_KEY_DOWN
// #define KEY_LEFT RAYLIB_KEY_LEFT
// #define KEY_RIGHT RAYLIB_KEY_RIGHT

#define TICKS_PER_SEC 268123480.0

#include "3ds.h"
#include <GL/picaGL.h>

// #undef KEY_A
// #undef KEY_B
// #undef KEY_R
// #undef KEY_L
// #undef KEY_X
// #undef KEY_Y
// #undef KEY_UP
// #undef KEY_DOWN
// #undef KEY_LEFT
// #undef KEY_RIGHT

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct {
    void* handle;
    Result romfs;
    int currentScreen;
} PlatformData;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
extern CoreData CORE;                   // Global CORE state context

static PlatformData platform = { 0 };   // Platform specific data

//----------------------------------------------------------------------------------
// Module Internal Functions Declaration
//----------------------------------------------------------------------------------
int InitPlatform(void);          // Initialize platform (graphics, inputs and more)
void ClosePlatform(void);        // Close platform

// Error callback event
static void ErrorCallback(int error, const char *description);                             // GLFW3 Error Callback, runs on GLFW3 error

// Input callbacks events
// static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods); // GLFW3 Keyboard Callback, runs on key pressed
// static void CharCallback(GLFWwindow *window, unsigned int codepoint);                   // GLFW3 Char Callback, runs on key pressed (get codepoint value)
// static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);  // GLFW3 Mouse Button Callback, runs on mouse button pressed
// static void MouseCursorPosCallback(GLFWwindow *window, double x, double y);             // GLFW3 Cursor Position Callback, runs on mouse move
// static void MouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset);    // GLFW3 Scrolling Callback, runs on mouse wheel
// static void CursorEnterCallback(GLFWwindow *window, int enter);                         // GLFW3 Cursor Enter Callback, cursor enters client area
// static void JoystickCallback(int jid, int event);                                       // GLFW3 Joystick Connected/Disconnected Callback

// Memory allocator wrappers [used by glfwInitAllocator()]
static void *AllocateWrapper(size_t size, void *user);                                  // GLFW3 GLFWallocatefun, wrapps around RL_CALLOC macro
static void *ReallocateWrapper(void *block, size_t size, void *user);                   // GLFW3 GLFWreallocatefun, wrapps around RL_REALLOC macro
static void DeallocateWrapper(void *block, void *user);                                 // GLFW3 GLFWdeallocatefun, wraps around RL_FREE macro

// static void SetDimensionsFromMonitor(GLFWmonitor *monitor);     // Set screen dimensions from monitor/display dimensions

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
// NOTE: Functions declaration is provided by raylib.h

//----------------------------------------------------------------------------------
// Module Functions Definition: Window and Graphics Device
//----------------------------------------------------------------------------------

// Check if application should close
// NOTE: By default, if KEY_ESCAPE pressed or window close icon clicked
bool WindowShouldClose(void)
{
    if (CORE.Window.ready) return !aptMainLoop();
    
    return true;
}

// Toggle fullscreen mode
void ToggleFullscreen(void)
{
    TRACELOG(LOG_WARNING, "ToggleFullscreen() not implemented on target platform");
}

// Toggle borderless windowed mode
void ToggleBorderlessWindowed(void)
{
    TRACELOG(LOG_WARNING, "ToggleBorderlessWindowed() not implemented on target platform");
}

// Set window state: maximized, if resizable
void MaximizeWindow(void)
{
    TRACELOG(LOG_WARNING, "MaximizeWindow() not implemented on target platform");
}

// Set window state: minimized
void MinimizeWindow(void)
{
    TRACELOG(LOG_WARNING, "MinimizeWindow() not implemented on target platform");
}

// Restore window from being minimized/maximized
void RestoreWindow(void)
{
    TRACELOG(LOG_WARNING, "RestoreWindow() not implemented on target platform");
}

// Set window configuration state using flags
void SetWindowState(unsigned int flags)
{
    TRACELOG(LOG_WARNING, "SetWindowState() not implemented on target platform");
}

// Clear window configuration state flags
void ClearWindowState(unsigned int flags)
{
    TRACELOG(LOG_WARNING, "ClearWindowState() not implemented on target platform");
}

void SetWindowIcon(Image image)
{
    TRACELOG(LOG_WARNING, "SetWindowIcon() not implemented on target platform");
}

void SetWindowIcons(Image *images, int count)
{
    TRACELOG(LOG_WARNING, "SetWindowIcons() not implemented on target platform");
}

// Set title for window
void SetWindowTitle(const char *title)
{
    CORE.Window.title = title;
}

// Set window position on screen (windowed mode)
void SetWindowPosition(int x, int y)
{
    CORE.Window.position.x = x;
    CORE.Window.position.y = y;
}

// Set monitor for the current window
void SetWindowMonitor(int monitor)
{
    TRACELOG(LOG_WARNING, "SetWindowMonitor() not implemented on target platform");
}

// Set window minimum dimensions (FLAG_WINDOW_RESIZABLE)
void SetWindowMinSize(int width, int height)
{
    CORE.Window.screenMin.width = width;
    CORE.Window.screenMin.height = height;
}

// Set window maximum dimensions (FLAG_WINDOW_RESIZABLE)
void SetWindowMaxSize(int width, int height)
{
    CORE.Window.screenMax.width = width;
    CORE.Window.screenMax.height = height;
}

// Set window dimensions
void SetWindowSize(int width, int height)
{
    CORE.Window.screen.width = width;
    CORE.Window.screen.height = height;
}

// Set window opacity, value opacity is between 0.0 and 1.0
void SetWindowOpacity(float opacity)
{
    TRACELOG(LOG_WARNING, "SetWindowOpacity() not implemented on target platform");
}

// Set window focused
void SetWindowFocused(void)
{
    TRACELOG(LOG_WARNING, "SetWindowFocused() not implemented on target platform");
}

// Get native window handle
void *GetWindowHandle(void)
{
    TRACELOG(LOG_WARNING, "SetWindowMonitor() not implemented on target platform");
    return NULL;
}

// Get number of monitors
int GetMonitorCount(void)
{
    TRACELOG(LOG_WARNING, "GetMonitorCount() not implemented on target platform");
    return 1;
}

// Get current monitor where window is placed
int GetCurrentMonitor(void)
{
    TRACELOG(LOG_WARNING, "GetCurrentMonitor() not implemented on target platform");
    return 0;
}

// Get selected monitor position
Vector2 GetMonitorPosition(int monitor)
{
    TRACELOG(LOG_WARNING, "GetMonitorPosition() not implemented on target platform");
    return (Vector2){ 0, 0 };
}

// Get selected monitor width (currently used by monitor)
int GetMonitorWidth(int monitor)
{
    TRACELOG(LOG_WARNING, "GetMonitorWidth() not implemented on target platform");
    return 0;
}

// Get selected monitor height (currently used by monitor)
int GetMonitorHeight(int monitor)
{
    TRACELOG(LOG_WARNING, "GetMonitorHeight() not implemented on target platform");
    return 0;
}

// Get selected monitor physical width in millimetres
int GetMonitorPhysicalWidth(int monitor)
{
    TRACELOG(LOG_WARNING, "GetMonitorPhysicalWidth() not implemented on target platform");
    return 0;
}

// Get selected monitor physical height in millimetres
int GetMonitorPhysicalHeight(int monitor)
{
    TRACELOG(LOG_WARNING, "GetMonitorPhysicalHeight() not implemented on target platform");
    return 0;
}

// Get selected monitor refresh rate
int GetMonitorRefreshRate(int monitor)
{
    TRACELOG(LOG_WARNING, "GetMonitorRefreshRate() not implemented on target platform");
    return 0;
}

// Get the human-readable, UTF-8 encoded name of the selected monitor
const char *GetMonitorName(int monitor)
{
    TRACELOG(LOG_WARNING, "GetMonitorName() not implemented on target platform");
    return "";
}

// Get window position XY on monitor
Vector2 GetWindowPosition(void)
{
    int x = 0;
    int y = 0;

    TRACELOG(LOG_WARNING, "GetWindowPosition() not implemented on target platform");

    return (Vector2){ (float)x, (float)y };
}

// Get window scale DPI factor for current monitor
Vector2 GetWindowScaleDPI(void)
{
    Vector2 scale = { 1 };

    TRACELOG(LOG_WARNING, "GetWindowScaleDPI() not implemented on target platform");

    return scale;
}

// Set clipboard text content
void SetClipboardText(const char *text)
{
    // TODO: ??
    TRACELOG(LOG_WARNING, "SetClipboardText() not implemented on target platform");
}

// Get clipboard text content
// NOTE: returned string is allocated and freed by GLFW
const char *GetClipboardText(void)
{
    // TODO: ??
    TRACELOG(LOG_WARNING, "GetClipboardText() not implemented on target platform");
    return NULL;
}

// Get clipboard image
Image GetClipboardImage(void)
{
    Image image = { 0 };

    TRACELOG(LOG_WARNING, "GetClipboardImage() not implemented on target platform");

    return image;
}

// Show mouse cursor
void ShowCursor(void)
{
    TRACELOG(LOG_WARNING, "ShowCursor() not implemented on target platform");
}

// Hides mouse cursor
void HideCursor(void)
{
    TRACELOG(LOG_WARNING, "HideCursor() not implemented on target platform");
}

// Enables cursor (unlock cursor)
void EnableCursor(void)
{
    TRACELOG(LOG_WARNING, "EnableCursor() not implemented on target platform");
}

// Disables cursor (lock cursor)
void DisableCursor(void)
{
    TRACELOG(LOG_WARNING, "DisableCursor() not implemented on target platform");
}

// Swap back buffer with front buffer (screen drawing)
void SwapScreenBuffer(void)
{
    pglSwapBuffers();

    if (platform.currentScreen == 0) {
        // CORE.Window.screen.width = 400;
        // CORE.Window.screen.height = 240;
        // CORE.Window.currentFbo.width = CORE.Window.screen.width;
        // CORE.Window.currentFbo.height = CORE.Window.screen.height;
        // rlglInit(CORE.Window.currentFbo.width, CORE.Window.currentFbo.height);
        // SetupViewport(400, 240);
        // pglSelectScreen(GFX_TOP, GFX_LEFT);
    } else {
        // CORE.Window.screen.width = 320;
        // CORE.Window.screen.height = 240;
        // CORE.Window.currentFbo.width = CORE.Window.screen.width;
        // CORE.Window.currentFbo.height = CORE.Window.screen.height;
        // rlglInit(CORE.Window.currentFbo.width, CORE.Window.currentFbo.height);
        // SetupViewport(320, 240);
        // pglSelectScreen(GFX_BOTTOM, GFX_LEFT);
    }
}

void SelectDisplayScreen(int screenId) {
    if (platform.currentScreen == screenId) {
        return;
    }

    // glFlush();
    // glFinish();
    pglSwapBuffers();

    if (platform.currentScreen == 0) {
        // glFlush();
        // pglSwapBuffers();
        printf("changing to bottom screen\n");

        // CORE.Window.screen.width = 320;
        // CORE.Window.screen.height = 240;
        // CORE.Window.currentFbo.width = CORE.Window.screen.width;
        // CORE.Window.currentFbo.height = CORE.Window.screen.height;
        // rlglInit(CORE.Window.currentFbo.width, CORE.Window.currentFbo.height);
        // SetupViewport(320, 240);
        pglSelectScreen(GFX_BOTTOM, GFX_LEFT);
        platform.currentScreen = 1;
    } else {
        // glFlush();
        // pglSwapBuffers();

        printf("changing to top screen\n");
        // CORE.Window.screen.width = 400;
        // CORE.Window.screen.height = 240;
        // CORE.Window.currentFbo.width = CORE.Window.screen.width;
        // CORE.Window.currentFbo.height = CORE.Window.screen.height;
        // rlglInit(CORE.Window.currentFbo.width, CORE.Window.currentFbo.height);
        // SetupViewport(400, 240);
        pglSelectScreen(GFX_TOP, GFX_RIGHT);
        platform.currentScreen = 0;
    }
}

//----------------------------------------------------------------------------------
// Module Functions Definition: Misc
//----------------------------------------------------------------------------------

static inline double u64_to_double(u64 value) {
    return (((double)(u32)(value >> 32))*0x100000000ULL+(u32)value);
}

// Get elapsed time measure in seconds since InitTimer()
double GetTime(void)
{
    uint64_t time = svcGetSystemTick();
    return u64_to_double(time - CORE.Time.base) / TICKS_PER_SEC;
}

// Open URL with default system browser (if available)
// NOTE: This function is only safe to use if you control the URL given
// A user could craft a malicious string performing another action
// Only call this function yourself not with user input or make sure to check the string yourself
// Ref: https://github.com/raysan5/raylib/issues/686
void OpenURL(const char *url)
{
    // Security check to (partially) avoid malicious code
    if (strchr(url, '\'') != NULL) TRACELOG(LOG_WARNING, "SYSTEM: Provided URL could be potentially malicious, avoid [\'] character");
    else
    {
        TRACELOG(LOG_WARNING, "OpenURL() not implemented on target platform");
        // char *cmd = (char *)RL_CALLOC(strlen(url) + 32, sizeof(char));

        // sprintf(cmd, "xdg-open '%s'", url); // Alternatives: firefox, x-www-browser

        // int result = system(cmd);
        // if (result == -1) TRACELOG(LOG_WARNING, "OpenURL() child process could not be created");
        // RL_FREE(cmd);
    }
}

//----------------------------------------------------------------------------------
// Module Functions Definition: Inputs
//----------------------------------------------------------------------------------

// Set internal gamepad mappings
int SetGamepadMappings(const char *mappings)
{
    TRACELOG(LOG_WARNING, "SetGamepadMappings() not implemented on target platform");
    return 0;
}

// Set gamepad vibration
void SetGamepadVibration(int gamepad, float leftMotor, float rightMotor, float duration)
{
    TRACELOG(LOG_WARNING, "SetGamepadVibration() not available on target platform");
}

// Set mouse position XY
void SetMousePosition(int x, int y)
{
    TRACELOG(LOG_WARNING, "SetMousePosition() not implemented on target platform");
}

// Set mouse cursor
void SetMouseCursor(int cursor)
{
    TRACELOG(LOG_WARNING, "SetMouseCursor() not implemented on target platform");
}

// Get physical key name
const char *GetKeyName(int key)
{
    TRACELOG(LOG_WARNING, "GetKeyName() not implemented on target platform");
    return NULL;
}

// Register all input events
void PollInputEvents(void)
{
    
    // Reset keys/chars pressed registered
    CORE.Input.Keyboard.keyPressedQueueCount = 0;
    CORE.Input.Keyboard.charPressedQueueCount = 0;

    // Reset last gamepad button/axis registered state
    CORE.Input.Gamepad.lastButtonPressed = 0;       // GAMEPAD_BUTTON_UNKNOWN
    //CORE.Input.Gamepad.axisCount = 0;

    // Keyboard/Mouse input polling (automatically managed by GLFW3 through callback)

    // Register previous keys states
    for (int i = 0; i < MAX_KEYBOARD_KEYS; i++)
    {
        CORE.Input.Keyboard.previousKeyState[i] = CORE.Input.Keyboard.currentKeyState[i];
        CORE.Input.Keyboard.keyRepeatInFrame[i] = 0;
    }

    // Register previous mouse states
    for (int i = 0; i < MAX_MOUSE_BUTTONS; i++) CORE.Input.Mouse.previousButtonState[i] = CORE.Input.Mouse.currentButtonState[i];

    // Register previous mouse wheel state
    CORE.Input.Mouse.previousWheelMove = CORE.Input.Mouse.currentWheelMove;
    CORE.Input.Mouse.currentWheelMove = (Vector2){ 0.0f, 0.0f };

    // Register previous mouse position
    CORE.Input.Mouse.previousPosition = CORE.Input.Mouse.currentPosition;

    // Register previous touch states
    for (int i = 0; i < MAX_TOUCH_POINTS; i++) CORE.Input.Touch.previousTouchState[i] = CORE.Input.Touch.currentTouchState[i];

    // Reset touch positions
    for (int i = 0; i < MAX_TOUCH_POINTS; i++) CORE.Input.Touch.position[i] = (Vector2){ 0, 0 };

    CORE.Input.Touch.position[0] = CORE.Input.Mouse.currentPosition;

    CORE.Window.resizedLastFrame = false;

    hidScanInput();
    u32 kDown = hidKeysDown();
    u32 kUp = hidKeysUp();
    for (int i = 0; i < 64; ++i) {
        if (kDown & (1 << i)) {
            CORE.Input.Keyboard.currentKeyState[i] = 1;
        }

        if (kUp & (1 << i)) {
            CORE.Input.Keyboard.currentKeyState[i] = 0;
        }
    }

    // either d-pad or c-pad
    CORE.Input.Keyboard.currentKeyState[DS_KEY_UP] = (CORE.Input.Keyboard.currentKeyState[DS_KEY_DUP] || CORE.Input.Keyboard.currentKeyState[DS_KEY_CPAD_UP]);
    CORE.Input.Keyboard.currentKeyState[DS_KEY_DOWN] = (CORE.Input.Keyboard.currentKeyState[DS_KEY_DDOWN] || CORE.Input.Keyboard.currentKeyState[DS_KEY_CPAD_DOWN]);
    CORE.Input.Keyboard.currentKeyState[DS_KEY_LEFT] = (CORE.Input.Keyboard.currentKeyState[DS_KEY_DLEFT] || CORE.Input.Keyboard.currentKeyState[DS_KEY_CPAD_LEFT]);
    CORE.Input.Keyboard.currentKeyState[DS_KEY_RIGHT] = (CORE.Input.Keyboard.currentKeyState[DS_KEY_DRIGHT] || CORE.Input.Keyboard.currentKeyState[DS_KEY_CPAD_RIGHT]);
}

//----------------------------------------------------------------------------------
// Module Internal Functions Definition
//----------------------------------------------------------------------------------
// Function wrappers around RL_*alloc macros, used by glfwInitAllocator() inside of InitPlatform()
// We need to provide these because GLFWallocator expects function pointers with specific signatures
// Similar wrappers exist in utils.c but we cannot reuse them here due to declaration mismatch
// https://www.glfw.org/docs/latest/intro_guide.html#init_allocator
static void *AllocateWrapper(size_t size, void *user)
{
    (void)user;
    return RL_CALLOC(size, 1);
}
static void *ReallocateWrapper(void *block, size_t size, void *user)
{
    (void)user;
    return RL_REALLOC(block, size);
}
static void DeallocateWrapper(void *block, void *user)
{
    (void)user;
    RL_FREE(block);
}

// Initialize platform: graphics, inputs and more
int InitPlatform(void)
{
    gfxInitDefault();
    pglInit();
    hidInit();

    consoleInit(GFX_BOTTOM, NULL);

    platform.romfs = romfsInit();
    if (platform.romfs) TRACELOG(LOG_WARNING, "ROMFS failed to load! Err:%08lX", platform.romfs);

    platform.currentScreen = 0;

    CORE.Window.ready = true;
    //----------------------------------------------------------------------------
    // Initialize timming system
    //----------------------------------------------------------------------------
    InitTimer();
    //----------------------------------------------------------------------------
    // Initialize storage system
    //----------------------------------------------------------------------------
    CORE.Storage.basePath = GetWorkingDirectory();
    //----------------------------------------------------------------------------

    TRACELOG(LOG_INFO, "PLATFORM: 3DS: Initialized successfully");

    return 0;
}

// Close platform
void ClosePlatform(void)
{
    if (platform.romfs) {
        romfsExit();
    }
    pglExit();
    gfxExit();
}

// GLFW3 Error Callback, runs on GLFW3 error
static void ErrorCallback(int error, const char *description)
{
    TRACELOG(LOG_WARNING, "3DS: Error: %i Description: %s", error, description);
}

#if 0
// GLFW3 Keyboard Callback, runs on key pressed
static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // TODO: convert to 3DS
    if (key < 0) return;    // Security check, macOS fn key generates -1

    // WARNING: GLFW could return GLFW_REPEAT, we need to consider it as 1
    // to work properly with our implementation (IsKeyDown/IsKeyUp checks)
    if (action == GLFW_RELEASE) CORE.Input.Keyboard.currentKeyState[key] = 0;
    else if (action == GLFW_PRESS) CORE.Input.Keyboard.currentKeyState[key] = 1;
    else if (action == GLFW_REPEAT) CORE.Input.Keyboard.keyRepeatInFrame[key] = 1;

    // WARNING: Check if CAPS/NUM key modifiers are enabled and force down state for those keys
    if (((key == KEY_CAPS_LOCK) && ((mods & GLFW_MOD_CAPS_LOCK) > 0)) ||
        ((key == KEY_NUM_LOCK) && ((mods & GLFW_MOD_NUM_LOCK) > 0))) CORE.Input.Keyboard.currentKeyState[key] = 1;

    // Check if there is space available in the key queue
    if ((CORE.Input.Keyboard.keyPressedQueueCount < MAX_KEY_PRESSED_QUEUE) && (action == GLFW_PRESS))
    {
        // Add character to the queue
        CORE.Input.Keyboard.keyPressedQueue[CORE.Input.Keyboard.keyPressedQueueCount] = key;
        CORE.Input.Keyboard.keyPressedQueueCount++;
    }

    // Check the exit key to set close window
    if ((key == CORE.Input.Keyboard.exitKey) && (action == GLFW_PRESS)) glfwSetWindowShouldClose(platform.handle, GLFW_TRUE);
}

// GLFW3 Char Callback, get unicode codepoint value
static void CharCallback(GLFWwindow *window, unsigned int codepoint)
{
    // TODO: convert to 3ds
    // NOTE: Registers any key down considering OS keyboard layout but
    // does not detect action events, those should be managed by user...
    // Ref: https://github.com/glfw/glfw/issues/668#issuecomment-166794907
    // Ref: https://www.glfw.org/docs/latest/input_guide.html#input_char

    // Check if there is space available in the queue
    if (CORE.Input.Keyboard.charPressedQueueCount < MAX_CHAR_PRESSED_QUEUE)
    {
        // Add character to the queue
        CORE.Input.Keyboard.charPressedQueue[CORE.Input.Keyboard.charPressedQueueCount] = codepoint;
        CORE.Input.Keyboard.charPressedQueueCount++;
    }
}

// GLFW3 Mouse Button Callback, runs on mouse button pressed
static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    // TODO: convert to 3ds
    // WARNING: GLFW could only return GLFW_PRESS (1) or GLFW_RELEASE (0) for now,
    // but future releases may add more actions (i.e. GLFW_REPEAT)
    CORE.Input.Mouse.currentButtonState[button] = action;
    CORE.Input.Touch.currentTouchState[button] = action;
}

// GLFW3 Cursor Position Callback, runs on mouse move
static void MouseCursorPosCallback(GLFWwindow *window, double x, double y)
{
    // TODO: convert to 3ds
    CORE.Input.Mouse.currentPosition.x = (float)x;
    CORE.Input.Mouse.currentPosition.y = (float)y;
    CORE.Input.Touch.position[0] = CORE.Input.Mouse.currentPosition;
}

// GLFW3 Scrolling Callback, runs on mouse wheel
static void MouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    TRACELOG(LOG_WARNING, "MouseScrollCallback() not implemented on target platform");
}

// GLFW3 CursorEnter Callback, when cursor enters the window
static void CursorEnterCallback(GLFWwindow *window, int enter)
{
    TRACELOG(LOG_WARNING, "CursorEnterCallback() not implemented on target platform");
}

// GLFW3 Joystick Connected/Disconnected Callback
static void JoystickCallback(int jid, int event)
{
    TRACELOG(LOG_WARNING, "JoystickCallback() not implemented on target platform");
}
#endif

// Set screen dimensions from monitor/display dimensions
// static void SetDimensionsFromMonitor(GLFWmonitor *monitor)
// {
//     TRACELOG(LOG_WARNING, "SetDimensionsFromMonitor() not implemented on target platform");
// }

// EOF


//bool WindowShouldClose(void)
//void ToggleFullscreen(void)
//void ToggleBorderlessWindowed(void)
//void MaximizeWindow(void)
//void MinimizeWindow(void)
//void RestoreWindow(void)

//void SetWindowState(unsigned int flags)
//void ClearWindowState(unsigned int flags)

//void SetWindowIcon(Image image)
//void SetWindowIcons(Image *images, int count)
//void SetWindowTitle(const char *title)
//void SetWindowPosition(int x, int y)
//void SetWindowMonitor(int monitor)
//void SetWindowMinSize(int width, int height)
//void SetWindowMaxSize(int width, int height)
//void SetWindowSize(int width, int height)
//void SetWindowOpacity(float opacity)
//void SetWindowFocused(void)
//void *GetWindowHandle(void)
//Vector2 GetWindowPosition(void)
//Vector2 GetWindowScaleDPI(void)

//int GetMonitorCount(void)
//int GetCurrentMonitor(void)
//int GetMonitorWidth(int monitor)
//int GetMonitorHeight(int monitor)
//int GetMonitorPhysicalWidth(int monitor)
//int GetMonitorPhysicalHeight(int monitor)
//int GetMonitorRefreshRate(int monitor)
//Vector2 GetMonitorPosition(int monitor)
//const char *GetMonitorName(int monitor)

//void SetClipboardText(const char *text)
//const char *GetClipboardText(void)

//void ShowCursor(void)
//void HideCursor(void)
//void EnableCursor(void)
//void DisableCursor(void)
