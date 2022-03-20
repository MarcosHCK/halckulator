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
#ifndef __MATH_OBJECT__
#define __MATH_OBJECT__ 1
#include <glib-object.h>

#define MATH_TYPE_NIL (math_nil_get_type ())
#define MATH_NIL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MATH_TYPE_NIL, MathNil))
#define MATH_IS_NIL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MATH_TYPE_NIL))

typedef struct _MathNil MathNil;

#define MATH_TYPE_OBJECT (math_object_get_type ())
#define MATH_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MATH_TYPE_OBJECT, MathObject))
#define MATH_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MATH_TYPE_OBJECT, MathObjectClass))
#define MATH_IS_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MATH_TYPE_OBJECT))
#define MATH_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MATH_TYPE_OBJECT))
#define MATH_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MATH_TYPE_OBJECT, MathObjectClass))

typedef struct _MathObject MathObject;
typedef struct _MathObjectPrivate MathObjectPrivate;
typedef struct _MathObjectClass MathObjectClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
math_nil_get_type (void) G_GNUC_CONST;
GType
math_object_get_type (void) G_GNUC_CONST;

struct _MathObject
{
  GTypeInstance parent_instance;
  gint ref_count;

  /*<private>*/
  MathObjectPrivate* priv;
};

struct _MathObjectClass
{
  GTypeClass parent_class;
  void (*finalize) (MathObject* object);
};

/*
 * API
 *
 */

gpointer
math_object_new (GType g_type);
gpointer
math_object_ref (gpointer object);
void
math_object_unref (gpointer object);

/*
 * list API
 *
 */

gpointer
math_object_append (gpointer head, gpointer link) G_GNUC_WARN_UNUSED_RESULT;
gpointer
math_object_prepend (gpointer head, gpointer link) G_GNUC_WARN_UNUSED_RESULT;
gpointer
math_object_insert (gpointer head, gpointer link, gint position) G_GNUC_WARN_UNUSED_RESULT;
gpointer
math_object_remove (gpointer head, gpointer link) G_GNUC_WARN_UNUSED_RESULT;
gpointer
math_object_nth (gpointer head, gint n);
gint
math_object_length (gpointer head);

#if defined(glib_typeof)
/* Make reference APIs type safe with macros */
# define math_object_ref(obj) ((glib_typeof (obj)) (math_object_ref) (obj))
# define math_object_append(obj,link) ((glib_typeof (obj)) (math_object_append) (obj,link))
# define math_object_prepend(obj,link) ((glib_typeof (obj)) (math_object_prepend) (obj,link))
# define math_object_insert(obj,link,position) ((glib_typeof (obj)) (math_object_insert) (obj,link,position))
# define math_object_remove(obj,link) ((glib_typeof (obj)) (math_object_remove) (obj,link))
# define math_object_nth(obj, n) ((glib_typeof (obj)) (math_object_nth) (obj, n))
#endif

#if __cplusplus
}
#endif // __cplusplus

#endif // __MATH_OBJECT__
