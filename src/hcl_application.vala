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
  errordomain ApplicationError
  {
    FAILED,
    MISSING_SETTINGS,
  }

  enum MenuPtrID
  {
    APPEREANCE,
    LAYOUT,
  }

  public class Application : Gtk.Application, GLib.Initable
  {
    public Hcl.ModuleManager manager { get; private set; }
    public GLib.Settings gsettings { get; private set; }
    private Hcl.Settings settings;
    private GLib.Menu menuptr;

  /*
   * Signals
   *
   */

    private signal void turnoff ();

  /*
   * GInitable
   *
   */

    public bool init (GLib.Cancellable? cancellable = null) throws GLib.Error
    {
      Gdk.Pixbuf icon;
      GLib.File path;
      string name;

    /*
     * Module manager
     *
     */

      manager = new Hcl.ModuleManager ();
#if DEVELOPER == 1
      path = GLib.File.new_for_path (Config.ABSTOPBUILDDIR + "/src/modules");
#else // !DEVELOPER
      path = GLib.File.new_for_path (Config.MODULESDIR);
#endif // DEVELOPER
      manager.add_path (path);
      manager.load_all ();

    /*
     * Settings
     *
     */

      settings = new Hcl.Settings ();
      gsettings = settings.get_settings (Config.GAPPNAME);

      if (unlikely (gsettings == null))
        {
          throw new ApplicationError.MISSING_SETTINGS ("Missing settings schema '%s'", Config.GAPPNAME);
        }

    /*
     * Icon
     *
     */

      name = Config.GRESNAME + "/res/org.hck.halckulator.svg";
      icon = new Gdk.Pixbuf.from_resource (name);
      Gtk.Window.set_default_icon (icon);
    return true;
    }

  /*
   * private API
   *
   */

    private void on_changed_layout (Hcl.Window window)
    {
      if (!window.is_active) return;
      var state = window.layout;
      var menu = manager.get_appereance (state);

      menuptr.remove (0);
      menuptr.insert_submenu (0, "Appereance", menu);
    }

    private void on_is_active_notify (GLib.Object sender, GLib.ParamSpec pspec)
    {
      var window = (!) (sender as Hcl.Window);
      on_changed_layout (window);
    }

    private void on_menu_notify (GLib.Object sender, GLib.ParamSpec pspec)
    {
      var manager = (!) (sender as Hcl.ModuleManager);
      var menu = manager.menu;

      menuptr.remove (1);
      menuptr.insert_submenu (1, "Layout", menu);
    }

  /*
   * abstract API
   *
   */

    public override void window_added (Gtk.Window window)
    {
      base.window_added (window);
      window.notify["is-active"].connect (on_is_active_notify);
    }

    public override void window_removed (Gtk.Window window)
    {
      base.window_removed (window);
      window.notify["is-active"].disconnect (on_is_active_notify);
    }

    public override void startup ()
    {
      base.startup ();

    /*
     * Create menu
     *
     */

      var name = Config.GRESNAME + "/ui/menu.ui";
      var builder = new Gtk.Builder.from_resource (name);
      var menu = builder.get_object ("root") as GLib.Menu;
      var section = builder.get_object ("module") as GLib.Menu;

      menuptr = section;
      section.append ("label1", null);
      section.append ("label2", null);
      manager.notify["menu"].connect (on_menu_notify);
      manager.notify_property ("menu");

    /*
     * Set menu
     *
     */

      this.set_app_menu (menu);
      this.set_menubar (menu);
    }

    public override void activate ()
    {
      base.activate ();
      var window = new Hcl.Window (this);
      turnoff.connect (window.close);
      window.present ();
    }

  /*
   * Constructors
   *
   */

    public Application (string application_id, GLib.ApplicationFlags flags)
    {
      Object (application_id : application_id, flags : flags);
      var action = new GLib.SimpleAction ("Quit", (GLib.VariantType) null);
      ((GLib.SimpleAction) action).activate.connect (() => this.turnoff ());
      ((GLib.ActionMap) this).add_action (action);
    }
  }
}
