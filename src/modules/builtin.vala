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
  public class Builtin : Hcl.Module
  {
    public const string moduleid = Config.GAPPNAME + ".builtin";

    public override GLib.Menu get_appereance () { return new GLib.Menu (); }
    public override Hcl.ModuleLayout get_layout () { return new Hcl.BuiltinLayout (); }
  }

  [ModuleInit]
  public Hcl.Module module_entry () throws GLib.Error
  {
    Module.check_version (Config.PACKAGE_VERSION);
    var module = new Builtin ();
    module.id = Hcl.Builtin.moduleid;
    module.name = "Built-in extensions";
    module.description = "Built-in expensions module";
  return module;
  }
}
