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
#ifndef __MATH_CONVERT__
#define __MATH_CONVERT__ 1
#include <libmathcorext.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

G_GNUC_INTERNAL
MathNumberKind
_math_core_equalize (MathNumberKind kind1, MathNumberKind kind2);
G_GNUC_INTERNAL
void
math_core_pushnumber_as (MathCore* core, int index, MathNumberKind newkind);

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_CONVERT__
