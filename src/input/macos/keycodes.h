/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:23:20 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/06 12:42:01 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

enum e_key
{
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_BACKSPC = 117,
	KEY_ENTER = 76,
	KEY_HOME = 115,
	KEY_END = 119,
	KEY_PAGEDOWN = 121,
	KEY_PAGEUP = 116,
	KEY_RETURN = 36,
	KEY_DELETE = 51,
	KEY_TAB = 48,
	KEY_SPACEBAR = 49,
	KEY_SHIFT = 56,
	KEY_CONTROL = 59,
	KEY_MENU = 58,
	KEY_ESCAPE = 53,
	KEY_CAPSLOCK = 57,
	KEY_HELP = 114,
	KEY_F1 = 122,
	KEY_F2 = 120,
	KEY_F3 = 99,
	KEY_F4 = 118,
	KEY_F5 = 96,
	KEY_F6 = 97,
	KEY_F7 = 98,
	KEY_F8 = 100,
	KEY_F9 = 101,
	KEY_F10 = 109,
	KEY_F11 = 103,
	KEY_F12 = 111,
	KEY_FN = 63,
	KEY_OPT = 58,
	KEY_CMD = 55,
	KEY_Q = 12,
	KEY_W = 13,
	KEY_E = 14,
	KEY_R = 15,
	KEY_T = 17,
	KEY_Y = 16,
	KEY_U = 32,
	KEY_I = 34,
	KEY_O = 31,
	KEY_P = 35,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_F = 3,
	KEY_G = 5,
	KEY_H = 4,
	KEY_J = 38,
	KEY_K = 40,
	KEY_L = 37,
	KEY_Z = 6,
	KEY_X = 7,
	KEY_C = 8,
	KEY_V = 9,
	KEY_B = 11,
	KEY_N = 45,
	KEY_M = 46,
	KEY_0 = 29,
	KEY_1 = 18,
	KEY_2 = 19,
	KEY_3 = 20,
	KEY_4 = 21,
	KEY_5 = 23,
	KEY_6 = 22,
	KEY_7 = 26,
	KEY_8 = 28,
	KEY_9 = 25,
	KEY_PERIOD = 4,
	KEY_COMMA = 43,
	KEY_SLASH = 44,
	KEY_NUM0 = 82,
	KEY_NUM1 = 83,
	KEY_NUM2 = 84,
	KEY_NUM3 = 85,
	KEY_NUM4 = 86,
	KEY_NUM5 = 87,
	KEY_NUM6 = 88,
	KEY_NUM7 = 89,
	KEY_NUM8 = 91,
	KEY_NUM9 = 92,
	KEY_NUM_MUL = 67,
	KEY_NUM_ADD = 69,
	KEY_NUM_SUB = 78,
	KEY_NUM_DIV = 75,
	KEY_NUM_DEC = 65,
	KEY_NUM_EQ = 81
};

enum	e_button
{
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 2,
	MOUSE_MID = 3,
	SCROLL_DOWN = 4,
	SCROLL_UP = 5,
};

#endif
