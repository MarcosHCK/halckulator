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
#ifndef __MATH_CLONABLE__
#define __MATH_CLONABLE__ 1
#include <glib-object.h>

#define MATH_TYPE_CLONABLE (math_clonable_get_type ())
#define MATH_CLONABLE(obj) (G_TYPE_CHECK_INSTANCE_CAST (obj, MATH_TYPE_CLONABLE, MathClonable))
#define MATH_IS_CLONABLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE (obj, MATH_TYPE_CLONABLE))
#define MATH_CLONABLE_GET_IFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE (obj, MATH_TYPE_CLONABLE, MathClonableIface))

typedef struct _MathClonable MathClonable;
typedef struct _MathClonableIface MathClonableIface;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
math_clonable_get_type (void) G_GNUC_CONST;

struct _MathClonableIface
{
  GTypeInterface parent_iface;
  MathClonable* (*clone) (MathClonable* clonable);
};

/*
 * API
 *
 */

gpointer
math_clonable_clone (gpointer object);

#if defined(glib_typeof)
/* Make reference APIs type safe with macros */
# define math_clonable_clone(obj) ((glib_typeof (obj)) (math_clonable_clone) (obj))
#endif

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_CLONABLE__
