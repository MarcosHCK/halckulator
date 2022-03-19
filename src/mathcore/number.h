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
#ifndef __MATH_NUMBER__
#define __MATH_NUMBER__ 1
#include <numberkind.h>
#include <value.h>
#include <gmp.h>

#define MATH_TYPE_NUMBER (math_number_get_type ())
#define MATH_NUMBER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MATH_TYPE_NUMBER, MathNumber))
#define MATH_NUMBER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MATH_TYPE_NUMBER, MathNumberClass))
#define MATH_IS_NUMBER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MATH_TYPE_NUMBER))
#define MATH_IS_NUMBER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MATH_TYPE_NUMBER))
#define MATH_NUMBER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MATH_TYPE_NUMBER, MathNumberClass))

typedef struct _MathNumber MathNumber;
typedef struct _MathNumberClass MathNumberClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
math_number_get_type (void) G_GNUC_CONST;

struct _MathNumber
{
  MathValue parent_instance;

  /*<private>*/
  MathNumberKind kind;
  gint inited : 1;
  union
  {
    mpz_t integer;
    mpq_t rational;
    mpf_t real;
  };
};

struct _MathNumberClass
{
  MathValueClass parent_class;
};

MathNumber*
math_number_new (MathNumberKind kind);
gboolean
math_number_check_kind (MathNumber* number, MathNumberKind kind);
void
math_number_set_uint (MathNumber* number, guint value);
guint
math_number_get_uint (MathNumber* number);
void
math_number_set_num (MathNumber* number, MathNumber* num);
MathNumber*
math_number_get_num (MathNumber* number);
void
math_number_set_den (MathNumber* number, MathNumber* den);
MathNumber*
math_number_get_den (MathNumber* number);
void
math_number_set_double (MathNumber* number, gdouble value);
gdouble
math_number_get_double (MathNumber* number);
void
math_number_set_string (MathNumber* number, const gchar* value, gint base);
gchar*
math_number_get_string (MathNumber* number, gint base);

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_NUMBER__
