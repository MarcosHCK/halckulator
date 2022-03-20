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
#include <core.h>
#include <internal.h>
#include <object.h>

struct _MathCore
{
  GObject parent_instance;
  MathObject* head;
  gint top;
};

struct _MathCoreClass
{
  GObjectClass parent_class;
};

G_DEFINE_TYPE
(MathCore,
 math_core,
 G_TYPE_OBJECT);

static void
math_core_class_finalize (GObject* pself)
{
  MathCore* self = MATH_CORE (pself);
  MathObject* head = self->head;
  while (head != NULL)
    {
      head = math_object_remove (head, head);
    }
G_OBJECT_CLASS (math_core_parent_class)->finalize (pself);
}

static void
math_core_class_init (MathCoreClass* klass)
{
  GObjectClass* oclass = G_OBJECT_CLASS (klass);

  oclass->finalize = math_core_class_finalize;
}

static void
math_core_init (MathCore* self)
{
  self->head = NULL;
  self->top = 0;
}

/*
 * internal API
 *
 */

#ifdef validate_index
# undef validate_index
#endif // validate_index
#define validate_index(index) ((validate_index)(core,index))
#define reverse(index) (core->top-((index))-1)

static inline
int
(validate_index) (MathCore* core, gint index)
{
  if (index >= 0)
    {
      if (core->top > index)
        return index;
    }
  else
    {
      return core->top + index;
    }
return -1;
}

G_GNUC_INTERNAL
int
_math_core_checkidx (MathCore* core, int index)
{
  return (validate_index) (core, index); 
}

G_GNUC_INTERNAL
void
_math_core_push (MathCore* core, gpointer object)
{
  g_return_if_fail (MATH_IS_OBJECT (object));
  core->head = math_object_prepend (core->head, (MathObject*) object);
  ++core->top;
}

G_GNUC_INTERNAL
void
_math_core_pop (MathCore* core)
{
  core->head = math_object_remove (core->head, core->head);
  --core->top;
}

G_GNUC_INTERNAL
gpointer
_math_core_peek (MathCore* core, gint index)
{
  g_return_val_if_fail ((index = validate_index (index)) >= 0, NULL);
#if DEBUG == 1
  MathObject* object = math_object_nth (core->head, reverse (index));
  g_assert (object != NULL);
return object;
#else
return math_object_nth (core->head, reverse (index));
#endif // DEBUG
}

/*
 * API
 *
 */

MathCore*
math_core_new ()
{
  return (MathCore*)
  g_object_new (MATH_TYPE_CORE, NULL);
}

int
math_core_gettop (MathCore* core)
{
  g_return_val_if_fail (MATH_IS_CORE (core), -1);
return core->top;
}

void
math_core_settop (MathCore* core, int newtop)
{
  g_return_if_fail (MATH_IS_CORE (core));
  g_return_if_fail (newtop >= 0);
  int i, top = math_core_gettop (core);

  if (newtop > top)
    {
      int extra = newtop - top;
      for (i = 0; i < extra; i++)
      {
        math_core_pushnil (core);
      }
    }
  else
    {
      int left = top - newtop;
      for (i = 0; i < left; i++)
      {
        _math_core_pop (core);
      }
    }
}

void
math_core_pop (MathCore* core, int n_values)
{
  g_return_if_fail (MATH_IS_CORE (core));
  g_return_if_fail (core->top >= n_values);
  math_core_settop (core, core->top - n_values);
}

void
math_core_remove (MathCore* core, int index)
{
  g_return_if_fail (MATH_IS_CORE (core));
  g_return_if_fail ((index = validate_index (index)) >= 0);
  MathObject* nth = _math_core_peek (core, index);
  core->head = math_object_remove (core->head, nth);
  --core->top;
}

void
math_core_insert (MathCore* core, int index)
{
  g_return_if_fail (MATH_IS_CORE (core));
  g_return_if_fail ((index = validate_index (index)) >= 0);
  g_return_if_fail (core->top > 0);
  MathObject* object = NULL;

  object = math_object_nth (core->head, 0 /* top */);
  object = math_object_ref (object);
  core->head = math_object_remove (core->head, object);
  core->head = math_object_insert (core->head, object, reverse (index));
  math_object_unref (object);
}
