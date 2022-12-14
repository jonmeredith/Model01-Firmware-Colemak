
// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
// #include "Kaleidoscope-LED-ActiveLayerColor.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-HardwareTestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for Qukeys -- quantum keys
#include <Kaleidoscope-Qukeys.h>

// Support for TOPSY - inverts shift for a key
#include <Kaleidoscope-TopsyTurvy.h>

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using XXX to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */




  // Define an EGA palette. Conveniently, that's exactly 16 colors, just like the
 #define C_BLACK    CRGB(0x00, 0x00, 0x00)
 #define C_BLUE    CRGB(0x00, 0x00, 0xaa)
 #define C_GREEN    CRGB(0x00, 0xaa, 0x00)
 #define C_CYAN    CRGB(0x00, 0xaa, 0xaa)
 #define C_RED   CRGB(0xaa, 0x00, 0x00)
 #define C_MAGENTA    CRGB(0xaa, 0x00, 0xaa)
 #define C_BROWN    CRGB(0xaa, 0x55, 0x00)
 #define C_LGRAY    CRGB(0xaa, 0xaa, 0xaa)
 #define C_DGRAY    CRGB(0x55, 0x55, 0x55)
 #define C_BBLUE    CRGB(0x55, 0x55, 0xff)
 #define C_BGREEN    CRGB(0x55, 0xff, 0x55)
 #define C_BCYAN    CRGB(0x55, 0xff, 0xff)
 #define C_BRED    CRGB(0xff, 0x55, 0x55)
 #define C_BMAGENTA    CRGB(0xff, 0x55, 0xff)
 #define C_YELLOW    CRGB(0xff, 0xff, 0x55)
 #define C_WHITE    CRGB(0xff, 0xff, 0xff)

static const cRGB LAYER_COLORMAP[] PROGMEM = {
   C_BLACK, C_BLACK, C_WHITE, C_WHITE, C_RED, C_BLUE, C_GREEN, C_YELLOW, C_CYAN, C_MAGENTA };
enum { PRIMARY, COLEMAKDH, LSEL, RSEL, FUN, NUM, SYM, NAV, MOUSE, WM }; // layers


/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

#define Key_CopyShortcut  LGUI(Key_C)
#define Key_CutShortcut   LGUI(Key_X)
#define Key_PasteShortcut LGUI(Key_V)

#define Key_Undo LGUI(Key_Z)
#define Key_Redo LGUI(LSHIFT(Key_Z))

#define Key_AppWindowShortcut LCTRL(Key_DownArrow)
#define Key_ShowDesktopShortcut Key_F11

