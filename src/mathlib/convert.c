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
/*
MathNumber*
math_convert_z2q (MathNumber* number)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), NULL);
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_INTEGER))
    return NULL;
  MathNumber* result = math_number_new (MATH_NUMBER_KIND_RATIONAL);
  mpq_set_z (result->rational, number->integer);
return result;
}

MathNumber*
math_convert_z2f (MathNumber* number)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), NULL);
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_INTEGER))
    return NULL;
  MathNumber* result = math_number_new (MATH_NUMBER_KIND_REAL);
  mpf_set_z (result->real, number->integer);
return result;
}

MathNumber*
math_convert_q2z (MathNumber* number)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), NULL);
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_RATIONAL))
    return NULL;
  MathNumber* result = math_number_new (MATH_NUMBER_KIND_INTEGER);
  mpz_set_q (result->integer, number->rational);
return result;
}

MathNumber*
math_convert_q2f (MathNumber* number)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), NULL);
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_RATIONAL))
    return NULL;
  MathNumber* result = math_number_new (MATH_NUMBER_KIND_REAL);
  mpf_set_q (result->real, number->rational);
return result;
}

MathNumber*
math_convert_f2z (MathNumber* number)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), NULL);
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_REAL))
    return NULL;
  MathNumber* result = math_number_new (MATH_NUMBER_KIND_INTEGER);
  mpz_set_f (result->integer, number->real);
return result;
}

MathNumber*
math_convert_f2q (MathNumber* number)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), NULL);
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_REAL))
    return NULL;
  MathNumber* result = math_number_new (MATH_NUMBER_KIND_RATIONAL);
  mpq_set_f (result->rational, number->real);
return result;
}

MathNumberKind
math_convert_equalize_kind (MathNumberKind kind1, MathNumberKind kind2)
{
  int kind1_ = (int) kind1;
  int kind2_ = (int) kind2;

  if (kind1_ > kind2_)
    return kind1_;
  else
    return kind2_;
}

static MathNumber*
convert_upwards (MathNumber* number, MathNumberKind newkind)
{
  switch (newkind)
  {
  case MATH_NUMBER_KIND_RATIONAL:
    switch (number->kind)
    {
    case MATH_NUMBER_KIND_INTEGER:
      return math_convert_z2q (number);
    default:
      g_assert_not_reached ();
      break;
    }
    break;
  case MATH_NUMBER_KIND_REAL:
    switch (number->kind)
    {
    case MATH_NUMBER_KIND_INTEGER:
      return math_convert_z2f (number);
    case MATH_NUMBER_KIND_RATIONAL:
      return math_convert_q2f (number);
    default:
      g_assert_not_reached ();
      break;
    }
    break;
  default:
    g_assert_not_reached ();
    break;
  }
}

MathNumber*
math_convert_equalize (MathNumber* number, MathNumberKind kind)
{
  if (number->kind == kind)
    return math_value_ref (number);
  else
    {
      int kind1 = (int) kind;
      int kind2 = (int) number->kind;
      if (kind1 >= kind2)
        return convert_upwards (number, kind);
      g_assert_not_reached ();
    }
}
*/
