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
#include <internal.h>
#include <object.h>

typedef struct _MathNilClass MathNilClass;

struct _MathNil
{
  MathObject parent_instance;
};

struct _MathNilClass
{
  MathObjectClass parent_class;
};

G_DEFINE_TYPE
(MathNil,
 math_nil,
 MATH_TYPE_OBJECT);

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
