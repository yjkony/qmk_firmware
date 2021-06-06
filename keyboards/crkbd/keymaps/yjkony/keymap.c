/*
Copyright 2021 Yuji Konishi
*/

#include QMK_KEYBOARD_H

// Mac key code
#define MKC_MUTE 0x7f
#define MKC_SDUP 0x81
#define MKC_SDDW 0x80

// カスタムキー処理
enum custom_keycodes {
    FN_LNMO13 = SAFE_RANGE,
    FN_MO23,
    FN_ESCGUI,
    FN_ESCALT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
    // ,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    // |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    // |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSPC,
    // |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           FN_ESCALT,FN_ESCGUI,KC_SPC,    KC_ENT, FN_LNMO13,FN_MO23
    //                                     `--------------------------'  `--------------------------'
    ),

    [1] = LAYOUT_split_3x6_3(
    // ,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS,
    // |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_COLN, XXXXXXX,
    // |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                       KC_F11,  KC_F12,  KC_COMM, KC_DOT,  KC_SLSH, KC_BSPC,
    // |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______, _______, _______
    //                                     `--------------------------'  `--------------------------'
    ),

    [2] = LAYOUT_split_3x6_3(
    // ,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS,
    // |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
    // |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                       KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
    // |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______, _______, _______
    //                                     `--------------------------'  `--------------------------'
    ),

    [3] = LAYOUT_split_3x6_3(
    // ,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, XXXXXXX, MKC_MUTE,MKC_SDUP,MKC_SDDW,XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, DEBUG,   RESET,   EEP_RST,
    // |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                      XXXXXXX, RGB_M_P, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,                      XXXXXXX, RGB_M_TW,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______, _______, _______
    //                                     `--------------------------'  `--------------------------'
    )
};

#ifdef OLED_DRIVER_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}
#endif // OLED_DRIVER_ENABLE


/** キー処理のカスタマイズ **/
static bool lang_state = false;
static bool lang_pressed = false;
static uint16_t lang_pressed_time = 0;
static bool esc_pressed = false;
static uint16_t esc_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef OLED_DRIVER_ENABLE
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    #endif  // OLED_DRIVER_ENABLE

    switch (keycode) {
        case FN_LNMO13:
            if (record->event.pressed) {
                lang_pressed = true;
                lang_pressed_time = record->event.time;

                layer_on(1);
                update_tri_layer(1, 2, 3);
            } else {
                layer_off(1);
                update_tri_layer(1, 2, 3);

                if (lang_pressed && (TIMER_DIFF_16(record->event.time, lang_pressed_time) < TAPPING_TERM)) {
                    if (lang_state) {
                        tap_code16(KC_LANG2);
                        lang_state = false;
                    } else {
                        tap_code16(KC_LANG1);
                        lang_state = true;
                    }
                    // tap_code16(LGUI(KC_SPC));
                }
                lang_pressed = false;
            }
            return false;
            break;

        case FN_MO23:
            if (record->event.pressed) {
                layer_on(2);
                update_tri_layer(1, 2, 3);
            } else {
                layer_off(2);
                update_tri_layer(1, 2, 3);
            }
            return false;
            break;

        case FN_ESCGUI:
            if (record->event.pressed) {
                esc_pressed = true;
                esc_pressed_time = record->event.time;
                register_code(KC_LGUI);
            } else {
                unregister_code(KC_LGUI);
                if (esc_pressed && (TIMER_DIFF_16(record->event.time, esc_pressed_time) < TAPPING_TERM)) {
                    tap_code(KC_ESC);
                }
                esc_pressed = false;
            }
            return false;

        case FN_ESCALT:
            if (record->event.pressed) {
                esc_pressed = true;
                esc_pressed_time = record->event.time;
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
                if (esc_pressed && (TIMER_DIFF_16(record->event.time, esc_pressed_time) < TAPPING_TERM)) {
                    tap_code(KC_ESC);
                }
                esc_pressed = false;
            }
            return false;

        default:
            if (record->event.pressed) {
                // reset the flags
                lang_pressed = false;
                esc_pressed = false;
            }
            break;
    }

    return true;
}

/** 初期化後処理 **/
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_disable();
}
