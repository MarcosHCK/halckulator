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
  public abstract class Module : GLib.Object
  {
    private const string invalid_id = "__invalid_id__";

  /*
   * Module properties
   *
   */

    public string id { get; set; }
    public string name { get; set; }
    public string description { get; set; }

  /*
   * Abstracts
   *
   */

    public abstract GLib.Menu get_appereance ();
    public abstract Hcl.ModuleLayout get_layout ();

  /*
   * Checks
   *
   */

    public bool is_consistent ()
    {
      return id != invalid_id;
    }

    public static bool check_version (string expected) throws GLib.Error
    {
      return
      Patch.Module.check_version (expected);
    }

  /*
   * Constructors
   *
   */

    construct
    {
      this.id = invalid_id;
      this.name = "";
      this.description = "";
    }
  }
}
