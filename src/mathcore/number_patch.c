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
#include <number_patch.h>

/*
 * Section
 * - init
 * - clear
 * - clone
 * - get_*
 * - set_*
 *
 */

G_GNUC_INTERNAL
void
mpx_value_init (MpxValue* value)
{
  switch (value->type)
  {
  case MPX_VALUE_TYPE_INTEGER:
    mpz_init ((mpz_ptr) value->integer);
    break;
  case MPX_VALUE_TYPE_RATIONAL:
    mpq_init ((mpq_ptr) value->rational);
    break;
  case MPX_VALUE_TYPE_REAL:
    mpf_init ((mpf_ptr) value->real);
    break;
  }
}

G_GNUC_INTERNAL
void
mpx_value_clear (MpxValue* value)
{
  switch (value->type)
  {
  case MPX_VALUE_TYPE_INTEGER:
    mpz_clear ((mpz_ptr) value->integer);
    break;
  case MPX_VALUE_TYPE_RATIONAL:
    mpq_clear ((mpq_ptr) value->rational);
    break;
  case MPX_VALUE_TYPE_REAL:
    mpf_clear ((mpf_ptr) value->real);
    break;
  }
}

G_GNUC_INTERNAL
void
mpx_value_clone (MpxValue* value, MpxValue* result)
{
  switch (value->type)
  {
  case MPX_VALUE_TYPE_INTEGER:
    mpz_init (result->integer);
    mpz_set (result->integer, value->integer);
    break;
  case MPX_VALUE_TYPE_RATIONAL:
    mpq_init (result->rational);
    mpq_set (result->rational, value->rational);
    break;
  case MPX_VALUE_TYPE_REAL:
    mpf_init (result->real);
    mpf_set (result->real, value->real);
    break;
  }
}

G_GNUC_INTERNAL
gboolean
mpx_value_check_type (MpxValue* value, MpxValueType type)
{
  if (value->type != type)
    {
      g_log_structured
      (G_LOG_DOMAIN,
       G_LOG_LEVEL_WARNING,
#if DEVELOPER == 1
       "(%s: %i): "
#endif // DEVELOPER
       "Number is of type '%i' but '%i' is requested",
#if DEVELOPER == 1
       G_STRFUNC,
       __LINE__,
#endif // DEVELOPER
       value->type,
       type);
      return FALSE;
    }
return TRUE;
}

G_GNUC_INTERNAL
void
mpx_value_set_numerator (MpxValue* value, MpxValue* newvalue)
{
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_RATIONAL))
    return;
  if (!mpx_value_check_type (newvalue, MPX_VALUE_TYPE_INTEGER))
    return;
  mpq_set_num (value->rational, newvalue->integer);
}
G_GNUC_INTERNAL
void
mpx_value_get_numerator (MpxValue* value, MpxValue* result)
{
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_RATIONAL))
    return;
  if (!mpx_value_check_type (result, MPX_VALUE_TYPE_INTEGER))
    return;
  mpq_get_num (result->integer, value->rational);
}
G_GNUC_INTERNAL
void
mpx_value_set_denominator (MpxValue* value, MpxValue* newvalue)
{
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_RATIONAL))
    return;
  if (!mpx_value_check_type (newvalue, MPX_VALUE_TYPE_INTEGER))
    return;
  mpq_set_den (value->rational, newvalue->integer);
}
G_GNUC_INTERNAL
void
mpx_value_get_denominator (MpxValue* value, MpxValue* result)
{
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_RATIONAL))
    return;
  if (!mpx_value_check_type (result, MPX_VALUE_TYPE_INTEGER))
    return;
  mpq_get_den (result->integer, value->rational);
}

G_GNUC_INTERNAL
void
mpx_value_set_uint (MpxValue* value, guint newval)
{
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_INTEGER))
    return;
  mpz_set_ui (value->integer, newval);
}

G_GNUC_INTERNAL
void
mpx_value_set_double (MpxValue* value, gdouble newval)
{
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_REAL))
    return;
  mpf_set_d (value->real, newval);
}

G_GNUC_INTERNAL
void
mpx_value_set_string (MpxValue* value, const gchar* newval)
{
  switch (value->type)
  {
  case MPX_VALUE_TYPE_INTEGER:
    mpz_set_str (value->integer, newval, 10);
    break;
  case MPX_VALUE_TYPE_RATIONAL:
    mpq_set_str (value->rational, newval, 10);
    break;
  case MPX_VALUE_TYPE_REAL:
    mpf_set_str (value->real, newval, 10);
    break;
  }
}

