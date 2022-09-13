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
    private GLib.SimpleAction _switch;

    public string layout_id
    {
      get
      {
        var state = _switch.get_state ();
        return state.get_string ();
      }

      set
      {
        var state = new GLib.Variant ("s", value);
            _switch.set_state (state);
      }
    }

    private Hcl.Layout? _layout;
    public Hcl.Layout? layout
    {
      get
      {
        return _layout;
      }

      set
      {
        if (_layout != layout)
        {
          if (_layout != null)
            remove (_layout);

          _layout = value;
                  add (_layout);
          _layout.show ();
        }
      }
    }

    /*
     * Constructors
     *
     */

    public Window ()
    {
      Object (show_menubar : false);
      var state = new GLib.Variant ("s", "none");
      var action = (GLib.SimpleAction) null;

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
      action = new GLib.SimpleAction.stateful ("Switch", (GLib.VariantType) "s", state);
      action.change_state.connect ((action, state) => { if (state != null) layout_id = state.get_string (); });
      ((GLib.ActionMap) this).add_action (action);
      _switch = action;
    }
  }
}
