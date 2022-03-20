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
#include <closure.h>
#include <internal.h>

G_DEFINE_QUARK
(math-core-current-closure-quark,
 math_core_current_closure);

struct _MathClosurePrivate
{
  MathCFunction callback;
};

G_DEFINE_TYPE_WITH_PRIVATE
(MathClosure,
 math_closure,
 MATH_TYPE_OBJECT);

static void
math_closure_class_init (MathClosureClass* klass)
{
}

static void
math_closure_init (MathClosure* self)
{
  self->priv = math_closure_get_instance_private (self);
  self->priv->callback = NULL;
}

/*
 * API
 *
 */

void
math_core_pushcfunction (MathCore* core, MathCFunction cclosure)
{
  g_return_if_fail (MATH_CORE (core));
  g_return_if_fail (cclosure != NULL);
  MathClosure* closure = math_object_new (MATH_TYPE_CLOSURE);
  closure->priv->callback = cclosure;
  _math_core_push (core, closure);
  math_object_unref (closure);
}

static inline void
leave_n_items (MathCore* core, int n)
{
  int i, top = math_core_gettop (core);
  if (n >= top)
    math_core_settop (core, n);
  else while (top-- > n)
    math_core_remove (core, 0);
}

MathClosureResult
math_core_call (MathCore* core, int n_args, int n_res)
{
  g_return_val_if_fail (MATH_IS_CORE (core), MATH_CLOSURE_ERROR);
  g_return_val_if_fail (n_args >= 0, MATH_CLOSURE_ERROR);
  g_return_val_if_fail (math_core_gettop (core) >= (n_args + 1), MATH_CLOSURE_ERROR);
  g_return_val_if_fail (n_res == MATH_CLOSURE_MULTIRET || n_res >= 0, MATH_CLOSURE_ERROR);
  MathClosure* closure = _math_core_peek (core, -n_args-1);
  g_return_val_if_fail (MATH_IS_CLOSURE (closure), MATH_CLOSURE_ERROR);
  MathClosureResult result;
  int i, oldindex;

  oldindex =
  switch_index (n_args);
  oldindex -= (n_args + 1);
  {
    int result_;

    result_ =
    closure->priv->callback (core);
    if (result < 0)
      {
        math_core_settop (core, 0);
        result = MATH_CLOSURE_ERROR;
      }
    else
      {
        leave_n_items (core, result_);
        if (n_res == MATH_CLOSURE_MULTIRET)
          oldindex += result_;
        else
          {
            math_core_settop (core, n_res);
            oldindex += n_res;
          }
        result = MATH_CLOSURE_SUCCESS;
      } 
  }
  switch_index (oldindex);
return result;
}
