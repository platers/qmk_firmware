#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _RAISE 1
#define _LOWER 2
#define _QWERTY 3
#define _VIM 4

enum custom_keycodes {
    WINDOWLEFT = SAFE_RANGE,
    WINDOWRIGHT,
    DESKTOPLEFT,
    DESKTOPRIGHT,
	VIM_ESC,
	_VIM_W,
	_VIM_B,  
	_VIM_A,  
	_VIM_E,  
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	static uint16_t fnx_layer_timer;
	static bool fnx_inverting;

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

    case VIM_ESC:
        if(record->event.pressed){
			fnx_layer_timer = timer_read();
			fnx_inverting = true;
			register_mods(MOD_BIT(KC_LSFT));
		} else {
			unregister_mods(MOD_BIT(KC_LSFT));

			if (timer_elapsed(fnx_layer_timer) < TAPPING_TERM && fnx_inverting)
				layer_invert(_VIM);
		}
        break;

    case _VIM_W:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
        }
        break;

    case _VIM_B:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
        }
        break;

    case _VIM_A:
        if (record->event.pressed) {
        	SEND_STRING(SS_TAP(X_RIGHT));
			layer_invert(_VIM);
        }
        break;

    case _VIM_E:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
            SEND_STRING(SS_TAP(X_LEFT));
        }
        break;

    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_COLEMAK] = LAYOUT_5x6(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, 												KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
		KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, 												KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_MINS, 
		VIM_ESC, KC_A, KC_R, KC_S, KC_T, KC_D, 												KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, 
		KC_TAB, KC_Z, KC_X, KC_C, KC_V, KC_B, 												KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
		KC_UP, KC_DOWN, 														KC_LEFT, KC_RGHT, 
		LT(_RAISE,KC_ENT), KC_SPC, 												LSFT_T(KC_BSPC), LT(_LOWER,KC_ESC), 
		KC_LALT, KC_LCTL, 														LCTL_T(KC_DEL), KC_LGUI, 
		KC_LGUI, KC_LALT, 														KC_APP, KC_RALT),
	[_RAISE] = LAYOUT_5x6(
		KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, 				KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, 
		KC_GRV, _______, _______, KC_UP, _______, _______, 				_______, KC_LCBR, KC_RCBR, _______, KC_MINS, KC_EQL, 
		_______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_LPRN, 			_______, KC_LPRN, KC_RPRN, KC_QUOT, KC_BSLS, KC_QUOT, 
		_______, _______, _______, _______, _______, _______, 			_______, KC_LBRC, KC_RBRC, _______, KC_EQL, KC_UNDS, 
		_______, _______, 												_______, _______, 
		_______, _______, 												_______, _______, 
		_______, _______, 												_______, _______, 
		_______, _______, 												_______, _______),
	[_LOWER] = LAYOUT_5x6(
		KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,			 							KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
		KC_MPLY, KC_MUTE, _______, KC_MS_U, _______, _______, 							KC_WH_D, _______, _______, KC_PSCR, KC_INS, KC_HOME, 
		KC_MNXT, KC_VOLU, KC_MS_L, KC_MS_D, KC_MS_R, _______, 							_______, KC_BTN1, KC_BTN2, _______, KC_DEL, KC_END, 
		KC_MPRV, KC_VOLD, WINDOWLEFT, WINDOWRIGHT, DESKTOPLEFT, DESKTOPRIGHT, 			KC_WH_U, _______, _______, _______, _______, _______, 
		RGB_RMOD, RGB_MOD, 																_______, _______,
		_______, _______, 																_______, _______, 
		TG(_QWERTY), _______, 															_______, _______, 
		RESET, RGB_TOG, 																_______, _______),
	[_QWERTY] = LAYOUT_5x6(
     _______ , _______  , _______, _______,_______, _______,                  _______  	, _______  , _______  , _______  , _______  ,_______,
     _______ , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                        KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
     _______, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
     _______, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                      _______,_______,                                                       _______, _______,
                                      _______,_______,                        _______, _______,
                                      TG(_QWERTY),_______,                     _______,  _______,
                                      _______, _______,                        _______, _______),
	[_VIM] = LAYOUT_5x6(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 				XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, _VIM_W, XXXXXXX, XXXXXXX, XXXXXXX, 				KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		TG(_VIM), _VIM_A, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 				KC_LEFT, XXXXXXX, _VIM_E, TG(_VIM), XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _VIM_B, 				KC_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, 												XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, 												XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, 												XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, 												XXXXXXX, XXXXXXX),
};

