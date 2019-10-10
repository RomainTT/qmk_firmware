// An Ergodox EZ keymap meant to be used with a bépo layout (FR ergonomic
// layout, dvorak style). 
//
// See the README.md file for an image of this keymap.

#include QMK_KEYBOARD_H
#include "keymap_bepo.h"

// The layers that we are defining for this keyboards.
#define BASE 0
#define FN 1
#define NUM 2

// Set only one tap for TT keys
#define TAPPING_TOGGLE 1

// Decrease value of tapping timeout to be able to have a rapid hold
#undef TAPPING_TERM
#define TAPPING_TERM 100

// The Tap Dance identifiers, used in the TD keycode and tap_dance_actions array.
#define TAP_MACRO 0

// A 'transparent' key code (that falls back to the layers below it).
#define ___ KC_TRANSPARENT

// A 'blocking' key code. Does nothing but prevent falling back to another layer.
#define XXX KC_NO

// Some combined keys (one normal keycode when tapped and one modifier or layer
// toggle when held).
#define CCED_RCTL    MT(MOD_RCTL, BP_CCED)        // CCED and Ctrl when hold
#define W_LCTL       MT(MOD_LCTL, BP_W)           // W and Ctrl when hold
#define M_SFT        MT(MOD_RSFT, BP_M)			  // M and right shift when hold
#define SFT_LCK      MT(MOD_LSFT, KC_CAPSLOCK)    // Caps lock and shift when hold
#define CTRL_ALT     MT(MOD_LCTL | MOD_LALT, KC_NO) // CTRL + ALT when hold
#define CTRL_B		 RCTL(BP_B) 				  // CTRL + B once

// The most portable copy/paste keys (windows (mostly), linux, and some terminal emulators).
#define MK_CUT    LSFT(KC_DEL)  // shift + delete
#define MK_COPY   LCTL(KC_INS)  // ctrl + insert
#define MK_PASTE  LSFT(KC_INS)  // shift + insert

// Custom keycodes
enum {
  // SAFE_RANGE must be used to tag the first element of the enum.
  // DYNAMIC_MACRO_RANGE must always be the last element of the enum if other
  // values are added (as its value is used to create a couple of other keycodes
  // after it.
  DYNAMIC_MACRO_RANGE = SAFE_RANGE,
};

// This file must be included after DYNAMIC_MACRO_RANGE is defined...
#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Layer 0: basic keys.
  [BASE] = LAYOUT_ergodox(
    /* left hand */
    BP_DLR,   BP_DQOT, BP_LGIL, BP_RGIL, BP_LPRN, BP_RPRN, ___,
    KC_TAB,   BP_B,    BP_ECUT, BP_P,    BP_O,    BP_EGRV, KC_ESC,
    SFT_LCK,  BP_A,    BP_U,    BP_I,    BP_E,    BP_COMM,
    W_LCTL,   BP_ECRC, BP_AGRV, BP_Y,    BP_X,    BP_DOT,  BP_K,
    TT(FN),   CTRL_ALT,KC_LGUI, KC_LALT, KC_RALT,
                                                          TT(NUM),  KC_PSCR,
                                                                    ___,
                                                  KC_ENT, CTRL_B,   ___,
    /* right hand */
        BP_PERC, BP_AT,   BP_PLUS,  BP_MINS, BP_SLSH,     BP_ASTR, BP_EQL,
        KC_BSPC, BP_DCRC, BP_V,     BP_D,    BP_L,        BP_J,    BP_Z,
                 BP_C,    BP_T,     BP_S,    BP_R,        BP_N,    M_SFT,
        KC_DEL,  BP_APOS, BP_Q,     BP_G,    BP_H,        BP_F,    CCED_RCTL,
                          KC_RALT,  KC_LALT,  KC_RGUI,    CTRL_ALT,TT(FN),
    KC_AUDIO_VOL_UP, TD(TAP_MACRO),
    KC_AUDIO_MUTE,
    KC_AUDIO_VOL_DOWN, ___, KC_SPC),

  // Layer 1: function and media keys.
  [FN] = LAYOUT_ergodox(
    /* left hand */
    KC_SLEP, KC_F1, KC_F2,  KC_F3,   KC_F4,    KC_F5,    ___,
    ___,     ___,   ___,    ___,     ___,      ___,      ___,
    ___,     ___,   ___,    ___,     ___,      ___,
    ___,     ___,   MK_CUT, MK_COPY, MK_PASTE, ___,      ___,
    ___,     ___,   ___,    ___,     ___,
                                                     ___, ___,
                                                          ___,
                                             ___,    ___, ___,
    /* right hand */
        ___, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,
        ___, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   ___,     KC_F12,
             KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, ___,     ___,
        ___, ___,     ___,     ___,     ___,      ___,     ___,
                      ___,     ___,     ___,      ___,     ___,
    ___, ___,
    ___,
    ___, ___,    ___),

  // Layer 2: Numeric keypad 
  [NUM] = LAYOUT_ergodox(
    /* left hand */
    ___,     ___,    ___,    ___,     ___,      ___, ___,
    ___,     ___,    ___,    ___,     ___,      ___, ___,
    ___,     ___,    ___,    ___,     ___,      ___,
    ___,     ___,    ___,    ___,     ___,      ___, ___,
    ___,     ___,    ___,    ___,     ___,
                                              ___, ___,
                                                   ___,
                                         ___, ___, ___,
    /* right hand */
         ___,   ___,   KC_PPLS, KC_PMNS, KC_PSLS,    ___,     ___,
         ___,   ___,   KC_P7,   KC_P8,   KC_P9,      KC_PEQL, ___,
                ___,   KC_P4,   KC_P5,   KC_P6,      ___,     ___,
         ___,   ___,   KC_P1,   KC_P2,   KC_P3,      ___,     ___,
                       ___,     KC_P0,   KC_KP_DOT,  ___,     ___,
    ___, ___,
    ___,
    ___, ___, ___),

};

