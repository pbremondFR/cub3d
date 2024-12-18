/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mlx_codes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:23:49 by pbremond          #+#    #+#             */
/*   Updated: 2024/12/17 16:11:11 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MLX_CODES_H
# define CUB3D_MLX_CODES_H

# ifdef __linux__

#  define XK_MISCELLANY
#  define XK_LATIN1
#  include <X11/X.h>
#  include <X11/keysymdef.h>

#  define EVENT_KEY_DOWN		KeyPress
#  define EVENT_KEY_UP			KeyRelease
#  define EVENT_MOUSE_PRESS		ButtonPress
#  define EVENT_MOUSE_RELEASE	ButtonRelease
#  define EVENT_MOUSE_MOVE		MotionNotify
#  define EVENT_EXPOSE			Expose
#  define EVENT_DESTROY			DestroyNotify

#  define E_KDWN	EVENT_KEY_DOWN
#  define E_KUP		EVENT_KEY_UP
#  define E_MPRESS	EVENT_MOUSE_PRESS
#  define E_MREL	EVENT_MOUSE_RELEASE
#  define E_MMOV	EVENT_MOUSE_MOVE
#  define E_XP		EVENT_EXPOSE
#  define E_DSTR	EVENT_DESTROY

#  define KEYC_ESC		XK_Escape
#  define KEYC_W		XK_w
#  define KEYC_A		XK_a
#  define KEYC_S		XK_s
#  define KEYC_D		XK_d
#  define KEYC_LEFT		XK_Left
#  define KEYC_RIGHT	XK_Right
#  define KEYC_UP		XK_Up
#  define KEYC_SPA		XK_space

#  define KEYC_M1	1
#  define KEYC_M2	2
#  define KEYC_M3	3
#  define KEYC_MUP	4
#  define KEYC_MDWN	5

// Codes from the project back when I finished it (for MacOS)
# else

#  define EVENT_KEY_DOWN		2
#  define EVENT_KEY_UP			3
#  define EVENT_MOUSE_PRESS		4
#  define EVENT_MOUSE_RELEASE	5
#  define EVENT_MOUSE_MOVE		6
#  define EVENT_EXPOSE			12
#  define EVENT_DESTROY			17

#  define E_KDWN	EVENT_KEY_DOWN
#  define E_KUP		EVENT_KEY_UP
#  define E_MPRESS	EVENT_MOUSE_PRESS
#  define E_MREL	EVENT_MOUSE_RELEASE
#  define E_MMOV	EVENT_MOUSE_MOVE
#  define E_XP		EVENT_EXPOSE
#  define E_DSTR	EVENT_DESTROY

#  define KEYC_ESC		53
#  define KEYC_W		13
#  define KEYC_A		0
#  define KEYC_S		1
#  define KEYC_D		2
#  define KEYC_LEFT		123
#  define KEYC_RIGHT	124
#  define KEYC_UP		126
#  define KEYC_SPA		49

#  define KEYC_M1	1
#  define KEYC_M2	2
#  define KEYC_M3	3
#  define KEYC_MUP	4
#  define KEYC_MDWN	5

# endif

#endif
