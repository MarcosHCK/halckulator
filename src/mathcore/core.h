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
#define MATH_IS_CORE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MATH_TYPE_CORE))

typedef struct _MathCore MathCore;

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
math_core_pushvalue (MathCore* core, int index);
void
math_core_pop (MathCore* core, int n_values);
void
math_core_remove (MathCore* core, int index);
void
math_core_insert (MathCore* core, int index);

/*
 * C-Math API
 *
 */

gboolean
math_core_isnone (MathCore* core, int index);
void
math_core_pushnil (MathCore* core);
gboolean
math_core_isnil (MathCore* core, int index);
void
math_core_pushnumber_uint (MathCore* core, unsigned int value);
unsigned int
math_core_tonumber_uint (MathCore* core, int index);
void
math_core_pushnumber_double (MathCore* core, double value);
double
math_core_tonumber_double (MathCore* core, int index);
gboolean
math_core_pushnumber_string (MathCore* core, const gchar* value, int base);
gchar*
math_core_tonumber_string (MathCore* core, int index, int base);
gboolean
math_core_isnumber (MathCore* core, int index);

#define math_core_isnoneornil(core,index) (math_core_isnone ((core),(index))||math_core_isnil ((core),(index)))

/*
 * Closures
 *
 */

typedef int (*MathCFunction)(MathCore *core);

#define MATH_CLOSURE_MULTIRET (-1)

typedef enum
{
  MATH_CLOSURE_SUCCESS = 0,
  MATH_CLOSURE_ERROR = -1,
} MathClosureResult;

void
math_core_pushcfunction (MathCore* core, MathCFunction cclosure);
MathClosureResult
math_core_call (MathCore* core, int n_args, int n_results);

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_CORE__
