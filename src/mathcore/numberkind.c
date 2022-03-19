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
#include <numberkind.h>

GType
math_number_kind_get_type (void)
{
  static
  gsize __type__ = 0;
  if (g_once_init_enter (&__type__))
    {
      static const
      GEnumValue __values__[] =
      {
        {MATH_NUMBER_KIND_INTEGER, "MATH_NUMBER_KIND_INTEGER", "integer"},
        {MATH_NUMBER_KIND_RATIONAL, "MATH_NUMBER_KIND_RATIONAL", "rational"},
        {MATH_NUMBER_KIND_REAL, "MATH_NUMBER_KIND_REAL", "real"},
      };

      GType g_type;
      g_type = g_enum_register_static ("MathNumberKind", __values__);
      g_once_init_leave (&__type__, g_type);
    }
return (GType) __type__;
}
