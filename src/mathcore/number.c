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
#include <number.h>
#include <numberext.h>

G_DEFINE_QUARK
(math-number-error-quark,
 math_number_error);

G_DEFINE_TYPE_WITH_PRIVATE
(MathNumber,
 math_number,
 MATH_TYPE_OBJECT);

static void
math_number_class_finalize (MathObject* pself)
{
  MathNumber* self = MATH_NUMBER (pself);
  MathNumberPrivate* priv = self->priv;
  switch (priv->kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    mpz_clear (priv->integer);
    break;
  case MATH_NUMBER_KIND_RATIONAL:
    mpq_clear (priv->rational);
    break;
  case MATH_NUMBER_KIND_REAL:
    mpf_clear (priv->real);
    break;
  }
MATH_OBJECT_CLASS (math_number_parent_class)->finalize (pself);
}

static void
math_number_class_init (MathNumberClass* klass)
{
  MathObjectClass* oclass = MATH_OBJECT_CLASS (klass);

  oclass->finalize = math_number_class_finalize;
}

static void
math_number_init (MathNumber* self)
{
  self->priv = math_number_get_instance_private (self);
}

/*
 * API
 *
 */

static inline
MathNumber*
_math_number_new (MathNumberKind kind)
{
  MathNumber* number;
  number = math_object_new (MATH_TYPE_NUMBER);
  number->priv->kind = kind;

  switch (kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    mpz_init (number->priv->integer);
    break;
  case MATH_NUMBER_KIND_RATIONAL:
    mpq_init (number->priv->rational);
    break;
  case MATH_NUMBER_KIND_REAL:
    mpf_init (number->priv->real);
    break;
  }
return number;
}

void
math_core_pushnumber_uint (MathCore* core, unsigned int value)
{
  g_return_if_fail (MATH_IS_CORE (core));
  MathNumber* n = _math_number_new (MATH_NUMBER_KIND_INTEGER);
  mpz_set_ui (n->priv->integer, value);
  _math_core_push (core, n);
  math_object_unref (n);
}

unsigned int
math_core_tonumber_uint (MathCore* core, int index)
{
  g_return_val_if_fail (MATH_IS_CORE (core), -1);
  g_return_val_if_fail ((index = validate_index (index)) >= 0, -1);
  MathNumber* number = _math_core_peek (core, index);
  g_return_val_if_fail (MATH_IS_NUMBER (number), -1);

  switch (number->priv->kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    return mpz_get_ui (number->priv->integer);
  case MATH_NUMBER_KIND_RATIONAL:
#if DEBUG == 1
    g_warning ("Loosing precision on conversion");
#endif // DEBUG
    {
      unsigned int result;
      mpz_t mpz;

      mpz_init (mpz);
      mpz_set_q (mpz, number->priv->rational);
      result = mpz_get_ui (mpz);
      mpz_clear (mpz);
      return result;
    }
    break;
  case MATH_NUMBER_KIND_REAL:
#if DEBUG == 1
    g_warning ("Loosing precision on conversion");
#endif // DEBUG
    return mpf_get_ui (number->priv->real);
  }
}

void
math_core_pushnumber_double (MathCore* core, double value)
{
  g_return_if_fail (MATH_IS_CORE (core));
  MathNumber* n = _math_number_new (MATH_NUMBER_KIND_REAL);
  mpf_set_d (n->priv->real, value);
  _math_core_push (core, n);
  math_object_unref (n);
}

double
math_core_tonumber_double (MathCore* core, int index)
{
  g_return_val_if_fail (MATH_IS_CORE (core), -1);
  g_return_val_if_fail ((index = validate_index (index)) >= 0, -1);
  MathNumber* number = _math_core_peek (core, index);
  g_return_val_if_fail (MATH_IS_NUMBER (number), -1);

  switch (number->priv->kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    return mpz_get_d (number->priv->integer);
  case MATH_NUMBER_KIND_RATIONAL:
    return mpq_get_d (number->priv->rational);
  case MATH_NUMBER_KIND_REAL:
    return mpf_get_d (number->priv->real);
  }
}

