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
  public errordomain ModuleError
  {
    FAILED,
    MISMATCH,
    INCOMPATIBLE,
  }

  public abstract class Module
  {
    public const string __invalid__ = "__invalid__";
    public string? description { get; protected set; }
    public string? version { get; protected set; }
    public string? name { get; protected set; }
    public string id { get; protected set; }

    /*
     * abstract API
     *
     */

    public abstract GLib.Menu get_menu ();
    public abstract Layout get_layout ();

    /*
     * public API
     *
     */

    public static bool check_version (string expected) throws ModuleError
    {
      string message = null;
      bool failed = false;

      message = Hcl.Patch.Module.check_version (expected, out failed);

      if (message != null)
      {
        if (failed)
          throw new ModuleError.INCOMPATIBLE (message);
        else
          throw new ModuleError.MISMATCH (message);
      }
      else
      if (failed)
        throw new ModuleError.FAILED ("Failed!");
    return true;
    }

    /*
     * Constructors
     *
     */

    protected Module ()
    {
      this.id = __invalid__;
    }
  }
}
