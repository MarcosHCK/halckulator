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
#include <number.h>

G_DEFINE_TYPE
(MathNumber,
 math_number,
 MATH_TYPE_VALUE);

static void
math_number_class_finalize (MathValue* pself)
{
  MathNumber* self = MATH_NUMBER (pself);
  if (self->inited == TRUE)
  switch (self->kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    mpz_clear (self->integer);
    break;
  case MATH_NUMBER_KIND_RATIONAL:
    mpq_clear (self->rational);
    break;
  case MATH_NUMBER_KIND_REAL:
    mpf_clear (self->real);
    break;
  }
MATH_VALUE_CLASS (math_number_parent_class)->finalize (pself);
}

static void
math_number_class_init (MathNumberClass* klass)
{
  MathValueClass* oclass = MATH_VALUE_CLASS (klass);

  oclass->finalize = math_number_class_finalize;
}

static void
math_number_init (MathNumber* self)
{
  self->inited = FALSE;
}

/*
 * API
 *
 */

MathNumber*
math_number_new (MathNumberKind kind)
{
  MathNumber* self = (MathNumber*)
  math_value_new (MATH_TYPE_NUMBER);
  self->kind = kind;
  switch (kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    mpz_init (self->integer);
    break;
  case MATH_NUMBER_KIND_RATIONAL:
    mpq_init (self->rational);
    break;
  case MATH_NUMBER_KIND_REAL:
    mpf_init (self->real);
    break;
  }
return self;
}

gboolean
math_number_check_kind (MathNumber* number, MathNumberKind kind)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), FALSE);
  if (number->kind != kind)
    {
      g_log_structured
      (G_LOG_DOMAIN,
       G_LOG_LEVEL_WARNING,
#if DEVELOPER == 1
       "(%s: %i): "
#endif // DEVELOPER
       "Number is of kind '%i' but '%i' is needed",
#if DEVELOPER == 1
       G_STRFUNC,
       __LINE__,
#endif // DEVELOPER
       number->kind,
       kind);
      return FALSE;
    }
return TRUE;
}

void
math_number_set_uint (MathNumber* number, guint value)
{
  g_return_if_fail (MATH_IS_NUMBER (number));
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_INTEGER))
    return;
  mpz_set_ui (number->integer, value);
}

guint
math_number_get_uint (MathNumber* number)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), (guint) 0);
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_INTEGER))
    return (guint) 0;
return mpz_get_ui (number->integer);
}

void
math_number_set_num (MathNumber* number, MathNumber* num)
{
  g_return_if_fail (MATH_IS_NUMBER (number));
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_RATIONAL))
    return;
  g_return_if_fail (MATH_IS_NUMBER (num));
  mpq_set_num (number->rational, num->integer);
}

MathNumber*
math_number_get_num (MathNumber* number)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), NULL);
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_RATIONAL))
    return NULL;
  MathNumber* num = math_number_new (MATH_NUMBER_KIND_INTEGER);
  mpq_get_num (num->integer, number->rational);
return num;
}

void
math_number_set_den (MathNumber* number, MathNumber* den)
{
  g_return_if_fail (MATH_IS_NUMBER (number));
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_RATIONAL))
    return;
  g_return_if_fail (MATH_IS_NUMBER (den));
  mpq_set_num (number->rational, den->integer);
}

MathNumber*
math_number_get_den (MathNumber* number)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), NULL);
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_RATIONAL))
    return NULL;
  MathNumber* den = math_number_new (MATH_NUMBER_KIND_INTEGER);
  mpq_get_den (den->integer, number->rational);
return den;
}

void
math_number_set_double (MathNumber* number, gdouble value)
{
  g_return_if_fail (MATH_IS_NUMBER (number));
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_REAL))
    return;
  mpf_set_d (number->real, value);
}

gdouble
math_number_get_double (MathNumber* number)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), (gdouble) 0);
  if (!math_number_check_kind (number, MATH_NUMBER_KIND_REAL))
    return (gdouble) 0;
return mpf_get_d (number->real);
}

void
math_number_set_string (MathNumber* number, const gchar* value, gint base)
{
  g_return_if_fail (MATH_IS_NUMBER (number));
  switch (number->kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    mpz_set_str (number->integer, value, base);
    break;
  case MATH_NUMBER_KIND_RATIONAL:
    mpq_set_str (number->rational, value, base);
    break;
  case MATH_NUMBER_KIND_REAL:
    mpf_set_str (number->real, value, base);
    break;
  }
}

gchar*
math_number_get_string (MathNumber* number, gint base)
{
  g_return_val_if_fail (MATH_IS_NUMBER (number), NULL);
  switch (number->kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    return mpz_get_str (NULL, base, number->integer);
  case MATH_NUMBER_KIND_RATIONAL:
    return mpq_get_str (NULL, base, number->rational);
  case MATH_NUMBER_KIND_REAL:
    return mpf_get_str (NULL, NULL, base, 0, number->real);
  }
}
