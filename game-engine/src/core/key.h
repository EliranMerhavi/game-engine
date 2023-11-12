#pragma once
#pragma once
#include <stdint.h>

enum key_state
{
	RELEASED,
	PRESSED,
	REPEAT
};

using keycode_t = uint16_t;

namespace key
{
	enum : keycode_t
	{
		// from glfw3.h
		space = 32,
		apostrophe = 39, /* ' */
		comma = 44, /* , */
		minus = 45, /* - */
		period = 46, /* . */
		slash = 47, /* / */
		d0 = 48, /* 0 */
		d1 = 49, /* 1 */
		d2 = 50, /* 2 */
		d3 = 51, /* 3 */
		d4 = 52, /* 4 */
		d5 = 53, /* 5 */
		d6 = 54, /* 6 */
		d7 = 55, /* 7 */
		d8 = 56, /* 8 */
		d9 = 57, /* 9 */
		semicolon = 59, /* ; */
		equal = 61, /* = */
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		left_bracket = 91,  /* [ */
		backslash = 92,  /* \ */
		right_bracket = 93,  /* ] */
		graveaccent = 96,  /* ` */
		world1 = 161, /* non-us #1 */
		world2 = 162, /* non-us #2 */
		/* function keys */
		escape = 256,
		enter = 257,
		tab = 258,
		backspace = 259,
		insert = 260,
		delete_ = 261,
		right = 262,
		left = 263,
		down = 264,
		up = 265,
		pageup = 266,
		pagedown = 267,
		home = 268,
		end = 269,
		capslock = 280,
		scrolllock = 281,
		numlock = 282,
		printscreen = 283,
		pause = 284,
		f1 = 290,
		f2 = 291,
		f3 = 292,
		f4 = 293,
		f5 = 294,
		f6 = 295,
		f7 = 296,
		f8 = 297,
		f9 = 298,
		f10 = 299,
		f11 = 300,
		f12 = 301,
		f13 = 302,
		f14 = 303,
		f15 = 304,
		f16 = 305,
		f17 = 306,
		f18 = 307,
		f19 = 308,
		f20 = 309,
		f21 = 310,
		f22 = 311,
		f23 = 312,
		f24 = 313,
		f25 = 314,
		/* keypad */
		kp0 = 320,
		kp1 = 321,
		kp2 = 322,
		kp3 = 323,
		kp4 = 324,
		kp5 = 325,
		kp6 = 326,
		kp7 = 327,
		kp8 = 328,
		kp9 = 329,
		kp_decimal = 330,
		kp_divide = 331,
		kp_multiply = 332,
		kp_subtract = 333,
		kp_add = 334,
		kp_enter = 335,
		kp_equal = 336,
		left_shift = 340,
		left_control = 341,
		left_alt = 342,
		left_super = 343,
		right_shift = 344,
		right_control = 345,
		right_alt = 346,
		right_super = 347,
		menu = 348
	};
}