gboolean
math_core_pushnumber_string (MathCore* core, const gchar* value, int base)
{
  g_return_val_if_fail (MATH_IS_CORE (core), FALSE);
  g_return_val_if_fail (value != NULL, FALSE);

  size_t i, length = strlen (value);
  g_return_val_if_fail (g_utf8_validate (value, length, NULL), FALSE);

  const gchar* val = value;
  MathNumber* number = NULL;
  mpz_ptr num = NULL, den = NULL;
  gchar* next = NULL;
  int success = 0;
  gunichar c;

  do
  {
    c = g_utf8_get_char (val);
    if (c == 0)
      break;

    switch (c)
    {
    case '.':
      {
        number = _math_number_new (MATH_NUMBER_KIND_RATIONAL);
        num = mpq_numref (number->priv->rational);
        den = mpq_denref (number->priv->rational);

        /*
         * Numerator
         *
         */

        length -= g_utf8_skip[*(guchar*) val];
        next = g_malloc (length + 1);
        i = (size_t) (val - value);
        memset (next, '.', length);
        memcpy (&(next[0]), value, i);
        memcpy (&(next[i]), g_utf8_next_char (val), length - i);
        next[length] = 0;

        success = mpz_set_str (num, next, base);
        if (G_UNLIKELY (success < 0))
          {
            math_object_unref (number);
            g_free (next);
            return FALSE;
          }

        /*
         * Denominator
         *
         */

        length = g_utf8_strlen (val, -1);
        next = g_realloc (next, length + 1);
        memset (&(next[1]), '0', length - 1);
        next[0] = '1'; next[length] = 0;

        success = mpz_set_str (den, next, base);
        if (G_UNLIKELY (success < 0))
          {
            math_object_unref (number);
            g_free (next);
            return FALSE;
          }
        
        /*
         * Canonicalize and push it
         *
         */

        mpq_canonicalize (number->priv->rational);
        _math_core_push (core, number);
        math_object_unref (number);
        g_free (next);
        return TRUE;
      }
      break;
    }
  }
  while ((val = g_utf8_next_char (val)) != NULL);

  number = _math_number_new (MATH_NUMBER_KIND_INTEGER);
  mpz_set_str (number->priv->integer, value, base);
  _math_core_push (core, number);
  math_object_unref (number);
return TRUE;
}

gchar*
math_core_tonumber_string (MathCore* core, int index, int base)
{
  g_return_val_if_fail (MATH_IS_CORE (core), NULL);
  g_return_val_if_fail ((index = validate_index (index)) >= 0, NULL);
  MathNumber* number = _math_core_peek (core, index);
  g_return_val_if_fail (MATH_IS_NUMBER (number), NULL);

  switch (number->priv->kind)
  {
  case MATH_NUMBER_KIND_INTEGER:
    return mpz_get_str (NULL, base, number->priv->integer);
  case MATH_NUMBER_KIND_RATIONAL:
    return mpq_get_str (NULL, base, number->priv->rational);
  case MATH_NUMBER_KIND_REAL:
    return mpf_get_str (NULL, NULL, base, 0, number->priv->real);
  }
}

gboolean
math_core_isnumber (MathCore* core, int index)
{
  g_return_val_if_fail (MATH_IS_CORE (core), FALSE);
  g_return_val_if_fail ((index = validate_index (index)) >= 0, FALSE);
return MATH_IS_NUMBER (_math_core_peek (core, index));
}

/*
 * ext API
 *
 */

void
math_core_pushnumber (MathCore* core, MathNumberKind kind)
{
  g_return_if_fail (MATH_IS_CORE (core));
  MathNumber* n = _math_number_new (kind);
  _math_core_push (core, n);
  math_object_unref (n);
}

MathNumber*
math_core_tonumber (MathCore* core, int index)
{
  g_return_val_if_fail (MATH_IS_CORE (core), NULL);
  g_return_val_if_fail ((index = validate_index (index)) >= 0, FALSE);
  MathNumber* number = _math_core_peek (core, index);
  g_return_val_if_fail (MATH_IS_NUMBER (number), NULL);
return number;
}
