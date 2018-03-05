#include "mitosis.h"
#include "eeconfig.h"

enum mitosis_keycodes {
  MACSLEEP = SAFE_RANGE
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // LETTERS
  [0] = {
    {_______,     KC_W,        KC_F,          KC_P,       _______,     _______,          KC_L,       KC_U,         KC_Y,         _______      },
    {LT(6,KC_A),  LT(2,KC_R),  LT(8,KC_S),    LT(3,KC_T), KC_D,        KC_H,             LT(7,KC_N), LT(8,KC_E),   LT(2,KC_I),   LT(4,KC_O)   },
    {CTL_T(KC_Z), ALT_T(KC_X), GUI_T(KC_C),   KC_G,       KC_B,        KC_K,             LT(5,KC_M), RGUI_T(KC_J), ALGR_T(KC_Q), RCTL_T(KC_V) },
    {XXXXXXX,     _______,     _______,       _______,    _______,     _______,          _______,    _______,      _______,      XXXXXXX      },
    {XXXXXXX,     _______,     SFT_T(KC_TAB), KC_BSPACE,  TT(1),       SFT_T(KC_ESCAPE), KC_ENTER,   KC_SPACE,     KC_F5,        XXXXXXX      }
  },

  // MOUSE & MEDIA
  [1] = {
    {RESET,          KC_MS_WH_UP, KC_MS_UP,   KC_MS_WH_DOWN, _______,           _______, KC_AUDIO_MUTE,       KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP,     MACSLEEP },
    {KC_MS_WH_RIGHT, KC_MS_LEFT,  KC_MS_DOWN, KC_MS_RIGHT,   KC_MS_WH_LEFT,     _______, KC_MS_BTN1,          KC_MS_BTN2,          KC_F14,              KC_F15   },
    {_______,        _______,     _______,    _______,       _______,           _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, _______  },
    {XXXXXXX,        _______,     _______,    _______,       _______,           _______, _______,             _______,             _______,             XXXXXXX  },
    {XXXXXXX,        _______,     _______,    _______,       _______,           _______, _______,             _______,             _______,             XXXXXXX  }
  },

  // PARENS & BRACKETS
  [2] = {
    {_______,  _______, _______,     _______,     _______,      _______, _______, _______, _______, _______  },
    {KC_DQUO,  _______, KC_LPRN,     KC_RPRN,     _______,      _______, KC_LCBR, KC_RCBR, _______, KC_QUOTE },
    {_______,  _______, KC_LBRACKET, KC_RBRACKET, _______,      _______, KC_LABK, KC_RABK, _______, _______  },
    {XXXXXXX,  _______, _______,     _______,     _______,      _______, _______, _______, _______, XXXXXXX  },
    {XXXXXXX,  _______, _______,     _______,     _______,      _______, _______, _______, _______, XXXXXXX  }
  },

  // MODS & ARROWS
  [3] = {
    {_______, _______, _______, _______, _______,     _______, _______, _______, _______, _______  },
    {KC_LCTL, KC_LALT, KC_LGUI, _______, _______,     _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT },
    {_______, _______, _______, _______, _______,     _______, _______, _______, _______, _______  },
    {XXXXXXX, _______, _______, _______, _______,     _______, _______, _______, _______, XXXXXXX  },
    {XXXXXXX, _______, _______, _______, _______,     _______, _______, _______, _______, XXXXXXX  }
  },

  // COPY/PASTE
  [4] = {
    {_______,    _______,    _______,    _______,    _______,     LGUI(KC_Q), _______, _______, _______, LGUI(KC_W) },
    {LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), _______,     _______,    _______, _______, _______, _______    },
    {_______,    _______,    _______,    _______,    _______,     _______,    _______, _______, _______, _______    },
    {XXXXXXX,    _______,    _______,    _______,    _______,     _______,    _______, _______, _______, XXXXXXX    },
    {XXXXXXX,    _______,    _______,    _______,    _______,     _______,    _______, _______, _______, XXXXXXX    }
  },

  // NUMBERS
  [5] = {
    {_______, _______, _______, _______, _______,     _______, _______, _______, _______, _______ },
    {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        _______, _______, _______, _______, _______ },
    {KC_6,    KC_7,    KC_8,    KC_9,    KC_0,        _______, _______, _______, _______, _______ },
    {XXXXXXX, _______, _______, _______, _______,     _______, _______, _______, _______, XXXXXXX },
    {XXXXXXX, _______, _______, _______, _______,     _______, _______, _______, _______, XXXXXXX }
  },

  // MATH
  [6] = {
    {_______,  _______, _______,  _______, _______,     _______, _______, _______, _______,   _______  },
    {_______, KC_EQUAL, KC_MINUS, KC_UNDS, _______,     _______, KC_PLUS, KC_ASTR, KC_BSLASH, KC_SLASH },
    {_______, _______,  _______,  _______, _______,     _______, _______, _______, _______,   _______  },
    {XXXXXXX, _______,  _______,  _______, _______,     _______, _______, _______, _______,   XXXXXXX  },
    {XXXXXXX, _______,  _______,  _______, _______,     _______, _______, _______, _______,   XXXXXXX  }
  },

  // SYMBOLS
  [7] = {
    {_______,  _______, _______,  _______, _______,     _______, _______, _______, _______, _______ },
    {KC_EXLM,  KC_AT,   KC_HASH,  KC_DLR,  _______,     _______, _______, KC_PERC, KC_CIRC, KC_AMPR },
    {_______, _______,  _______,  _______, _______,     _______, _______, _______, _______, _______ },
    {XXXXXXX, _______,  _______,  _______, _______,     _______, _______, _______, _______, XXXXXXX },
    {XXXXXXX, _______,  _______,  _______, _______,     _______, _______, _______, _______, XXXXXXX }
  },

  // PUNCTUATION
  [8] = {
    {_______,  _______, _______,  _______,   _______,     _______, _______, _______, _______,  _______ },
    {KC_GRAVE, KC_COLN, _______,  KC_SCOLON, _______,     _______, KC_DOT,  _______, KC_COMMA, KC_QUES },
    {_______, _______,  _______,  KC_TILD,   _______,     _______, KC_PIPE, _______, _______,  _______ },
    {XXXXXXX, _______,  _______,  _______,   _______,     _______, _______, _______, _______,  XXXXXXX },
    {XXXXXXX, _______,  _______,  _______,   _______,     _______, _______, _______, _______,  XXXXXXX }
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MACSLEEP:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        register_code(KC_RCTL);
        register_code(KC_POWER);
        unregister_code(KC_POWER);
        unregister_code(KC_RCTL);
        unregister_code(KC_RSFT);
      }
      return false;
      break;

    default:
      return true;
  }
};

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  switch (layer) {
    case 1:
      set_led_green;
      break;
    default:
      set_led_off;
      break;
  }
};