KEYMAPS(

  [PRIMARY] = KEYMAP_STACKED
  (XXX,          Key_1, Key_2, Key_3, Key_4, Key_5, LockLayer(FUN),
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, LockLayer(NUM),
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, LockLayer(SYM),
   Key_Delete,   Key_Backspace, Key_LShift, Key_Tab,
   ShiftToLayer(LSEL),

   LockLayer(WM),    Key_6, Key_7, Key_8,     Key_9,         Key_0,         XXX,
   LockLayer(NAV),   Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                     Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   LockLayer(MOUSE), Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_Enter,     Key_RShift, Key_Spacebar, Key_Escape,
   ShiftToLayer(RSEL)),

  [COLEMAKDH] = KEYMAP_STACKED
  (XXX,          Key_1, Key_2, Key_3, Key_4, Key_5, LockLayer(FUN),
   Key_Backtick, Key_Q, Key_W, Key_F, Key_P, Key_B, LockLayer(NUM),
   Key_PageUp,   Key_A, Key_R, Key_S, Key_T, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_D, Key_V, LockLayer(SYM),
   Key_Delete,   Key_Backspace, Key_LShift, Key_Tab,
   ShiftToLayer(LSEL),

   MoveToLayer(PRIMARY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         XXX,
   Key_Enter,     Key_J, Key_L, Key_U,     Key_Y,         Key_Semicolon, Key_Equals,
                  Key_M, Key_N, Key_E,     Key_I,         Key_O,         Key_Quote,
   ___,  Key_K, Key_H, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_Enter,     Key_RShift, Key_Spacebar, Key_Escape,
   ShiftToLayer(RSEL)),
  
  [LSEL] = KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, Key_LeftGui, Key_LeftAlt, Key_LeftControl, Key_LeftShift, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ShiftToLayer(WM), ShiftToLayer(NAV), ShiftToLayer(MOUSE), ___,
   ___,

   ___,  ___, ___, ___, ___, ___, ___,
   ___,  ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___,
   ___,  ___, ___, ___, ___, ___, ___,
   ___,  ___, ___, ___,
   ___),

  [RSEL] = KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___,  ___, ___, ___, ___, ___, ___,
   ___,  ___, ___, ___, ___, ___, ___,
         ___, Key_RightShift, Key_RightControl, Key_RightAlt, Key_RightGui, ___, // 6 - middle
   ___,  ___, ___, ___, ___, ___, ___,
   ___,  ShiftToLayer(SYM), ShiftToLayer(NUM), ShiftToLayer(FUN),
   ___),  
 
  [FUN] = KEYMAP_STACKED
  (XXX, Key_1,   Key_2,  Key_3,  Key_4,  Key_5,           ___, // 7
   XXX, Key_F12, Key_F7, Key_F8, Key_F9, Key_PrintScreen, XXX, // 7 - top
   XXX, Key_F11, Key_F4, Key_F5, Key_F6, Key_ScrollLock,       // 6 - middle
   XXX, Key_F10, Key_F1, Key_F2, Key_F3, Key_Pause,       XXX, // 7 - bottom
   Key_LeftGui, Key_Space, Key_Tab, XXX,
   XXX,

   XXX, Key_6, Key_7,         Key_8,            Key_9,        Key_0,        XXX, // 7
   XXX, XXX,  XXX,            XXX,              XXX,          XXX,          XXX, // 7 - top
        XXX,  Key_RightShift, Key_RightControl, Key_RightAlt, Key_RightGui, XXX, // 6 - middle
   XXX, XXX,  XXX,            XXX,              XXX,          XXX,          XXX, // 7 - bottom
   XXX, Key_Enter, Key_Spacebar, Key_Escape,
   XXX),

  [NUM] = KEYMAP_STACKED
  (XXX, Key_1,           Key_2, Key_3, Key_4, Key_5,           XXX, // 7
   XXX, Key_LeftBracket, Key_7, Key_8, Key_9, Key_RightBracket, ___, // 7 - top
   XXX, Key_Semicolon,   Key_4, Key_5, Key_6, Key_Equals,       // 6 - middle
   XXX, Key_Backtick,    Key_1, Key_2, Key_3, Key_Backslash,       XXX, // 7 - bottom
   Key_Period, Key_0, Key_Minus, XXX,
   XXX,

   XXX, Key_6, Key_7,         Key_8,            Key_9,        Key_0,        XXX, // 7
   XXX, XXX,  XXX,            XXX,              XXX,          XXX,          XXX, // 7 - top
        XXX,  Key_RightShift, Key_RightControl, Key_RightAlt, Key_RightGui, XXX, // 6 - middle
   XXX, XXX,  XXX,            XXX,              XXX,          XXX,          XXX, // 7 - bottom
   XXX, Key_Escape, Key_Spacebar, Key_Enter,
   XXX),

  [SYM] = KEYMAP_STACKED
  (XXX, Key_1,           Key_2, Key_3, Key_4, Key_5,           XXX, // 7
   XXX, TOPSY(LeftBracket), TOPSY(7), TOPSY(8), TOPSY(9), TOPSY(RightBracket), XXX, // 7 - top
   XXX, TOPSY(Semicolon),   TOPSY(4), TOPSY(5), TOPSY(6), TOPSY(Equals),       // 6 - middle
   XXX, TOPSY(Backtick),    TOPSY(1), TOPSY(2), TOPSY(3), TOPSY(Backslash), ___, // 7 - bottom
   Key_LeftParen, Key_RightParen, TOPSY(Minus), XXX,
   XXX,

   XXX, Key_6, Key_7,         Key_8,            Key_9,        Key_0,        XXX, // 7
   XXX, XXX,  XXX,            XXX,              XXX,          XXX,          XXX, // 7 - top
        XXX,  Key_RightShift, Key_RightControl, Key_RightAlt, Key_RightGui, XXX, // 6 - middle
   XXX, XXX,  XXX,            XXX,              XXX,          XXX,          XXX, // 7 - bottom
   XXX, Key_Enter, Key_Spacebar, Key_Escape,
   XXX),

  [NAV] = KEYMAP_STACKED
  (XXX,          Key_1, Key_2, Key_3, Key_4, Key_5, XXX,
   Key_Backtick, Key_Q, Key_W, Key_F, Key_P, Key_B, XXX,
   Key_PageUp,   Key_LeftGui, Key_LeftAlt, Key_LeftControl, Key_LeftShift, Key_LFN2,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_D, Key_V, XXX,
   Key_Delete,   Key_Backspace, Key_Tab, XXX,
   XXX,

   XXX,  Key_6, Key_7, Key_8,     Key_9,         Key_0,         XXX,
   ___,     Key_Redo, Key_PasteShortcut, Key_CopyShortcut,  Key_CutShortcut,         Key_Undo, Key_Equals,
                  Key_CapsLock, Key_LeftArrow, Key_DownArrow, Key_UpArrow, Key_RightArrow, Key_Quote,
   XXX,  Key_Insert,   Key_Home,      Key_PageDown,  Key_PageUp,  Key_End,        Key_Minus,
   XXX,           Key_Escape, Key_Spacebar, Key_Enter,
   XXX),

  [MOUSE] = KEYMAP_STACKED
  (XXX,          Key_1, Key_2, Key_3, Key_4, Key_5, XXX,
   Key_Backtick, Key_Q, Key_W, Key_F, Key_P, Key_B, XXX,
   Key_PageUp,   Key_LeftGui, Key_LeftAlt, Key_LeftControl, Key_LeftShift, Key_LFN2,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_D, Key_V, XXX,
   Key_Delete,   Key_Backspace, Key_Tab, XXX,
   XXX,

   XXX,  Key_6, Key_7, Key_8,     Key_9,         Key_0,         XXX,
   XXX,     Key_Redo, Key_PasteShortcut, Key_CopyShortcut,     Key_CutShortcut,         Key_Undo, Key_Equals,
                  Key_CapsLock, Key_mouseL, Key_mouseDn, Key_mouseUp, Key_mouseR, Key_Quote,
   ___,  Key_Insert,   Key_mouseScrollL,      Key_mouseScrollDn,  Key_mouseScrollUp,  Key_mouseScrollR,        Key_Minus,
   XXX,           Key_mouseBtnL, Key_mouseBtnL, Key_mouseBtnM,
   XXX),

  [WM] = KEYMAP_STACKED
  (XXX,          Key_1, Key_2, Key_3, Key_4, Key_5, XXX,
   Key_Backtick, Key_Q, Key_W, Key_F, Key_P, Key_B, XXX,
   Key_PageUp,   Key_LeftGui, Key_LeftAlt, Key_LeftControl, Key_LeftShift, Key_LFN2,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_D, Key_V, XXX,
   Key_Delete,   Key_Backspace, Key_Tab, XXX,
   XXX,

   ___,  Key_6, Key_7, Key_8,     Key_9,         Key_0,         XXX,
   XXX,      Consumer_VolumeDecrement, Consumer_VolumeIncrement, Key_CopyShortcut,     Key_CutShortcut,         Key_Undo, Key_Equals,
                  XXX, Key_Tab, Key_Backtick, Key_LeftBracket, Key_RightBracket, Key_Quote,
   XXX,  Key_Insert,   Key_Home,      Key_PageDown,  Key_PageUp,  Key_End,        Key_Minus,
   XXX,           Key_Escape, Key_Spacebar, Key_Enter,
   XXX),

  /*

  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___,  ___, ___, ___, ___, ___, ___,
   ___,  ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___,
   ___,  ___, ___, ___, ___, ___, ___,
   ___,  ___, ___, ___,
   ___),
  */
  

) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {

  switch (macro_id) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(event.state);
    break;

  }

  return MACRO_NONE;
}

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 01's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE,
  // Enter test mode
  COMBO_ENTER_TEST_MODE
};

/** Wrappers, to be used by MagicCombo. **/

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/**
 *  This enters the hardware test mode
 */
static void enterHardwareTestMode(uint8_t combo_index) {
  HardwareTestMode.runTests();
}

/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = { R3C6, R2C6, R3C7 }
}, {
  .action = enterHardwareTestMode,
  // Left Fn + Prog + LED
  .keys = { R3C6, R0C0, R0C6 }
});

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,
  
  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The boot greeting effect pulses the LED button for 10 seconds after the
  // keyboard is first connected
  BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  HardwareTestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,
  //LEDActiveLayerColorEffect,

  // The macros plugin adds support for macros
  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // TopsyTurvy - invert shift keys
  TopsyTurvy,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {

  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
  //LEDActiveLayerColorEffect.setColormap(layerColormap);

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for five layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command, or by using the
  // `keymap.onlyCustom` command to use EEPROM layers only.
  EEPROMKeymap.setup(5);
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
