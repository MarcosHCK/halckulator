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
  [GtkTemplate (ui = "/org/hck/halckulator/basic/ui/layout.ui")]
  public class BasicLayout : Gtk.Grid, Hcl.ModuleLayout
  {
    private Basicore core;
    [GtkChild]
    private unowned Gtk.Label label1;

  /*
   * Signals
   *
   */

    [GtkCallback]
    private void on_cleanall_clicked (Gtk.Button button)
    {
      try {
        core.touch ("C");
        label1.label = core.display;
      } catch (GLib.Error e)
      {
        warning (@"$(e.domain):$(e.code):$(e.message)");
      }
    }

    [GtkCallback]
    private void on_clean_clicked (Gtk.Button button)
    {
      try {
        core.touch ("CE");
        label1.label = core.display;
      } catch (GLib.Error e)
      {
        warning (@"$(e.domain):$(e.code):$(e.message)");
      }
    }

    [GtkCallback]
    private void on_numpad_clicked (Gtk.Button button)
    {
      var widget = button as Gtk.Widget;
      var name = widget.name;

      try {
        core.touch (name);
        label1.label = core.display;
      } catch (GLib.Error e)
      {
        warning (@"$(e.domain):$(e.code):$(e.message)");
      }
    }

  /*
   * Constructor
   *
   */

    public BasicLayout ()
    {
      Object ();
      core = new Basicore ();
    }
  }
}
