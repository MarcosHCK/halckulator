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
#include <clonable.h>
#include <internal.h>
#include <object.h>

#define MATH_NIL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MATH_TYPE_CORE, MathNilClass))
#define MATH_IS_NIL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MATH_TYPE_CORE))
#define MATH_NIL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MATH_TYPE_CORE, MathNilClass))
typedef struct _MathNilClass MathNilClass;

static void
math_clonable_iface_init (MathClonableIface* iface);

struct _MathNil
{
  MathObject parent_instance;
};

struct _MathNilClass
{
  MathObjectClass parent_class;
};

G_DEFINE_TYPE_WITH_CODE
(MathNil,
 math_nil,
 MATH_TYPE_OBJECT,
 G_IMPLEMENT_INTERFACE
 (MATH_TYPE_CLONABLE,
  math_clonable_iface_init));

static void
math_clonable_iface_init (MathClonableIface* iface) { }

static void
math_nil_class_init (MathNilClass* klass) { }

static void
math_nil_init (MathNil* self) { }

/*
 * API
 *
 */

void
math_core_pushnil (MathCore* core)
{
  g_return_if_fail (MATH_IS_CORE (core));
  MathNil* nil = math_object_new (MATH_TYPE_NIL);
  _math_core_push (core, nil);
  math_object_unref (nil);
}

gboolean
math_core_isnil (MathCore* core, int index)
{
  g_return_val_if_fail (MATH_IS_CORE (core), FALSE);
  g_return_val_if_fail ((index = validate_index (index)) >= 0, FALSE);
  MathObject* value = _math_core_peek (core, index);
return MATH_IS_NIL (value);
}

gboolean
math_core_isnone (MathCore* core, int index)
{
  g_return_val_if_fail (MATH_IS_CORE (core), FALSE);
return validate_index (index) < 0;
}
