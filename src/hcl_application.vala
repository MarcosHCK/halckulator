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
  public class Application : Gtk.Application, GLib.Initable
  {
    public Hcl.ModuleManager manager { get; private set; }
    private GLib.Func<GLib.Menu> update_appereance = (() => { });
    private GLib.Func<GLib.Menu> update_layouts = (() => { });
    private GLib.Func<string> update_layout = (() => { });

  /*
   * Properties
   *
   */

    private GLib.Menu _appereance = null;
    private GLib.Menu appereance
    {
      get { return _appereance; }
      set { _appereance = value; update_appereance (value); }
    }

    private GLib.Menu _layouts = null;
    private GLib.Menu layouts
    {
      get { return _layouts; }
      set { _layouts = value; update_layouts (value); }
    }

    private string _layout = null;
    public string layout
    {
      get { return _layout; }
      set { _layout = value; update_layout (value); }
    }

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
     * Icon
     *
     */

      name = Config.GRESNAME + "/res/org.hck.halckulator.svg";
      icon = new Gdk.Pixbuf.from_resource (name);
      Gtk.Window.set_default_icon (icon);

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
    return true;
    }

  /*
   * private API
   *
   */

    private static void connect_updates (Hcl.Application self, GLib.Menu section)
    {
      var manager = self.manager;
      unowned var self_ = self;

      self.update_appereance = (menu) => { section.remove (0); section.insert_submenu (0, "Appereance", menu); };
      self.update_layouts = (menu) => { section.remove (1); section.insert_submenu (1, "Layouts", menu); };
      self.update_layout = (id) => { self_.appereance = manager.get_appereance (id); };
      manager.notify["menu"].connect (() => { self_.layouts = manager.menu; });

      section.insert (0, null, null);
      self.layouts = manager.menu;
      self.layout = "org.hck.halckulator.basic";
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
      Application.connect_updates (this, section);

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
      var window = new Hcl.Window ();
      turnoff.connect (window.close);
      window.set_application (this);
      window.present ();
      window.layout = layout;
    }

    public override void open (GLib.File[] files, string hint)
    {
      base.open (files, hint);
      var window = new Hcl.Window ();
      turnoff.connect (window.close);
      window.set_application (this);
      window.present ();
      window.layout = layout;
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
