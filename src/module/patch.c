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
#include <patch.h>

#define PRIiBITS "%i.%i.%i.%i"
#define EXPAND_BITS(b) b[0],b[1],b[2],b[3]
#define FAIL(...) \
  G_STMT_START { \
    *failed = TRUE; \
    return g_strdup_printf (__VA_ARGS__); \
  } G_STMT_END

enum
{
  BIT_MAJOR,
  BIT_MINOR,
  BIT_MICRO,
  BIT_MAX,
};

gchar*
_hcl_patch_module_check_version (const gchar* expected, gboolean* failed)
{
  guint bits [BIT_MAX], n_bit = 0;
  const gchar* bit = expected;
  gboolean mismatch = FALSE;
  guint i;

  *failed = FALSE;

  /*
   * Load version bits
   *
   */

  static guint cur [] =
  {
    PACKAGE_VERSION_MAJOR,
    PACKAGE_VERSION_MINOR,
    PACKAGE_VERSION_MICRO,
  };

  G_STATIC_ASSERT (G_N_ELEMENTS (cur) == BIT_MAX);

  do
  {
    if (G_UNLIKELY (n_bit >= BIT_MAX))
      FAIL ("Malformed version string");

    bits [n_bit++] = (gint) g_strtod (bit, NULL);
    bit = g_strstr_len (bit, -1, ".");
  } while (bit && ++bit);

  /*
   * Major release are expected to
   * be ABI-incompatible
   *
   */

  if (bits [BIT_MAJOR] < cur[BIT_MAJOR])
    FAIL ("Halckulator version '" PRIiBITS "' is incompatible with this module expected version '" PRIiBITS "'",
      EXPAND_BITS (cur), EXPAND_BITS (bits));

  /*
   * Check if current binary is
   * older than module
   *
   */

  for (i = 0; i < BIT_MAX; i++)
    {
      if (bits [i] > cur [i])
        FAIL ("Halckulator version '" PRIiBITS "' is incompatible with this module expected version '" PRIiBITS "'",
          EXPAND_BITS (cur), EXPAND_BITS (bits));
      else
      if (bits [i] < cur [i])
        mismatch = TRUE;
    }

  /*
   * If version mismatches
   * but reaches this point
   * means module should work
   * correctly, although I don't
   * recommend it so emit a little
   * warning
   *
   */

  if (mismatch)
    return g_strdup_printf
    ("Halckulator expected version '" PRIiBITS "' differs from actual version '" PRIiBITS "'",
     EXPAND_BITS (bits), EXPAND_BITS (cur));
return NULL;
}
