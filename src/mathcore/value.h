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
#ifndef __MATH_VALUE__
#define __MATH_VALUE__ 1
#include <glib-object.h>

#define MATH_TYPE_VALUE (math_value_get_type ())
#define MATH_VALUE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MATH_TYPE_VALUE, MathValue))
#define MATH_VALUE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MATH_TYPE_VALUE, MathValueClass))
#define MATH_IS_VALUE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MATH_TYPE_VALUE))
#define MATH_IS_VALUE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MATH_TYPE_VALUE))
#define MATH_VALUE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MATH_TYPE_VALUE, MathValueClass))

typedef struct _MathValue MathValue;
typedef struct _MathValueClass MathValueClass;
typedef union  _MathValueChain MathValueChain;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
math_value_get_type (void) G_GNUC_CONST;

struct _MathValue
{
  GTypeInstance parent_instance;
  gint ref_count; /*<atomic>*/

  /*<private>*/
  union _MathValueChain
  {
    GList list_;
    struct
    {
      MathValue* link;
      MathValueChain* next;
      MathValueChain* prev;
    };
  } chain;
};

struct _MathValueClass
{
  GTypeClass parent_class;
  void (*finalize) (MathValue* value);
};

/*
 * API
 *
 */

MathValue*
math_value_new (GType g_type);
gpointer
math_value_ref (gpointer value);
void
math_value_unref (gpointer value);

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_STACK_VALUE__
