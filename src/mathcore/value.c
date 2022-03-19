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
#include <value.h>

static void
math_value_class_init (MathValueClass* klass);
static void
math_value_init (MathValue* self);

static GType
math_value_get_type_once (void)
{
  GType g_type;

	static const
  GTypeInfo __info__ =
  {
    sizeof (MathValueClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) math_value_class_init,
    (GClassFinalizeFunc) NULL,
    NULL,
    sizeof (MathValue),
    0,
    (GInstanceInitFunc) math_value_init,
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
   "MathValue",
   &__info__,
   &__fundamental__,
   G_TYPE_FLAG_ABSTRACT);
return g_type;
}

GType
math_value_get_type (void)
{
	static volatile gsize __g_type__ = 0;
	if (g_once_init_enter (&__g_type__))
    {
		  GType g_type;
      g_type = math_value_get_type_once();
      g_once_init_leave (&__g_type__, g_type);
	  }
return (GType) __g_type__;
}

static void
math_value_class_finalize (MathValue* self)
{

}

static void
math_value_class_init (MathValueClass* klass)
{
  klass->finalize = math_value_class_finalize;
}

static void
math_value_init (MathValue* self)
{
  self->ref_count = 1;
  self->chain.link = self;
  self->chain.next = NULL;
  self->chain.prev = NULL;
}

/*
 * API
 *
 */

MathValue*
math_value_new (GType g_type)
{
  g_return_val_if_fail (g_type_is_a (g_type, MATH_TYPE_VALUE), NULL);
  return (MathValue*) g_type_create_instance (g_type);
}

gpointer
math_value_ref (gpointer value)
{
  g_return_val_if_fail (MATH_IS_VALUE (value), NULL);
  MathValue* self = (MathValue*) value;
  g_atomic_ref_count_inc (&(self->ref_count));
return value;
}

void
math_value_unref (gpointer value)
{
  g_return_if_fail (MATH_IS_VALUE (value));
  MathValue* self = (MathValue*) value;
  if (g_atomic_ref_count_dec (&(self->ref_count)))
    {
      MATH_VALUE_GET_CLASS (value)->finalize (value);
      g_type_free_instance ((GTypeInstance*) value);
    }
}
