#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _RAISE 1
#define _LOWER 2
#define _QWERTY 3

enum custom_keycodes {
    WINDOWLEFT = SAFE_RANGE,
    WINDOWRIGHT,
    DESKTOPLEFT,
    DESKTOPRIGHT,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case WINDOWLEFT:
        if (record->event.pressed) {
            SEND_STRING(SS_RGUI(SS_LSFT(SS_TAP(X_LEFT))));
        }
        break;

    case WINDOWRIGHT:
        if (record->event.pressed) {
            SEND_STRING(SS_RGUI(SS_LSFT(SS_TAP(X_RIGHT))));
        }
        break;

    case DESKTOPLEFT:
        if (record->event.pressed) {
            SEND_STRING(SS_RGUI(SS_LCTL(SS_TAP(X_LEFT))));
        }
        break;

    case DESKTOPRIGHT:
        if (record->event.pressed) {
            SEND_STRING(SS_RGUI(SS_LCTL(SS_TAP(X_RIGHT))));
        }
        break;

    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_5x6(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, 												KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
		KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, 												KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_MINS, 
		KC_LSFT, KC_A, KC_R, KC_S, KC_T, KC_D, 												KC_H, KC_N, KC_E, KC_I, KC_O, KC_RSFT, 
		KC_LALT, KC_Z, KC_X, KC_C, KC_V, KC_B, 												KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_QUOT,
		KC_UP, KC_DOWN, 												KC_LEFT, KC_RGHT, 
		LT(_RAISE,KC_ENT), KC_SPC, 												KC_BSPC, LT(_LOWER,KC_ESC), 
		KC_LALT, KC_LCTL, 												LCTL_T(KC_DEL), KC_LGUI, 
		KC_LGUI, KC_LALT, 												KC_APP, KC_RALT),
	[1] = LAYOUT_5x6(
		KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, 				KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, 
		KC_GRV, KC_1, KC_2, KC_UP, KC_4, KC_5, 							KC_6, KC_LCBR, KC_RCBR, KC_9, KC_MINS, KC_EQL, 
		KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_LPRN, 			KC_H, KC_LPRN, KC_RPRN, KC_QUOT, KC_BSLS, KC_QUOT, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 			KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS, KC_EQL, KC_UNDS, 
		KC_TRNS, KC_PSCR, 												KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, 												KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, 												KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, 												KC_TRNS, KC_TRNS),
	[2] = LAYOUT_5x6(
		KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,			 			KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
		KC_MPLY, KC_MUTE, KC_TRNS, KC_MS_U, KC_TRNS, KC_LBRC, 			KC_RBRC, KC_WH_U, KC_TRNS, KC_PSCR, KC_INS, KC_HOME, 
		KC_MNXT, KC_VOLU, KC_MS_L, KC_MS_D, KC_MS_R, KC_LPRN, 			KC_RPRN, KC_BTN1, KC_BTN2, KC_TRNS, KC_DEL, KC_END, 
		KC_MPRV, KC_VOLD, WINDOWLEFT, WINDOWRIGHT, DESKTOPLEFT, DESKTOPRIGHT, 			KC_TRNS, KC_WH_D, KC_TRNS, KC_TRNS, KC_TRNS, KC_NLCK, 
		RGB_RMOD, RGB_MOD, 												KC_EQL, KC_TRNS,
		KC_TRNS, KC_TRNS, 												KC_TRNS, KC_TRNS, 
		TG(_QWERTY), KC_TRNS, 												KC_TRNS, KC_TRNS, 
		RESET, RGB_TOG, 												KC_TRNS, KC_TRNS),
	[_QWERTY] = LAYOUT_5x6(
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
     KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
     KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                      KC_LBRC,KC_RBRC,                                                       KC_PLUS, KC_EQL,
                                      KC_TRNS,KC_SPC,                        KC_ENT, KC_TRNS,
                                      TG(_QWERTY),KC_HOME,                         KC_END,  KC_DEL,
                                      KC_BSPC, KC_GRV,                        KC_LGUI, KC_LALT
  ),
};

