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
#include <hcl_patch.h>

/*
 * hcl_module_manager.vala
 *
 */

/*
 * hcl_module.vala
 *
 */

G_DEFINE_QUARK
(hcl-module-error-quark,
 hcl_module_error);

enum
{
  BIT_MAYOR,
  BIT_MINOR,
  BIT_MICRO,
  BIT_BUILD,
};

static
guint cur[4] = {0};

#define PRIiBITS "%i.%i.%i.%i"
#define EXPAND_BITS(b) b[0],b[1],b[2],b[3]

G_GNUC_INTERNAL
gboolean
_hcl_patch_module_check_version (const gchar* expected, GError** error)
{
  g_return_val_if_fail (expected != NULL, FALSE);
  g_return_val_if_fail (error == NULL || *error == NULL, FALSE);
  guint bits[4] = {0}, n_bit = 0, i;
  const gchar* bit = expected;

  /*
   * Load version bits
   *
   */

  if (G_UNLIKELY
    (cur[BIT_MAYOR] == 0
  || cur[BIT_MINOR] == 0
  || cur[BIT_MICRO] == 0
  || cur[BIT_BUILD] == 0))
    {
      cur[BIT_MAYOR] = (gint) g_strtod (PACKAGE_VERSION_MAYOR, NULL);
      cur[BIT_MINOR] = (gint) g_strtod (PACKAGE_VERSION_MINOR, NULL);
      cur[BIT_MICRO] = (gint) g_strtod (PACKAGE_VERSION_MICRO, NULL);
      cur[BIT_BUILD] = (gint) g_strtod (PACKAGE_VERSION_BUILD, NULL);
    }

  do
  {
    g_return_val_if_fail (n_bit < 4, FALSE);
    bits[n_bit++] = (gint) g_strtod (bit, NULL);
    bit = g_strstr_len (bit, -1, ".");
  } while (bit && ++bit);

  /*
   * Check if current binary is
   * older than module
   *
   */

  for (i = 0; i < G_N_ELEMENTS (bits); i++)
    {
      if (G_UNLIKELY (bits[i] > cur[i]))
        {
          g_set_error
          (error,
           HCL_MODULE_ERROR,
           HCL_MODULE_ERROR_INCOMPATIBLE_VERSION,
           "Halckulator expected version '" PRIiBITS "' is greater than this build '" PRIiBITS "'\r\n",
           EXPAND_BITS (bits), EXPAND_BITS (cur));
          return FALSE;
        }
    }

  /*
 * Mayor build are expected to
 * be ABI-incompatible
 *
 */

  if G_UNLIKELY(bits[BIT_MAYOR] != cur[BIT_MAYOR])
    {
      g_set_error
      (error,
       HCL_MODULE_ERROR,
       HCL_MODULE_ERROR_INCOMPATIBLE_VERSION,
       "Halckulator expected version '" PRIiBITS "' doesn't match this build '" PRIiBITS "'\r\n",
       EXPAND_BITS(bits), EXPAND_BITS(cur));
      return FALSE;
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

  for(i = 0;i < G_N_ELEMENTS(bits);i++)
    {
      if G_UNLIKELY(bits[i] > cur[i])
        {
          g_set_error
          (error,
           HCL_MODULE_ERROR,
           HCL_MODULE_ERROR_VERSION_MISMATCH,
           "Halckulator expected version '" PRIiBITS "' doesn't match this build '" PRIiBITS "'\r\n",
           EXPAND_BITS(bits), EXPAND_BITS(cur));
          return FALSE;
        }
    }
return TRUE;
}
