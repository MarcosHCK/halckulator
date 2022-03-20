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
#include <object.h>

typedef union _Chain Chain;

struct _MathObjectPrivate
{
  union _Chain
  {
    GList list_;
    struct
    {
      MathObject* link;
      Chain* next;
      Chain* prev;
    };
  } chain;
};

G_STATIC_ASSERT (G_STRUCT_OFFSET (Chain, link) == G_STRUCT_OFFSET (GList, data));
G_STATIC_ASSERT (G_STRUCT_OFFSET (Chain, next) == G_STRUCT_OFFSET (GList, next));
G_STATIC_ASSERT (G_STRUCT_OFFSET (Chain, prev) == G_STRUCT_OFFSET (GList, prev));

static void
math_object_class_init (MathObjectClass* klass);
static void
math_object_init (MathObject* self);

static gint math_object_private_offset = 0;

static inline gpointer
math_object_get_instance_private (MathObject* self)
{
	return G_STRUCT_MEMBER_P (self, math_object_private_offset);
}

GType
math_object_get_type (void)
{
  static volatile
  gsize __typeid__ = 0;
  if (g_once_init_enter (&__typeid__))
    {
      GType g_type;

      static const
      GTypeInfo __info__ =
      {
        sizeof (MathObjectClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) math_object_class_init,
        (GClassFinalizeFunc) NULL,
        NULL,
        sizeof (MathObject),
        0,
        (GInstanceInitFunc) math_object_init,
      };

      static const
      GTypeFundamentalInfo __fundamental__ =
      {
        (G_TYPE_FLAG_CLASSED
        | G_TYPE_FLAG_INSTANTIATABLE
        | G_TYPE_FLAG_DERIVABLE
        | G_TYPE_FLAG_DEEP_DERIVABLE),
      };

      g_type =
      g_type_register_fundamental
      (g_type_fundamental_next(),
       "MathObject",
       &__info__,
       &__fundamental__,
       G_TYPE_FLAG_ABSTRACT);

      math_object_private_offset =
      g_type_add_instance_private (g_type, sizeof (MathObjectPrivate));
      g_once_init_leave (&__typeid__, g_type);
    }
return (GType) __typeid__;
}

static void
math_object_class_finalize (MathObject* self)
{
}

static void
math_object_class_init (MathObjectClass* klass)
{
  g_type_class_adjust_private_offset (klass, &math_object_private_offset);
  klass->finalize = math_object_class_finalize;
}

static void
math_object_init (MathObject* self)
{
  self->priv = math_object_get_instance_private (self);
  self->ref_count = 1;
  self->priv->chain.link = self;
  self->priv->chain.next = NULL;
  self->priv->chain.prev = NULL;
}

/*
 * API
 *
 */

gpointer
math_object_new (GType g_type)
{
  g_return_val_if_fail (g_type_is_a (g_type, MATH_TYPE_OBJECT), NULL);
  return (gpointer) g_type_create_instance (g_type);
}

gpointer
(math_object_ref) (gpointer object)
{
  g_return_val_if_fail (MATH_IS_OBJECT (object), NULL);
  g_atomic_ref_count_inc (&( ((MathObject*) object)->ref_count ));
return object;
}

void
(math_object_unref) (gpointer object)
{
  g_return_if_fail (MATH_IS_OBJECT (object));
  MathObject* self = (MathObject*) object;
  if (g_atomic_ref_count_dec (&( self->ref_count )))
    {
      MATH_OBJECT_GET_CLASS (object)->finalize (self);
      g_type_free_instance ((GTypeInstance*) self);
    }
}

static inline
GList*
_list_append_link (GList* list, GList* new_list)
{
  GList *last;
  new_list->next = NULL;

  if (list)
    {
      last = g_list_last (list);
#if DEBUG == 1
      g_assert (last != NULL);
#endif // DEBUG
      last->next = new_list;
      new_list->prev = last;

      return list;
    }
  else
    {
      new_list->prev = NULL;
      return new_list;
    }
}

static inline
GList*
_list_prepend_link (GList* list, GList* new_list)
{
  new_list->next = list;
  
  if (list)
    {
      new_list->prev = list->prev;
      if (list->prev)
        list->prev->next = new_list;
      list->prev = new_list;
    }
  else
    {
      new_list->prev = NULL;
    }
return new_list;
}

