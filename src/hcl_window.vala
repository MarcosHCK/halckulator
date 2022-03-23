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
    private weak GLib.WeakRef layout_notify_object;
    private ulong layout_notify_id;

  /*
   * Properties
   *
   */

    private string _layout;
    public string layout
    {
      get { return _layout; }
      set { _layout = value; on_switch_layout (value); }
    }

  /*
   * Signals
   *
   */

    [GtkCallback]
    private void on_is_active_notify ()
    {
      var app = application as Hcl.Application;
      if (is_active && app.layout != layout)
        {
          app.layout = layout;
        }
    }

    [GtkCallback]
    private void on_application_notify ()
    {
      var app = application as Hcl.Application;
      var prev = layout_notify_object.@get ();
      if (prev != null)
        {
          prev.disconnect (layout_notify_id);
          layout_notify_id = 0;
        }

      layout_notify_id =
      app.notify["layout"].connect (this.on_layout_notify);
      layout_notify_object.@set (app);
    }

    private void on_layout_notify ()
    {
      var app = application as Hcl.Application;
      layout = app.layout;
    }

    private void on_switch_layout (string id)
    {
      var app = application as Hcl.Application;
      var action = this.lookup_action ("Switch");
      var manager = app.manager;

      var state = new GLib.Variant ("s", id);
      ((GLib.SimpleAction) action).set_state (state);

      if (contents != null)
        this.remove (contents);
      contents = manager.get_layout (id);
      contents.show ();
      this.add (contents);
    }

  /*
   * Constructor
   *
   */

    public Window ()
    {
      Object (show_menubar : false);
      GLib.Action action;

      var state = new GLib.Variant ("s", "");
      action = new GLib.SimpleAction.stateful ("Switch", (GLib.VariantType) "s", state);
      ((GLib.SimpleAction) action).activate.connect ((idv) => { this.layout = idv.get_string (); });
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
    }
  }
}
