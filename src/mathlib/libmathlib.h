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
#ifndef __LIBMATHLIB__
#define __LIBMATHLIB__ 1
#include <libmathcore.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

int
math_lib_add (MathCore* core);
int
math_lib_sub (MathCore* core);
int
math_lib_mul (MathCore* core);
int
math_lib_div (MathCore* core);

#if __cplusplus
}
#endif // __cplusplus

#endif // __LIBMATHLIB__
