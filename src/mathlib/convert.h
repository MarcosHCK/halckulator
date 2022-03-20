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
#define __MATH_CONVERT__
//#include <number.h>

typedef struct _MathNumber MathNumber;
typedef enum _MathNumberKind MathNumberKind;

#if __cplusplus
extern "C" {
#endif // __cplusplus

MathNumber*
math_convert_z2q (MathNumber* number);
MathNumber*
math_convert_z2f (MathNumber* number);
MathNumber*
math_convert_q2z (MathNumber* number);
MathNumber*
math_convert_q2f (MathNumber* number);
MathNumber*
math_convert_f2z (MathNumber* number);
MathNumber*
math_convert_f2q (MathNumber* number);
MathNumberKind
math_convert_equalize_kind (MathNumberKind kind1, MathNumberKind kind2);
MathNumber*
math_convert_equalize (MathNumber* number, MathNumberKind kind);

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_CONVERT__
