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
#ifndef __MATH_FUNCTION__
#define __MATH_FUNCTION__ 1
#include <object.h>

#define MATH_TYPE_CLOSURE (math_closure_get_type ())
#define MATH_CLOSURE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MATH_TYPE_CLOSURE, MathClosure))
#define MATH_CLOSURE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MATH_TYPE_CLOSURE, MathClosureClass))
#define MATH_IS_CLOSURE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MATH_TYPE_CLOSURE))
#define MATH_IS_CLOSURE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MATH_TYPE_CLOSURE))
#define MATH_CLOSURE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MATH_TYPE_CLOSURE, MathClosureClass))

typedef struct _MathClosure MathClosure;
typedef struct _MathClosurePrivate MathClosurePrivate;
typedef struct _MathClosureClass MathClosureClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

struct _MathClosure
{
  MathObject parent_instance;
  MathClosurePrivate* priv;
};

struct _MathClosureClass
{
  MathObjectClass parent_class;
};

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_FUNCTION__
