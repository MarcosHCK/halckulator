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
#include <libmathlib.h>
#include <convert.h>

int
math_lib_add (MathCore* core)
{
  g_return_val_if_fail (MATH_IS_CORE (core), -1);
  g_return_val_if_fail (math_core_isnumber (core, 0), -1);
  g_return_val_if_fail (math_core_isnumber (core, 1), -1);
  MathNumber* number1 = NULL;
  MathNumber* number2 = NULL;
  MathNumber* result = NULL;
  MathNumberKind kind;

  number1 = math_core_tonumber (core, 0);
  number2 = math_core_tonumber (core, 1);
  kind = _math_core_equalize (number1->priv->kind, number2->priv->kind);

  math_core_pushnumber_as (core, 0, kind);
  math_core_pushnumber_as (core, 1, kind);
  math_core_pushnumber (core, kind);

  number1 = math_core_tonumber (core, -3);
  number2 = math_core_tonumber (core, -2);
  result = math_core_tonumber (core, -1);

  switch (kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    mpz_add
    (result->priv->integer,
     number1->priv->integer,
     number2->priv->integer);
    break;
  case MATH_NUMBER_KIND_RATIONAL:
    mpq_add
    (result->priv->rational,
     number1->priv->rational,
     number2->priv->rational);
    break;
  case MATH_NUMBER_KIND_REAL:
    mpf_add
    (result->priv->real,
     number1->priv->real,
     number2->priv->real);
    break;
  }
return 1;
}

int
math_lib_sub (MathCore* core)
{
  g_return_val_if_fail (MATH_IS_CORE (core), -1);
  g_return_val_if_fail (math_core_isnumber (core, 0), -1);
  g_return_val_if_fail (math_core_isnumber (core, 1), -1);
  MathNumber* number1 = NULL;
  MathNumber* number2 = NULL;
  MathNumber* result = NULL;
  MathNumberKind kind;

  number1 = math_core_tonumber (core, 0);
  number2 = math_core_tonumber (core, 1);
  kind = _math_core_equalize (number1->priv->kind, number2->priv->kind);

  math_core_pushnumber_as (core, 0, kind);
  math_core_pushnumber_as (core, 1, kind);
  math_core_pushnumber (core, kind);

  number1 = math_core_tonumber (core, -3);
  number2 = math_core_tonumber (core, -2);
  result = math_core_tonumber (core, -1);

  switch (kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    mpz_sub
    (result->priv->integer,
     number1->priv->integer,
     number2->priv->integer);
    break;
  case MATH_NUMBER_KIND_RATIONAL:
    mpq_sub
    (result->priv->rational,
     number1->priv->rational,
     number2->priv->rational);
    break;
  case MATH_NUMBER_KIND_REAL:
    mpf_sub
    (result->priv->real,
     number1->priv->real,
     number2->priv->real);
    break;
  }
return 1;
}

int
math_lib_mul (MathCore* core)
{
  g_return_val_if_fail (MATH_IS_CORE (core), -1);
  g_return_val_if_fail (math_core_isnumber (core, 0), -1);
  g_return_val_if_fail (math_core_isnumber (core, 1), -1);
  MathNumber* number1 = NULL;
  MathNumber* number2 = NULL;
  MathNumber* result = NULL;
  MathNumberKind kind;

  number1 = math_core_tonumber (core, 0);
  number2 = math_core_tonumber (core, 1);
  kind = _math_core_equalize (number1->priv->kind, number2->priv->kind);

  math_core_pushnumber_as (core, 0, kind);
  math_core_pushnumber_as (core, 1, kind);
  math_core_pushnumber (core, kind);

  number1 = math_core_tonumber (core, -3);
  number2 = math_core_tonumber (core, -2);
  result = math_core_tonumber (core, -1);

  switch (kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    mpz_mul
    (result->priv->integer,
     number1->priv->integer,
     number2->priv->integer);
    break;
  case MATH_NUMBER_KIND_RATIONAL:
    mpq_mul
    (result->priv->rational,
     number1->priv->rational,
     number2->priv->rational);
    break;
  case MATH_NUMBER_KIND_REAL:
    mpf_mul
    (result->priv->real,
     number1->priv->real,
     number2->priv->real);
    break;
  }
return 1;
}

int
math_lib_div (MathCore* core)
{
  g_return_val_if_fail (MATH_IS_CORE (core), -1);
  g_return_val_if_fail (math_core_isnumber (core, 0), -1);
  g_return_val_if_fail (math_core_isnumber (core, 1), -1);
  MathNumber* number1 = NULL;
  MathNumber* number2 = NULL;
  MathNumber* result = NULL;
  MathNumberKind kind;

  number1 = math_core_tonumber (core, 0);
  number2 = math_core_tonumber (core, 1);
  kind = _math_core_equalize (number1->priv->kind, number2->priv->kind);

  math_core_pushnumber_as (core, 0, kind);
  math_core_pushnumber_as (core, 1, kind);
  math_core_pushnumber (core, kind);

  number1 = math_core_tonumber (core, -3);
  number2 = math_core_tonumber (core, -2);
  result = math_core_tonumber (core, -1);

  switch (kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    mpz_div
    (result->priv->integer,
     number1->priv->integer,
     number2->priv->integer);
    break;
  case MATH_NUMBER_KIND_RATIONAL:
    mpq_div
    (result->priv->rational,
     number1->priv->rational,
     number2->priv->rational);
    break;
  case MATH_NUMBER_KIND_REAL:
    mpf_div
    (result->priv->real,
     number1->priv->real,
     number2->priv->real);
    break;
  }
return 1;
}
