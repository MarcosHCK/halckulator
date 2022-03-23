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
  [CCode (cheader_filename = "libhclmodule.h")]
  public abstract class Module : GLib.Object
  {
    [CCode (has_construct_function = false)]
    protected Module ();
    public string id { get; set; }
    public string name { get; set; }
    public string description { get; set; }
    public abstract GLib.Menu get_appereance ();
    public abstract Hcl.ModuleLayout get_layout ();
    public bool is_consistent ();
    public static bool check_version (string expected) throws GLib.Error;
  }

  [CCode (cheader_filename = "libhclmodule.h")]
  public errordomain ModuleError
  {
    FAILED,
    INCOMPATIBLE_VERSION,
    VERSION_MISMATCH;
    public static GLib.Quark quark ();
  }

  [CCode (cheader_filename = "libhclmodule.h")]
  public abstract class ModuleLayout : Gtk.Grid
  {
    [CCode (has_construct_function = false)]
    protected ModuleLayout ();
    public abstract signal void undo ();
    public abstract signal void redo ();
    public abstract signal void cut ();
    public abstract signal void copy ();
    public abstract signal void paste ();
  }

  [CCode (cheader_filename = "libhclmodule.h", has_target = false)]
  public delegate Hcl.Module? ModuleEntryPoint () throws GLib.Error;

  [CCode (cheader_filename = "libhclmodule.h")]
  public sealed class ModuleManager : GLib.Object, GLib.Initable
  {
    public ModuleManager () throws GLib.Error;
    public GLib.Menu menu { get; private set; }
    public void add_path (GLib.File path);
    public bool load (GLib.File file) throws GLib.Error;
    public bool load_all () throws GLib.Error;
    public GLib.Menu get_appereance (string id);
    public Hcl.ModuleLayout get_layout (string id);
  }

  [CCode (cheader_filename = "libhclmodule.h")]
  public sealed class Settings : GLib.Object, GLib.Initable
  {
    public Settings () throws GLib.Error;
    public Settings get_default ();
    public GLib.Settings get_settings (string schemaid);
  }
}