// Whether the macro 1 is currently being recorded.
static bool is_macro1_recording = false;

// The current set of active layers (as a bitmask).
// There is a global 'layer_state' variable but it is set after the call
// to layer_state_set_user().
static uint32_t current_layer_state = 0;
uint32_t layer_state_set_user(uint32_t state);

// Method called at the end of the tap dance on the TAP_MACRO key. That key is
// used to start recording a macro (double tap or more), to stop recording (any
// number of tap), or to play the recorded macro (1 tap).
void macro_tapdance_fn(qk_tap_dance_state_t *state, void *user_data) {
  uint16_t keycode;
  keyrecord_t record;
  dprintf("macro_tap_dance_fn %d\n", state->count);
  if (is_macro1_recording) {
    keycode = DYN_REC_STOP;
    is_macro1_recording = false;
    layer_state_set_user(current_layer_state);
  } else if (state->count == 1) {
    keycode = DYN_MACRO_PLAY1;
  } else {
    keycode = DYN_REC_START1;
    is_macro1_recording = true;
    layer_state_set_user(current_layer_state);
  }

  record.event.pressed = true;
  process_record_dynamic_macro(keycode, &record);
  record.event.pressed = false;
  process_record_dynamic_macro(keycode, &record);
}

// The definition of the tap dance actions:
qk_tap_dance_action_t tap_dance_actions[] = {
  // This Tap dance plays the macro 1 on TAP and records it on double tap.
  [TAP_MACRO] = ACTION_TAP_DANCE_FN(macro_tapdance_fn),
};

// Runs for each key down or up event.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode != TD(TAP_MACRO)) {
    // That key is processed by the macro_tapdance_fn. Not ignoring it here is
    // mostly a no-op except that it is recorded in the macros (and uses space).
    // We can't just return false when the key is a tap dance, because
    // process_record_user, is called before the tap dance processing (and
    // returning false would eat the tap dance).
    if (!process_record_dynamic_macro(keycode, record)) {
      return false;
    }
  }

  return true; // Let QMK send the enter press/release events
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// The state of the LEDs requested by the system, as a bitmask.
static uint8_t sys_led_state = 0;

// Use these masks to read the system LEDs state.
static const uint8_t sys_led_mask_num_lock = 1 << USB_LED_NUM_LOCK;
static const uint8_t sys_led_mask_caps_lock = 1 << USB_LED_CAPS_LOCK;
static const uint8_t sys_led_mask_scroll_lock = 1 << USB_LED_SCROLL_LOCK;

// Value to use to switch LEDs on. The default value of 255 is far too bright.
static const uint8_t max_led_value = 50;

// Whether the given layer (one of the constant defined at the top) is active.
#define LAYER_ON(layer) (current_layer_state & (1<<layer))

void led_1_on(void) {
  ergodox_right_led_1_on();
  ergodox_right_led_1_set(max_led_value);
}

void led_2_on(void) {
  ergodox_right_led_2_on();
  ergodox_right_led_2_set(max_led_value);
}

void led_3_on(void) {
  ergodox_right_led_3_on();
  ergodox_right_led_3_set(max_led_value);
}

void led_1_off(void) {
  ergodox_right_led_1_off();
}

void led_2_off(void) {
  ergodox_right_led_2_off();
}

void led_3_off(void) {
  ergodox_right_led_3_off();
}

// The following functions change the purpose of the leds, instead of being
// NUM-pad/CAPS/SCROLL-lock, leds now represent CAPS/FN-layer/NUM-layer

// Called when the computer wants to change the state of the keyboard LEDs.
void led_set_user(uint8_t usb_led) {
  sys_led_state = usb_led;
  if (sys_led_state & sys_led_mask_caps_lock) {
    led_1_on();
  } else {
    led_1_off();
  }
}

uint32_t layer_state_set_user(uint32_t state) {
  current_layer_state = state;

  if (is_macro1_recording) {
    led_1_on();
    led_2_on();
    led_3_on();
    return state;
  }

  if (LAYER_ON(FN)) {
    led_2_on();
  } else {
    led_2_off();
  }

  if (LAYER_ON(NUM)) {
    // enable NUMLOCK if it is not
	if (!(sys_led_state & sys_led_mask_num_lock)) {
	  register_code(KC_NUMLOCK);
	  unregister_code(KC_NUMLOCK);	
	}
	led_3_on();
  } else {
    led_3_off();
  }

  led_set_user(sys_led_state);
 
  return state;
};