G_GNUC_INTERNAL
guint
mpx_value_get_uint (MpxValue* value)
{
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_INTEGER))
    return (unsigned int) -1;
return mpz_get_ui (value->integer);
}

G_GNUC_INTERNAL
gdouble
mpx_value_get_double (MpxValue* value)
{
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_REAL))
    return (double) 0;
return mpf_get_d (value->real);
}

G_GNUC_INTERNAL
gchar*
mpx_value_get_string (MpxValue* value)
{
  switch (value->type)
  {
  case MPX_VALUE_TYPE_INTEGER:
    return mpz_get_str (NULL, 0, value->integer);
  case MPX_VALUE_TYPE_RATIONAL:
    return mpq_get_str (NULL, 0, value->rational);
  case MPX_VALUE_TYPE_REAL:
    return mpf_get_str (NULL, NULL, 10, 0, value->real);
  }
}

/*
 * Section
 * - z2q
 * - z2f
 * - q2f
 *
 */

G_GNUC_INTERNAL
void
mpx_value_z2q (MpxValue* value, MpxValue* result)
{
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_INTEGER))
    return;
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_RATIONAL))
    return;
  mpq_set_z (result->rational, value->integer);
}

G_GNUC_INTERNAL
void
mpx_value_z2f (MpxValue* value, MpxValue* result)
{
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_INTEGER))
    return;
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_REAL))
    return;
  mpf_set_z (result->real, value->integer);
}

G_GNUC_INTERNAL
void
mpx_value_q2f (MpxValue* value, MpxValue* result)
{
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_RATIONAL))
    return;
  if (!mpx_value_check_type (value, MPX_VALUE_TYPE_REAL))
    return;
  mpf_set_q (result->real, value->rational);
}

/*
 * Section
 * - add
 * - sub
 * - mul
 * - div
 * - pow
 * - root
 *
 */

G_GNUC_INTERNAL
void
mpx_value_add (MpxValue* value1, MpxValue* value2, MpxValue* result)
{
  int type = result->type;
  if (!mpx_value_check_type (value1, type))
    return;
  if (!mpx_value_check_type (value2, type))
    return;

  switch (type)
  {
  case MPX_VALUE_TYPE_INTEGER:
    mpz_add (result->integer, value1->integer, value2->integer);
    break;
  case MPX_VALUE_TYPE_RATIONAL:
    mpq_add (result->rational, value1->rational, value2->rational);
    break;
  case MPX_VALUE_TYPE_REAL:
    mpf_add (result->real, value1->real, value2->real);
    break;
  }
}

G_GNUC_INTERNAL
void
mpx_value_sub (MpxValue* value1, MpxValue* value2, MpxValue* result)
{
  int type = result->type;
  if (!mpx_value_check_type (value1, type))
    return;
  if (!mpx_value_check_type (value2, type))
    return;

  switch (type)
  {
  case MPX_VALUE_TYPE_INTEGER:
    mpz_sub (result->integer, value1->integer, value2->integer);
    break;
  case MPX_VALUE_TYPE_RATIONAL:
    mpq_sub (result->rational, value1->rational, value2->rational);
    break;
  case MPX_VALUE_TYPE_REAL:
    mpf_sub (result->real, value1->real, value2->real);
    break;
  }
}

G_GNUC_INTERNAL
void
mpx_value_mul (MpxValue* value1, MpxValue* value2, MpxValue* result)
{
  int type = result->type;
  if (!mpx_value_check_type (value1, type))
    return;
  if (!mpx_value_check_type (value2, type))
    return;

  switch (type)
  {
  case MPX_VALUE_TYPE_INTEGER:
    mpz_mul (result->integer, value1->integer, value2->integer);
    break;
  case MPX_VALUE_TYPE_RATIONAL:
    mpq_mul (result->rational, value1->rational, value2->rational);
    break;
  case MPX_VALUE_TYPE_REAL:
    mpf_mul (result->real, value1->real, value2->real);
    break;
  }
}

G_GNUC_INTERNAL
void
mpx_value_div (MpxValue* value1, MpxValue* value2, MpxValue* result)
{
  int type = result->type;
  if (!mpx_value_check_type (value1, type))
    return;
  if (!mpx_value_check_type (value2, type))
    return;

  switch (type)
  {
  case MPX_VALUE_TYPE_INTEGER:
    mpz_div (result->integer, value1->integer, value2->integer);
    break;
  case MPX_VALUE_TYPE_RATIONAL:
    mpq_div (result->rational, value1->rational, value2->rational);
    break;
  case MPX_VALUE_TYPE_REAL:
    mpf_div (result->real, value1->real, value2->real);
    break;
  }
}