static inline
GList*
_list_insert_link (GList* list, GList* new_list, gint position)
{
  GList *tmp_list;

  if (position < 0)
    return _list_append_link (list, new_list);
  else if (position == 0)
    return _list_prepend_link (list, new_list);

  tmp_list = g_list_nth (list, position);
  if (!tmp_list)
    return _list_append_link (list, new_list);

  new_list->prev = tmp_list->prev;
  tmp_list->prev->next = new_list;
  new_list->next = tmp_list;
  tmp_list->prev = new_list;
return list;
}

gpointer
(math_object_append) (gpointer head, gpointer link)
{
  g_return_val_if_fail (head == NULL || MATH_IS_OBJECT (head), NULL);
  g_return_val_if_fail (MATH_IS_OBJECT (link), NULL);
  MathObjectPrivate* phead = (head != NULL) ? ((MathObject*) head)->priv : NULL;
  MathObjectPrivate* plink = ((MathObject*) link)->priv;
  GList* newhead = NULL;

  g_return_val_if_fail (plink->chain.next == NULL, NULL);
  g_return_val_if_fail (plink->chain.prev == NULL, NULL);
  link = math_object_ref (link);

  newhead =
  _list_append_link
  ((head != NULL) ? &(phead->chain.list_) : NULL,
   &(plink->chain.list_));
return (newhead) ? newhead->data : NULL;
}

gpointer
(math_object_prepend) (gpointer head, gpointer link)
{
  g_return_val_if_fail (head == NULL || MATH_IS_OBJECT (head), NULL);
  g_return_val_if_fail (MATH_IS_OBJECT (link), NULL);
  MathObjectPrivate* phead = (head != NULL) ? ((MathObject*) head)->priv : NULL;
  MathObjectPrivate* plink = ((MathObject*) link)->priv;
  GList* newhead = NULL;

  g_return_val_if_fail (plink->chain.next == NULL, NULL);
  g_return_val_if_fail (plink->chain.prev == NULL, NULL);
  link = math_object_ref (link);

  newhead =
  _list_prepend_link
  ((head != NULL) ? &(phead->chain.list_) : NULL,
   &(plink->chain.list_));
return (newhead) ? newhead->data : NULL;
}

gpointer
(math_object_insert) (gpointer head, gpointer link, gint position)
{
  g_return_val_if_fail (head == NULL || MATH_IS_OBJECT (head), NULL);
  g_return_val_if_fail (MATH_IS_OBJECT (link), NULL);
  MathObjectPrivate* phead = (head != NULL) ? ((MathObject*) head)->priv : NULL;
  MathObjectPrivate* plink = ((MathObject*) link)->priv;
  GList* newhead = NULL;

  g_return_val_if_fail (plink->chain.next == NULL, NULL);
  g_return_val_if_fail (plink->chain.prev == NULL, NULL);
  link = math_object_ref (link);

  newhead =
  _list_insert_link
  ((head != NULL) ? &(phead->chain.list_) : NULL,
   &(plink->chain.list_),
   position);
return (newhead) ? newhead->data : NULL;
}

gpointer
(math_object_remove) (gpointer head, gpointer link)
{
  if (head == NULL) return NULL;
  g_return_val_if_fail (MATH_IS_OBJECT (head), NULL);
  g_return_val_if_fail (MATH_IS_OBJECT (link), NULL);
  MathObjectPrivate* phead = ((MathObject*) head)->priv;
  MathObjectPrivate *plink = ((MathObject*) link)->priv;
  GList* newhead = NULL;

  newhead =
  g_list_remove_link
  (&(phead->chain.list_),
   &(plink->chain.list_));
  math_object_unref (link);
return (newhead) ? newhead->data : NULL;
}

gpointer
(math_object_nth) (gpointer head, gint n)
{
  if (head == NULL) return NULL;
  g_return_val_if_fail (MATH_IS_OBJECT (head), NULL);
  MathObjectPrivate* phead = ((MathObject*) head)->priv;
  GList* newhead = g_list_nth (&(phead->chain.list_), n);
return (newhead) ? newhead->data : NULL;
}

gint
math_object_length (gpointer head)
{
  if (head == NULL) return 0;
  g_return_val_if_fail (MATH_IS_OBJECT (head), 0);
  MathObjectPrivate* phead = ((MathObject*) head)->priv;
return g_list_length (&(phead->chain.list_));
}
