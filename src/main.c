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
#include <resources/bundle.h>

void
pointer_ensure (gpointer pobject)
{
  if (G_UNLIKELY (pobject == NULL))
    g_error ("Erghh?");
}

GApplication*
hcl_application_new (GApplicationFlags flags);

int
main (int argc, char* argv[])
{
  GApplication* app = NULL;
  gboolean success = TRUE;
  GError* tmp_err = NULL;
  int status = 0;

  /*
   * Ensure things
   *
   */

  pointer_ensure (bundle_get_resource ());

  /*
   * Execute
   *
   */

  app = hcl_application_new (G_APPLICATION_FLAGS_NONE);
  status = g_application_run (app, argc, argv);

  /*
   * Cleanup
   *
   */

#if DEVELOPER == 1
  g_assert_finalize_object (app);
#else
  g_object_unref (app);
#endif // DEBUG
return status;
}
