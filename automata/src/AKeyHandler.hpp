#pragma once
#ifndef _A_KEYHANDLER_H
#define _A_KEYHANDLER_H

#include "imgui.h"
#include <iostream>

typedef enum {
	A_Key_A = 0x4,
	A_Key_B = 0x5,
	A_Key_C = 0x6,
	A_Key_D = 0x7,
	A_Key_E = 0x8,
	A_Key_F = 0x9,
	A_Key_G = 0xA,
	A_Key_H = 0xB,
	A_Key_I = 0xC,
	A_Key_J = 0xD,
	A_Key_K = 0xE,
	A_Key_L = 0xF,
	A_Key_M = 0x10,
	A_Key_N = 0x11,
	A_Key_O = 0x12,
	A_Key_P = 0x13,
	A_Key_Q = 0x14,
	A_Key_R = 0x15,
	A_Key_S = 0x16,
	A_Key_T = 0x17,
	A_Key_U = 0x18,
	A_Key_V = 0x19,
	A_Key_W = 0x1A,
	A_Key_X = 0x1B,
	A_Key_Y = 0x1C,
	A_Key_Z = 0x1D,
	// Number & Numpad Keys
	A_Key_1 = 0x1E | 0x59,
	A_Key_2 = 0x1F | 0x5A,
	A_Key_3 = 0x20 | 0x5B,
	A_Key_4 = 0x21 | 0x5C,
	A_Key_5 = 0x22 | 0x5D,
	A_Key_6 = 0x23 | 0x5E,
	A_Key_7 = 0x24 | 0x5F,
	A_Key_8 = 0x25 | 0x60,
	A_Key_9 = 0x26 | 0x61,
	A_Key_0 = 0x27 | 0x62,
	// Symbol Keys
	A_Key_Minus		= 0x2D | 0x56,
	A_Key_Plus		= 0x2E | 0x57,
	A_Key_LBracket	= 0x2F,
	A_Key_LBrace	= 0x2F,
	A_Key_LParen	= 0x26,
	A_Key_RBrace	= 0x30,
	A_Key_RBracket	= 0x30,
	A_Key_RParen	= 0x27,
	A_Key_Backslash = 0x31,
	A_Key_Slash		= 0x38,
	A_Key_Semicolon = 0x33,
	A_Key_Colon		= 0x33,
	A_Key_Apos		= 0x34,
	A_Key_Quote		= 0x34,
	A_Key_Comma		= 0x36,
	A_Key_Period	= 0x37,
	// F-Keys
	A_Key_F1	= 0x3A,
	A_Key_F2	= 0x3B,
	A_Key_F3	= 0x3C,
	A_Key_F4	= 0x3D,
	A_Key_F5	= 0x3E,
	A_Key_F6	= 0x3F,
	A_Key_F7	= 0x40,
	A_Key_F8	= 0x41,
	A_Key_F9	= 0x42,
	A_Key_F10	= 0x43,
	A_Key_F11	= 0x44,
	A_Key_F12	= 0x45,
	// Control Keys
	A_Key_LControl	= 0xE0,
	A_Key_LShift	= 0xE1,
	A_Key_LAlt		= 0xE2,
	A_Key_RControl	= 0xE4,
	A_Key_RShift	= 0xE5,
	A_Key_RAlt		= 0xE6,
	A_Key_Control	= A_Key_LControl	| A_Key_RControl,
	A_Key_Shift		= A_Key_LShift		| A_Key_RShift,
	A_Key_Alt		= A_Key_LAlt		| A_Key_RAlt,
	// Misc. Keys
	A_Key_Enter		= 0x28 | 0x58,
	A_Key_Escape	= 0x29,
	A_Key_Backspace = 0x2A,
	A_Key_Tab		= 0x2B,
	A_Key_Space		= 0x2C,
	A_Key_Tilde		= 0x35,
} A_Key;

bool is_key_pressed(ImGuiKey key);
bool is_key_pressed(A_Key key);
bool is_key_pressed(int* key);

bool is_key_down(ImGuiKey key);
bool is_key_down(A_Key key);
bool is_key_down(int* key);

bool is_key_released(ImGuiKey key);
bool is_key_released(A_Key key);
bool is_key_released(int* key);

#endif // _A_KEYHANDLER_H