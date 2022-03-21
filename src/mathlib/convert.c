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
#include <config.h>
#include <convert.h>

G_GNUC_INTERNAL
MathNumberKind
_math_core_equalize (MathNumberKind kind1, MathNumberKind kind2)
{
  int kind1_ = (int) kind1;
  int kind2_ = (int) kind2;

  if (kind1_ > kind2_)
    return kind1_;
  else
    return kind2_;
}

static inline void
math_convert_z2q (MathCore* core, int index)
{
  g_return_if_fail (MATH_IS_CORE (core));
  g_return_if_fail (math_core_isnumber (core, index));
  MathNumber* number = math_core_tonumber (core, index);
  math_core_pushnumber (core, MATH_NUMBER_KIND_RATIONAL);
  MathNumber* result = math_core_tonumber (core, -1);
  mpq_set_z (result->priv->rational, number->priv->integer);
}

static inline void
math_convert_z2f (MathCore* core, int index)
{
  g_return_if_fail (MATH_IS_CORE (core));
  g_return_if_fail (math_core_isnumber (core, index));
  MathNumber* number = math_core_tonumber (core, index);
  math_core_pushnumber (core, MATH_NUMBER_KIND_REAL);
  MathNumber* result = math_core_tonumber (core, -1);
  mpf_set_z (result->priv->real, number->priv->integer);
}

static inline void
math_convert_q2z (MathCore* core, int index)
{
  g_return_if_fail (MATH_IS_CORE (core));
  g_return_if_fail (math_core_isnumber (core, index));
  MathNumber* number = math_core_tonumber (core, index);
  math_core_pushnumber (core, MATH_NUMBER_KIND_INTEGER);
  MathNumber* result = math_core_tonumber (core, -1);
  mpz_set_q (result->priv->integer, number->priv->rational);
}

static inline void
math_convert_q2f (MathCore* core, int index)
{
  g_return_if_fail (MATH_IS_CORE (core));
  g_return_if_fail (math_core_isnumber (core, index));
  MathNumber* number = math_core_tonumber (core, index);
  math_core_pushnumber (core, MATH_NUMBER_KIND_REAL);
  MathNumber* result = math_core_tonumber (core, -1);
  mpf_set_q (result->priv->real, number->priv->rational);
}

static inline void
math_convert_f2z (MathCore* core, int index)
{
  g_return_if_fail (MATH_IS_CORE (core));
  g_return_if_fail (math_core_isnumber (core, index));
  MathNumber* number = math_core_tonumber (core, index);
  math_core_pushnumber (core, MATH_NUMBER_KIND_INTEGER);
  MathNumber* result = math_core_tonumber (core, -1);
  mpz_set_f (result->priv->integer, number->priv->real);
}

static inline void
math_convert_f2q (MathCore* core, int index)
{
  g_return_if_fail (MATH_IS_CORE (core));
  g_return_if_fail (math_core_isnumber (core, index));
  MathNumber* number = math_core_tonumber (core, index);
  math_core_pushnumber (core, MATH_NUMBER_KIND_RATIONAL);
  MathNumber* result = math_core_tonumber (core, -1);
  mpq_set_f (result->priv->rational, number->priv->real);
}

G_GNUC_INTERNAL
void
math_core_pushnumber_as (MathCore* core, int index, MathNumberKind newkind)
{
  g_return_if_fail (MATH_IS_CORE (core));
  g_return_if_fail (math_core_isnumber (core, index));
  MathNumber* number = math_core_tonumber (core, index);
  MathNumberKind kind = number->priv->kind;

  switch (kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    switch (newkind)
    {
    case MATH_NUMBER_KIND_INTEGER:
      math_core_pushvalue (core, index);
      break;
    case MATH_NUMBER_KIND_RATIONAL:
      math_convert_z2q (core, index);
      break;
    case MATH_NUMBER_KIND_REAL:
      math_convert_z2f (core, index);
      break;
    }
    break;
  case MATH_NUMBER_KIND_RATIONAL:
    switch (newkind)
    {
    case MATH_NUMBER_KIND_INTEGER:
      math_convert_q2z (core, index);
      break;
    case MATH_NUMBER_KIND_RATIONAL:
      math_core_pushvalue (core, index);
      break;
    case MATH_NUMBER_KIND_REAL:
      math_convert_q2f (core, index);
      break;
    }
    break;
  case MATH_NUMBER_KIND_REAL:
    switch (newkind)
    {
    case MATH_NUMBER_KIND_INTEGER:
      math_convert_f2z (core, index);
      break;
    case MATH_NUMBER_KIND_RATIONAL:
      math_convert_f2q (core, index);
      break;
    case MATH_NUMBER_KIND_REAL:
      math_core_pushvalue (core, index);
      break;
    }
    break;
  }
}
