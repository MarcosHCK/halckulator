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

namespace Hcl
{
  public class Manager : GLib.Object
  {
    /*
     * public API
     *
     */

    public GLib.Menu? get_menu (string id)
    {
      return null;
    }

    public Hcl.Layout? get_layout (string id)
    {
      return null;
    }

    public bool has_module (string id)
    {
      return false;
    }

    public void add_path (string path)
    {
    }

    public bool load_all () throws GLib.Error
    {
    return true;
    }

    /*
     * Constructors
     *
     */

    public Manager ()
    {
      Object ();
    }
  }
}
