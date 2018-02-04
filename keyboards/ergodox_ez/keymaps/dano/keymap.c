#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

enum custom_keycodes
{
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = KEYMAP(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LBRACKET,
        LT(3, KC_TAB), KC_Q, KC_W, KC_F, KC_P, KC_G, KC_LCBR,
        CTL_T(KC_ESCAPE), KC_A, KC_R, KC_S, KC_T, KC_D,
        OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LPRN,
        TT(1), KC_LSHIFT, OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI),
        LALT(LGUI(KC_LEFT)), LALT(LGUI(KC_DOWN)),
        LALT(LGUI(KC_F)),
        GUI_T(KC_BSPACE), TT(2), LGUI(KC_SPACE),

        KC_RBRACKET, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSLASH,
        KC_RCBR, KC_J, KC_L, KC_U, KC_Y, KC_SCOLON, KC_MINUS,
        KC_H, KC_N, KC_E, KC_I, KC_O, RCTL_T(KC_QUOTE),
        KC_RPRN, KC_K, KC_M, KC_COMMA, KC_DOT, KC_SLASH, OSM(MOD_RSFT),
        KC_EQUAL, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
        LALT(LGUI(KC_UP)), LALT(LGUI(KC_RIGHT)),
        LGUI(KC_GRAVE),
        KC_DELETE, KC_ENTER, GUI_T(KC_SPACE)),

    [1] = KEYMAP(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_F14, KC_F15, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT, KC_F10, KC_F11, KC_F12, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_F7, KC_F8, KC_F9, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_F4, KC_F5, KC_F6, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_F1, KC_F2, KC_F3, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),

    [2] = KEYMAP(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_AMPR, KC_KP_ASTERISK, KC_EQUAL, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_DLR, KC_PERC, KC_CIRC, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_EXLM, KC_AT, KC_HASH, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_PIPE,
        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_7, KC_8, KC_9, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_KP_4, KC_KP_5, KC_KP_6, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_1, KC_KP_2, KC_KP_3, KC_TRANSPARENT, TO(1),
        KC_KP_0, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TAB),

    [3] = KEYMAP(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(1)};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch (id)
  {
  case 0:
    if (record->event.pressed)
    {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    break;
  }
  return MACRO_NONE;
};

void matrix_init_user(void)
{
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  // dynamically generate these.
  case EPRM:
    if (record->event.pressed)
    {
      eeconfig_init();
    }
    return false;
    break;
  case VRSN:
    if (record->event.pressed)
    {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    return false;
    break;
  case RGB_SLD:
    if (record->event.pressed)
    {
      rgblight_mode(1);
    }
    return false;
    break;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state)
{

  uint8_t layer = biton32(state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer)
  {
  case 0:
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
    break;
  case 1:
    ergodox_right_led_1_on();
#ifdef RGBLIGHT_COLOR_LAYER_1
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
#endif
    break;
  case 2:
    ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_2
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
#endif
    break;
  case 3:
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_3
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
#endif
    break;
  case 4:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_4
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
#endif
    break;
  case 5:
    ergodox_right_led_1_on();
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_5
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
#endif
    break;
  case 6:
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_6
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
#endif
    break;
  case 7:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_7
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
#endif
    break;
  default:
    break;
  }
  return state;
};
