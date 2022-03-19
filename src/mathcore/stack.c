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
#include <stack.h>

G_DEFINE_TYPE_WITH_CODE
(MathStack,
 math_stack,
 G_TYPE_OBJECT,
 );

static void
math_stack_class_finalize (GObject* pself)
{
  MathStack* self = MATH_STACK (pself);
  int i;
  for (i = 0; i < self->top; i++)
    math_stack_pop (self);
G_OBJECT_CLASS (math_stack_parent_class)->finalize (pself);
}

static void
math_stack_class_dispose (GObject* pself)
{
  MathStack* self = MATH_STACK (pself);
G_OBJECT_CLASS (math_stack_parent_class)->dispose (pself);
}

static void
math_stack_class_init (MathStackClass* klass)
{
  GObjectClass *oclass = G_OBJECT_CLASS (klass);

  oclass->finalize = math_stack_class_finalize;
  oclass->dispose = math_stack_class_dispose;
}

static void
math_stack_init (MathStack* self)
{
  self->head = NULL;
  self->top = 0;
}

/*
 * API
 *
 */

MathStack*
math_stack_new ()
{
  return
  (MathStack*)
  g_object_new
  (MATH_TYPE_STACK,
   NULL);
}

#define REVERT(index) (stack->top-(index)-1)

void
math_stack_push (MathStack* stack, MathValue* value)
{
  g_return_if_fail (MATH_IS_STACK (stack));
  g_return_if_fail (MATH_IS_VALUE (value));
  value = math_value_ref (value);

  g_return_if_fail (value->chain.next == NULL);
  g_return_if_fail (value->chain.prev == NULL);

  stack->head =
  (MathValueChain*)
  g_list_insert_before_link
  (&(stack->head->list_),
   &(stack->head->list_),
   &(value->chain.list_));
  stack->top++;
}

void
math_stack_pop (MathStack* stack)
{
  g_return_if_fail (MATH_IS_STACK (stack));
  g_return_if_fail (stack->top > 0);
  MathValue* value = stack->head->link;

  stack->head =
  (MathValueChain*)
  g_list_remove_link
  (&(stack->head->list_),
   &(stack->head->list_));
  math_value_unref (value);
  stack->top--;
}

MathValue*
math_stack_peek (MathStack* stack, gint index)
{
  g_return_val_if_fail (MATH_IS_STACK(stack), NULL);
  g_return_val_if_fail (index >= 0 && index < stack->top, NULL);
return g_list_nth_data (&(stack->head->list_), REVERT (index));
}

static inline
GList*
_list_append_link (GList* list, GList* new_list)
{
  GList *last;
  new_list->next = NULL;

  if (list)
    {
      last = g_list_last (list);
#if DEBUG == 1
      g_assert (last != NULL);
#endif // DEBUG
      last->next = new_list;
      new_list->prev = last;

      return list;
    }
  else
    {
      new_list->prev = NULL;
      return new_list;
    }
}

void
math_stack_insert (MathStack* stack, MathValue* value, gint index)
{
  g_return_if_fail (MATH_IS_STACK (stack));
  g_return_if_fail (MATH_IS_VALUE (value));
  g_return_if_fail (index >= 0 && index < stack->top);
  value = math_value_ref (value);
  index = REVERT (index);

  g_return_if_fail (value->chain.next == NULL);
  g_return_if_fail (value->chain.prev == NULL);

  if (index == stack->top - 1)
    stack->head =
    (MathValueChain*)
    _list_append_link
    (&(stack->head->list_),
     &(value->chain.list_));
  else
  if (index == 0)
    {
      math_stack_push (stack, value);
      return;
    }
  else
    {
      MathValueChain* tmp_list = NULL;
      MathValueChain* new_list = &(value->chain);

      tmp_list =
      (MathValueChain*)
      g_list_nth
      (&(stack->head->list_),
       index);
#if DEBUG == 1
      g_assert (tmp_list != NULL);
#endif // DEBUG

      new_list->prev = tmp_list->prev;
      tmp_list->prev->next = new_list;
      new_list->next = tmp_list;
      tmp_list->prev = new_list;
    }
  stack->top++;
}

void
math_stack_remove (MathStack* stack, guint index)
{
  g_return_if_fail (MATH_IS_STACK(stack));
  g_return_if_fail (index >= 0 && index < stack->top);
  MathValue* value = math_stack_peek (stack, index);

  stack->head =
  (MathValueChain*)
  g_list_remove_link
  (&(stack->head->list_),
   &(value->chain.list_));
  math_value_unref (value);
  stack->top--;
}
