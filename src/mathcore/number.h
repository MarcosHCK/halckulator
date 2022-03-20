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
#include <object.h>

#define MATH_NUMBER_ERROR (math_number_error_quark ())

typedef enum
{
  MATH_NUMBER_ERROR_FAILED,
  MATH_NUMBER_ERROR_PARSE_ERROR,
} MathNumberError;

#define MATH_TYPE_NUMBER (math_number_get_type ())
#define MATH_NUMBER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MATH_TYPE_NUMBER, MathNumber))
#define MATH_NUMBER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MATH_TYPE_NUMBER, MathNumberClass))
#define MATH_IS_NUMBER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MATH_TYPE_NUMBER))
#define MATH_IS_NUMBER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MATH_TYPE_NUMBER))
#define MATH_NUMBER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MATH_TYPE_NUMBER, MathNumberClass))

typedef struct _MathNumber MathNumber;
typedef struct _MathNumberPrivate MathNumberPrivate;
typedef struct _MathNumberClass MathNumberClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GQuark
math_number_error_quark (void) G_GNUC_CONST;
GType
math_number_get_type (void) G_GNUC_CONST;

struct _MathNumber
{
  MathObject parent_instance;
  MathNumberPrivate* priv;
};

struct _MathNumberClass
{
  MathObjectClass parent_class;
};

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_NUMBER__
