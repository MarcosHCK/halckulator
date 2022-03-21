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

static void
math_clonable_default_init (MathClonableIface* iface);
typedef struct _MathClonableIface MathClonableInterface;

G_DEFINE_INTERFACE
(MathClonable,
 math_clonable,
 MATH_TYPE_OBJECT);

static MathClonable*
math_clonable_default_clone (MathClonable* clonable)
{
  MathObject* object = MATH_OBJECT (clonable);
  return (MathClonable*) math_object_ref (object);
}

static void
math_clonable_default_init (MathClonableIface* iface)
{
  iface->clone = math_clonable_default_clone;
}

/*
 * API
 *
 */

gpointer
(math_clonable_clone) (gpointer object)
{
  g_return_val_if_fail (MATH_IS_CLONABLE (object), NULL);
  MathClonableIface* iface = MATH_CLONABLE_GET_IFACE (object);
return (gpointer) iface->clone ((MathClonable*) object);
}
