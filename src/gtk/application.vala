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
  enum MenuPtrID
  {
    LAYOUT,
    OPTIONS,
  }

  public class Application : Gtk.Application
  {
    private Hcl.Manager manager;
    private GLib.Menu menuptr;
    private GLib.Settings settings;

    /*
     * private API
     *
     */

    private void on_is_active_notify (GLib.Object sender, GLib.ParamSpec pspec)
    {
      var window = (Hcl.Window) sender;
      var id = window.layout_id;
      var menu = manager.get_menu (id);
      update_options (menu);
    }

    private GenericSet<Hcl.Module> modules = new GenericSet<Hcl.Module> (GLib.direct_hash, GLib.direct_equal);

    private void on_module_changed ()
    {
      var menu = new GLib.Menu ();
      var iter = modules.iterator ();
      var module = (Hcl.Module?) null;

      while ((module = iter.next_value ()) != null)
      {
        var name = module.name ?? module.id;
        var item = new GLib.MenuItem (name, null);

        item.set_action_and_target ("win.Switch", "s", module.id);
        menu.append_item (item);
      }

      if (menuptr != null)
      {
        update_layouts (menu);
      }
    }

    private void on_module_added (Hcl.Module module)
    {
      modules.add (module);
      on_module_changed ();
    }

    private void on_module_removed (Hcl.Module module)
    {
      modules.remove (module);
      on_module_changed ();
    }

    private static void spawn (Hcl.Application self)
    {
      var window = new Hcl.Window ();
      var settings = self.settings;
      var manager = self.manager;

      var @default = settings.get_string ("layout");
      ((Gtk.Application) self).add_window (window);

      window.notify ["layout-id"].connect (() =>
        {
          var value = window.layout_id;
          if (manager.has_module (value))
          {
            var layout = manager.get_layout (value);
            var menu = manager.get_menu (value);

            settings.set_string ("layout", value);
            self.update_options (menu);
            window.layout = layout;
          }
          else
          {
            var msg = @"Unknown module id '$(value)'";
            var message = new Hcl.Message.warning (msg);
            ((Gtk.Dialog) message).run ();
            ((Gtk.Dialog) message).destroy ();
          }
        });

      window.layout_id = @default;
      window.present ();
    }

    private void update_layouts (GLib.Menu menu)
      requires (menu is GLib.Menu)
    {
      menuptr.remove (MenuPtrID.LAYOUT);
      menuptr.insert_submenu (MenuPtrID.LAYOUT, "Layouts", menu);
    }

    private void update_options (GLib.Menu menu)
      requires (menu is GLib.Menu)
    {
      menuptr.remove (MenuPtrID.OPTIONS);
      menuptr.insert_submenu (MenuPtrID.OPTIONS, "Options", menu);
    }

    /*
     * abstract API
     *
     */

    public override void activate ()
    {
      try
      {
#if DEVELOPER == 1
        var dir = Config.ABSTOPBUILDDIR + "/modules/";
#else // !DEVELOPER
        var dir = Config.MODULESDIR;
#endif // DEVELOPER
        manager.add_path (dir);
        manager.load_all ();
      } catch (GLib.Error e) {
        var message = new Hcl.Message.error_with_gerror (e);
        ((Gtk.Dialog) message).run ();
        ((Gtk.Dialog) message).destroy ();
        quit ();
        return;
      }

      spawn (this);
    }

    public override void startup ()
    {
      base.startup ();

      try
      {
        var name = Config.GRESNAME + "/res/org.hck.halckulator.svg";
        var icon = new Gdk.Pixbuf.from_resource (name);
        Gtk.Window.set_default_icon (icon);

#if DEVELOPER == 1
        var dir = Config.ABSTOPBUILDDIR + "/src/settings/";
#else // !DEVELOPER
        var dir = Config.SCHEMASDIR;
#endif // DEVELOPER
        var source = new GLib.SettingsSchemaSource.from_directory (dir, null, true);
        var schema = source.lookup (Config.GAPPNAME, false);
            settings = new GLib.Settings.full (schema, null, null);
            manager = new Hcl.Manager ();
      } catch (GLib.Error e) {
        critical (@"$(e.domain):$(e.code):$(e.message)");
        assert_not_reached ();
      }

      var name = Config.GRESNAME + "/ui/menu.ui";
      var builder = new Gtk.Builder.from_resource (name);
      var menu = builder.get_object ("root") as GLib.Menu;
      var section = builder.get_object ("module") as GLib.Menu;

      menuptr = section;
      section.append ("label1", null);
      section.append ("label2", null);
      on_module_changed ();

      manager.module_added.connect (on_module_added);
      manager.module_removed.connect (on_module_removed);

      set_app_menu (menu);
      set_menubar (menu);
    }

    public override void window_added (Gtk.Window window)
    {
      base.window_added (window);
      window.notify ["is-active"].connect (on_is_active_notify);
    }

    public override void window_removed (Gtk.Window window)
    {
      base.window_removed (window);
      window.notify ["is-active"].disconnect (on_is_active_notify);
    }

    /*
     * Constructors
     *
     */

    public Application (GLib.ApplicationFlags flags)
    {
      Object (application_id : Config.GAPPNAME, flags : flags);
    }
  }
}
