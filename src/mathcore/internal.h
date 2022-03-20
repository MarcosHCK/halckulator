/* Copyright 2021-2025 MarcosHCK
 * This file is part of halckulator.
 *
 * halckulator is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * halckulator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with halckulator.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef __MATH_INTERNAL__
#define __MATH_INTERNAL__ 1
#include <core.h>

#if !__LIBMATHCORE_INSIDE__
# error "You shouldn't be using this header"
#endif // !__LIBMATHCORE_INSIDE__

#if __cplusplus
extern "C" {
#endif // __cplusplus

/*
 * core.c
 *
 */

#define validate_index(index) ((_math_core_checkidx)(core,(index)))
#define switch_index(index) ((_math_core_switchidx)(core,(index)))

G_GNUC_INTERNAL
int
_math_core_checkidx (MathCore* core, int index);
G_GNUC_INTERNAL
int
_math_core_switchidx (MathCore* core, int index);
G_GNUC_INTERNAL
void
_math_core_push (MathCore* core, gpointer object);
G_GNUC_INTERNAL
void
_math_core_pop (MathCore* core);
G_GNUC_INTERNAL
gpointer
_math_core_peek (MathCore* core, gint index);

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_INTERNAL__
