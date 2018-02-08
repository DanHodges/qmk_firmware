#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

enum custom_keycodes
{
  SHRUG = SAFE_RANGE,
  DIASPORA,
  EPRM,
  VRSN,
  RGB_SLD,
};

//**************** Definitions needed for quad function to work *********************//
//Enums used to clearly convey the state of the tap dance
enum
{
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
};

typedef struct
{
  bool is_press_action;
  int state;
} tap;

int cur_dance(qk_tap_dance_state_t *state)
{
  if (state->count == 1)
  {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted || state->pressed == 0)
      return SINGLE_TAP;
    else
      return SINGLE_HOLD;
  }
  else
    return 6; //magic number. At some point this method will expand to work for more presses
}

//**************** Definitions needed for quad function to work *********************//

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap super_shift_state = {
    .is_press_action = true,
    .state = 0};

void super_shift_finished(qk_tap_dance_state_t *state, void *user_data)
{
  super_shift_state.state = cur_dance(state);
  switch (super_shift_state.state)
  {
  case SINGLE_TAP:
    set_oneshot_layer(1, ONESHOT_START);
    break;
  case SINGLE_HOLD:
    register_code(KC_LGUI);
    break;
  }
}

void super_shift_reset(qk_tap_dance_state_t *state, void *user_data)
{
  switch (super_shift_state.state)
  {
  case SINGLE_TAP:
    clear_oneshot_layer_state(ONESHOT_PRESSED);
    break;
  case SINGLE_HOLD:
    unregister_code(KC_LGUI);
    break;
  }
  super_shift_state.state = 0;
}

enum
{
  SUPER_SHIFT = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [SUPER_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, super_shift_finished, super_shift_reset)};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = KEYMAP(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LBRACKET,
        LT(3, KC_TAB), KC_Q, KC_W, KC_F, KC_P, KC_G, KC_LCBR,
        CTL_T(KC_ESCAPE), KC_A, KC_R, KC_S, KC_T, KC_D,
        OSL(1), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LPRN,
        TT(2), TG(3), KC_LSHIFT, KC_LCTL, KC_LALT,
        LALT(LGUI(KC_LEFT)), LALT(LGUI(KC_DOWN)),
        LALT(LGUI(KC_F)),
        TD(SUPER_SHIFT), KC_BSPACE, LGUI(KC_SPACE),

        KC_RBRACKET, KC_6, KC_7, KC_8, KC_9, KC_0, KC_KP_MINUS,
        KC_RCBR, KC_J, KC_L, KC_U, KC_Y, KC_SCOLON, KC_BSLASH,
        KC_H, KC_N, KC_E, KC_I, KC_O, RCTL_T(KC_QUOTE),
        KC_RPRN, KC_K, KC_M, KC_COMMA, KC_DOT, LT(2, KC_SLASH), OSL(1),
        KC_EQUAL, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
        LALT(LGUI(KC_UP)), LALT(LGUI(KC_RIGHT)),
        LGUI(KC_GRAVE),
        KC_DELETE, KC_ENTER, ALL_T(KC_SPACE)),

    [1] = KEYMAP(
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_LBRACKET,
        LSFT(KC_TAB), LSFT(KC_Q), LSFT(KC_W), LSFT(KC_F), LSFT(KC_P), LSFT(KC_G), KC_LCBR,
        KC_TRANSPARENT, LSFT(KC_A), LSFT(KC_R), LSFT(KC_S), LSFT(KC_T), LSFT(KC_D),
        KC_TRANSPARENT, LSFT(KC_Z), LSFT(KC_X), LSFT(KC_C), LSFT(KC_V), LSFT(KC_B),
        KC_LPRN, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LSFT(KC_LCTL), LSFT(KC_LALT),
        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        KC_RBRACKET, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
        KC_RCBR, LSFT(KC_J), LSFT(KC_L), LSFT(KC_U), LSFT(KC_Y), LSFT(KC_SCOLON), KC_PIPE,
        LSFT(KC_H), LSFT(KC_N), LSFT(KC_E), LSFT(KC_I), LSFT(KC_O), KC_DQUO,
        KC_RPRN, LSFT(KC_K), LSFT(KC_M), KC_LABK, KC_RABK, KC_QUES, KC_TRANSPARENT,
        KC_PLUS, LSFT(KC_LEFT), LSFT(KC_DOWN), LSFT(KC_UP), LSFT(KC_RIGHT),
        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, LSFT(KC_ENTER), LSFT(KC_SPACE)),

    [2] = KEYMAP(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, DIASPORA,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_F13, KC_F14, KC_F15, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT, KC_F10, KC_F11, KC_F12, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_F7, KC_F8, KC_F9, KC_TRANSPARENT, KC_TRANSPARENT,
        SHRUG, KC_F4, KC_F5, KC_F6, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_F1, KC_F2, KC_F3, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),

    [3] = KEYMAP(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_WH_LEFT, KC_MS_WH_UP, KC_MS_WH_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_MS_WH_DOWN, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
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

  case SHRUG:
    if (record->event.pressed)
    {
      SEND_STRING(SS_LCTRL("`") SS_LALT("00AF") SS_LALT("005C") SS_LALT("005F") SS_LALT("0028") SS_LALT("30C4") SS_LALT("0029") SS_LALT("005F") SS_LALT("002F") SS_LALT("00AF") SS_LCTRL("`"));
    }
    return false;
    break;

  case DIASPORA:
    if (record->event.pressed)
    {
      SEND_STRING(SS_LCTRL("`") SS_LALT("03B4") SS_LALT("03B9") SS_LALT("03B1") SS_LALT("03C3") SS_LALT("03C0") SS_LALT("03BF") SS_LALT("03C1") SS_LALT("03AC") SS_LCTRL("`"));
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
