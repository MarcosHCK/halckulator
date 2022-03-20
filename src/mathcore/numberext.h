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
#ifndef __MATH_NUMBEREXT__
#define __MATH_NUMBEREXT__ 1
#include <number.h>
#include <gmp.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum
{
  MATH_NUMBER_KIND_INTEGER,
  MATH_NUMBER_KIND_RATIONAL,
  MATH_NUMBER_KIND_REAL,
} MathNumberKind;

struct _MathNumberPrivate
{
  MathNumberKind kind;
  union
  {
    mpz_t integer;
    mpq_t rational;
    mpf_t real;
  };
};

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_NUMBER__
