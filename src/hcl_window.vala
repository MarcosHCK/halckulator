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
  [GtkTemplate (ui = "/org/hck/halckulator/ui/window.ui")]
  public class Window : Gtk.ApplicationWindow
  {
    private Hcl.ModuleLayout contents;
    private GLib.Settings gsettings;

  /*
   * Properties
   *
   */

    public string layout {
      get {
        var action = this.lookup_action ("Switch");
        var state = action.get_state ();
        return state.get_string ();
      }
    }

  /*
   * Signals
   *
   */

    public signal void changed_layout ()
    {
      var app = (application as Hcl.Application);
      var manager = app.manager;

      if (contents != null)
        this.remove (contents);
      contents = manager.get_layout (layout);
      contents.show ();
      this.add (contents);
    }

  /*
   * private API
   *
   */

    private void on_change_state (GLib.SimpleAction action, GLib.Variant? state)
    {
      action.set_state (state);
      gsettings.set_value ("selected-layout", state);
      changed_layout ();
    }

  /*
   * Constructor
   *
   */

    public Window (Hcl.Application application)
    {
      Object (show_menubar : false);
      GLib.Action action;

      gsettings = application.gsettings;
      var selected = gsettings.get_string ("selected-layout");
      var state = new GLib.Variant ("s", selected);

      action = new GLib.SimpleAction.stateful ("Switch", (GLib.VariantType) "s", state);
      ((GLib.SimpleAction) action).change_state.connect (on_change_state);
      ((GLib.ActionMap) this).add_action (action);
      action = new GLib.SimpleAction ("Undo", (GLib.VariantType) null);
      ((GLib.ActionMap) this).add_action (action);
      action = new GLib.SimpleAction ("Redo", (GLib.VariantType) null);
      ((GLib.ActionMap) this).add_action (action);
      action = new GLib.SimpleAction ("Cut", (GLib.VariantType) null);
      ((GLib.ActionMap) this).add_action (action);
      action = new GLib.SimpleAction ("Copy", (GLib.VariantType) null);
      ((GLib.ActionMap) this).add_action (action);
      action = new GLib.SimpleAction ("Paste", (GLib.VariantType) null);
      ((GLib.ActionMap) this).add_action (action);
      this.application = application;
      this.changed_layout ();
    }
  }
}
