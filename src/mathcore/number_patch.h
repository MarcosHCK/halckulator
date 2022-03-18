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
#ifndef __NUMBER_PATCH__
#define __NUMBER_PATCH__ 1
#include <glib.h>
#include <gmp.h>

typedef enum
{
  MPX_VALUE_TYPE_INTEGER,
  MPX_VALUE_TYPE_RATIONAL,
  MPX_VALUE_TYPE_REAL,
} MpxValueType;

typedef struct
{
  union
  {
    int __base;
    mpz_t integer;
    mpq_t rational;
    mpf_t real;
  };

  MpxValueType type;
} MpxValue;

#if __cplusplus
extern "C" {
#endif // __cplusplus

G_GNUC_INTERNAL
void
mpx_value_init (MpxValue* value);
G_GNUC_INTERNAL
void
mpx_value_clear (MpxValue* value);
G_GNUC_INTERNAL
void
mpx_value_clone (MpxValue* value, MpxValue* result);

G_GNUC_INTERNAL
gboolean
mpx_value_check_type (MpxValue* value, MpxValueType type);

G_GNUC_INTERNAL
void
mpx_value_z2q (MpxValue* value, MpxValue* result);
G_GNUC_INTERNAL
void
mpx_value_z2f (MpxValue* value, MpxValue* result);
G_GNUC_INTERNAL
void
mpx_value_q2f (MpxValue* value, MpxValue* result);

G_GNUC_INTERNAL
void
mpx_value_set_numerator (MpxValue* value, MpxValue* newvalue);
G_GNUC_INTERNAL
void
mpx_value_get_numerator (MpxValue* value, MpxValue* result);
G_GNUC_INTERNAL
void
mpx_value_set_denominator (MpxValue* value, MpxValue* newvalue);
G_GNUC_INTERNAL
void
mpx_value_get_denominator (MpxValue* value, MpxValue* result);

G_GNUC_INTERNAL
void
mpx_value_set_uint (MpxValue* value, guint newval);
G_GNUC_INTERNAL
void
mpx_value_set_double (MpxValue* value, gdouble newval);
G_GNUC_INTERNAL
void
mpx_value_set_string (MpxValue* value, const gchar* newval);
G_GNUC_INTERNAL
guint
mpx_value_get_uint (MpxValue* value);
G_GNUC_INTERNAL
gdouble
mpx_value_get_double (MpxValue* value);
G_GNUC_INTERNAL
gchar*
mpx_value_get_string (MpxValue* value);

G_GNUC_INTERNAL
void
mpx_value_add (MpxValue* value1, MpxValue* value2, MpxValue* result);
G_GNUC_INTERNAL
void
mpx_value_sub (MpxValue* value1, MpxValue* value2, MpxValue* result);
G_GNUC_INTERNAL
void
mpx_value_mul (MpxValue* value1, MpxValue* value2, MpxValue* result);
G_GNUC_INTERNAL
void
mpx_value_div (MpxValue* value1, MpxValue* value2, MpxValue* result);

#if __cplusplus
}
#endif // __cplusplus

#endif // __NUMBER_PATCH__
