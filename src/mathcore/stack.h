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
#ifndef __MATH_STACK__
#define __MATH_STACK__ 1
#include <glib-object.h>
#include <value.h>

#define MATH_TYPE_STACK (math_stack_get_type ())
#define MATH_STACK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MATH_TYPE_STACK, MathStack))
#define MATH_STACK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MATH_TYPE_STACK, MathStackClass))
#define MATH_IS_STACK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MATH_TYPE_STACK))
#define MATH_IS_STACK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MATH_TYPE_STACK))
#define MATH_STACK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MATH_TYPE_STACK, MathStackClass))

typedef struct _MathStack MathStack;
typedef struct _MathStackClass MathStackClass;
typedef union  _MathStackEntry MathStackEntry;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
math_stack_get_type (void) G_GNUC_CONST;

struct _MathStack
{
  GObject parent_instance;

  /*<private>*/
  MathValueChain* head;
  guint top;
};

struct _MathStackClass
{
  GObjectClass parent_class;
};

/*
 * API
 *
 */

MathStack *
math_stack_new();
void
math_stack_push (MathStack* stack, MathValue* value);
void
math_stack_pop (MathStack* stack);
MathValue*
math_stack_peek (MathStack* stack, gint index);
void
math_stack_insert (MathStack* stack, MathValue* value, gint index);
void
math_stack_remove (MathStack* stack, guint index);

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_STACK__
