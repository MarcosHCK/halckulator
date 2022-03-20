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
#ifndef __MATH_CORE__
#define __MATH_CORE__ 1
#include <glib-object.h>

#define MATH_TYPE_CORE (math_core_get_type ())
#define MATH_CORE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MATH_TYPE_CORE, MathCore))
#define MATH_CORE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MATH_TYPE_CORE, MathCoreClass))
#define MATH_IS_CORE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MATH_TYPE_CORE))
#define MATH_IS_CORE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MATH_TYPE_CORE))
#define MATH_CORE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MATH_TYPE_CORE, MathCoreClass))

typedef struct _MathCore MathCore;
typedef struct _MathCoreClass MathCoreClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
math_core_get_type (void) G_GNUC_CONST;

/*
 * API
 *
 */

MathCore*
math_core_new ();
int
math_core_gettop (MathCore* core);
void
math_core_settop (MathCore* core, int newtop);
void
math_core_remove (MathCore* core, int index);
void
math_core_insert (MathCore* core, int index);

/*
 * C -> Math
 *
 */

void
math_core_pushnil (MathCore* core);

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_CORE__
