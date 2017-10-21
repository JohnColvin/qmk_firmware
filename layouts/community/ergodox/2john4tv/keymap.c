// #include "ergodox.h"
#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#include "keymap_german.h"

#include "keymap_nordic.h"



enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = KEYMAP(KC_TRANSPARENT,KC_1,KC_2,KC_3,KC_4,KC_5,KC_TRANSPARENT,KC_DELETE,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_TRANSPARENT,LT(1,KC_ESCAPE),LT(2,KC_A),KC_S,KC_D,KC_F,KC_G,KC_LPRN,CTL_T(KC_Z),ALT_T(KC_X),GUI_T(KC_C),KC_V,KC_B,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_GRAVE,KC_LBRACKET,KC_RBRACKET,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_BSPACE,SFT_T(KC_TAB),TT(2),KC_TRANSPARENT,KC_6,KC_7,KC_8,KC_9,KC_0,KC_TRANSPARENT,KC_TRANSPARENT,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSLASH,KC_H,KC_J,KC_K,KC_L,LT(2,KC_SCOLON),LT(1,KC_QUOTE),KC_TRANSPARENT,KC_N,KC_M,RGUI_T(KC_COMMA),ALGR_T(KC_DOT),CTL_T(KC_SLASH),KC_RPRN,KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,TT(1),SFT_T(KC_ENTER),KC_SPACE),

  [1] = KEYMAP(KC_TRANSPARENT,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_TRANSPARENT,KC_TRANSPARENT,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_PIPE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_EQUAL,KC_MINUS,KC_UNDS,KC_GRAVE,KC_LCBR,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_TILD,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_BSPACE,KC_LSHIFT,TT(2),KC_TRANSPARENT,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_TRANSPARENT,KC_EQUAL,KC_7,KC_8,KC_9,KC_ASTR,KC_F12,KC_KP_DOT,KC_4,KC_5,KC_6,KC_PLUS,KC_TRANSPARENT,KC_TRANSPARENT,KC_0,KC_1,KC_2,KC_3,KC_BSLASH,KC_RCBR,KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,TO(0),SFT_T(KC_ENTER),KC_SPACE),

  [2] = KEYMAP(KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_ACCEL0,KC_MS_ACCEL1,KC_MS_ACCEL2,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_WH_DOWN,KC_MS_UP,KC_MS_WH_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_TRANSPARENT,KC_LBRACKET,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,TO(0),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_SYSTEM_SLEEP,KC_TRANSPARENT,KC_MEDIA_PLAY_PAUSE,KC_AUDIO_MUTE,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_F14,KC_F15,KC_MS_BTN1,KC_MS_BTN2,KC_TRANSPARENT,KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT,KC_RBRACKET,KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_WWW_BACK),

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;

  }
  return true;
}

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

};
