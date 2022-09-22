/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include <stdio.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
    MT(MOD_LGUI, KC_ESC),   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,        KC_O,    KC_P,    MT(MOD_RGUI, KC_LBRC),
    LCTL_T(KC_TAB),         KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,        KC_L,    KC_SCLN, MT(MOD_RCTL, KC_QUOT),
    KC_LALT,                KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM,     KC_DOT,  KC_SLSH, KC_RBRC,
                   LT(1, KC_BSPACE), LSFT_T(KC_SPACE), LT(2, KC_ENTER),      LT(2, KC_ENTER), RSFT_T(KC_SPACE), LT(1, KC_DELETE)
  ),

  [1] = LAYOUT_split_3x6_3(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,        KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, KC_F12,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
    KC_LALT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_INS,
                       KC_TRNS, KC_TRNS, LT(3, KC_ENTER),      LT(3, KC_ENTER), KC_TRNS, KC_TRNS
  ),

  [2] = LAYOUT_split_3x6_3(
      KC_GRAVE, KC_PSLS, KC_P7,   KC_P8,   KC_P9,  KC_PMNS,      KC_EQL,  KC_HOME, KC_UP,    KC_PGUP, KC_MPRV,   KC_LGUI,
     _______,  KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,      KC_VOLU, KC_LEFT, KC_DOWN,   KC_RGHT, KC_MPLY,   KC_BSLS,
     KC_NLCK,  KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PCMM,      KC_VOLD, KC_END,  KC_PSCR,   KC_PGDN, KC_MNXT,   KC_RCTL,
                        LT(3, KC_BSPACE), KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, LT(3, KC_DELETE)
  ),

  [3] = LAYOUT_split_3x6_3(
           RGB_MODE_PLAIN,  KC_ASUP, KC_ASTG, KC_ASDN, QK_BOOT, _______,      _______, QK_BOOT,  KC_ASDN,  KC_ASTG, KC_ASUP, RGB_MODE_PLAIN, \
           RGB_TOG,         RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,      RGB_MOD, RGB_SPI,  RGB_VAI,  RGB_SAI, RGB_HUI, RGB_TOG, \
           _______,         RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGB_RMOD,     RGB_RMOD, RGB_SPD, RGB_VAD,  RGB_SAD, RGB_HUD, _______, \
                                            _______, _______,   _______,      _______, _______,   _______\
  )
};

#ifdef OLED_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
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

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
    oled_write_ln_P(PSTR(""), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_mod_status(get_mods());
//        oled_write_ln(read_layer_state(), false);
#ifdef WPM_ENABLE
        char wpm_str[10];
        sprintf(wpm_str, "WPM: %03d", get_current_wpm());
        oled_write_ln(wpm_str, false);
#endif
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE
