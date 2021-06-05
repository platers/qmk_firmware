#include QMK_KEYBOARD_H

enum layers {
	_COLEMAK,
	_WINDOWS,
	_SYMBOLS,
	_MEDIA,
	_QWERTY,
	_NUMBERS,
};

enum custom_keycodes {
    WINDOWLEFT = SAFE_RANGE,
    WINDOWRIGHT,
    DESKTOPLEFT,
    DESKTOPRIGHT,
    ALT_TAB,
    ALT_TAB_SFT,
};
// Tap Dance declarations
enum {
	TD_CTRL_ALT,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	static bool in_tab = false; // does an ALT-TAB, for windows cycling, without an alt key

	if (keycode != ALT_TAB && keycode != ALT_TAB_SFT && in_tab){
	    // Exit alt tab before treating normally the keycode
	    SEND_STRING(SS_UP(X_LGUI));
	    in_tab = false;
	}

    switch (keycode) {
    	case ALT_TAB:
		    // Macro to handle lower-tab as alt-tab
			if (record->event.pressed) {
				if (!in_tab){
					SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_TAB));
					in_tab = true;
				} else {
					SEND_STRING(SS_TAP(X_TAB));
					// Do not release Alt here, or it will be impossible to switch more than one window:
					// alt-tab-tab will be interpreted as alt-tab, then tab
				}
			}
		    return false;

    	case ALT_TAB_SFT:
		    // Macro to handle lower-tab as alt-tab
			if (record->event.pressed) {
				if (!in_tab){
					SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LSFT) SS_TAP(X_TAB));
					SEND_STRING(SS_UP(X_LSFT));
					in_tab = true;
				} else {
					SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_TAB));
					SEND_STRING(SS_UP(X_LSFT));
					// Do not release Alt here, or it will be impossible to switch more than one window:
					// alt-tab-tab will be interpreted as alt-tab, then tab
				}
			}
		    return false;

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

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_CTRL_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_LCTRL),
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_COLEMAK] = LAYOUT_5x6(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, 												KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
		KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, 												KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_MINS, 
		KC_LSFT, KC_A, KC_R, KC_S, KC_T, KC_D, 												KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, 
		KC_LCTRL, KC_Z, KC_X, KC_C, KC_V, KC_B, 											KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
		KC_UP, KC_DOWN, 														KC_LEFT, KC_RGHT, 
		LT(_SYMBOLS,KC_ENT), KC_SPC, 											LSFT_T(KC_BSPC), LT(_MEDIA,KC_ESC), 
		KC_LALT, KC_LGUI, 														LSA(KC_DEL), KC_LGUI, 
		KC_LGUI, TG(_WINDOWS), 														KC_APP, KC_RALT),
	[_WINDOWS] = LAYOUT_5x6(
		_______, _______, _______, _______, _______, _______, 				_______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, 				_______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, 			_______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, 			_______, _______, _______, _______, _______, _______, 
		_______, _______, 												_______, _______, 
		_______, _______, 												_______, _______, 
		_______, KC_LCTRL, 												_______, _______, 
		_______, _______, 												_______, _______),
	[_SYMBOLS] = LAYOUT_5x6(
		KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, 				KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, 
		KC_GRV, _______, _______, KC_UP, _______, _______, 				_______, KC_LCBR, KC_RCBR, _______, KC_MINS, KC_EQL, 
		_______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_LPRN, 			_______, KC_LPRN, KC_RPRN, KC_QUOT, KC_BSLS, KC_QUOT, 
		_______, _______, _______, _______, _______, _______, 			_______, KC_LBRC, KC_RBRC, _______, KC_EQL, KC_UNDS, 
		_______, _______, 												_______, _______, 
		_______, _______, 												_______, _______, 
		_______, _______, 												_______, _______, 
		_______, _______, 												_______, _______),
	[_MEDIA] = LAYOUT_5x6(
		KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,			 							KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
		KC_MPLY, KC_MUTE, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, 							KC_WH_D, LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), KC_PSCR, KC_MUTE, KC_MPLY, 
		KC_MNXT, KC_VOLU, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, 							XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, KC_VOLU, KC_MNXT, 
		KC_MPRV, KC_VOLD, WINDOWLEFT, WINDOWRIGHT, DESKTOPLEFT, DESKTOPRIGHT, 			KC_WH_U, ALT_TAB, ALT_TAB_SFT, XXXXXXX, KC_VOLD, KC_MPRV, 
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
};

// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_CYAN}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_PURPLE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer     // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    // rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    // rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    return state;
}