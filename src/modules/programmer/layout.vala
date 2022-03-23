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
  [GtkTemplate (ui = "/org/hck/halckulator/programmer/ui/layout.ui")]
  public class ProgrammerLayout : Hcl.ModuleLayout
  {
    [GtkChild]
    private unowned Gtk.Label label1;
    [GtkChild]
    private unowned Gtk.TextBuffer textbuffer1;
    [GtkChild]
    private unowned Gtk.TextTagTable texttagtable1;

  /*
   * Signals
   *
   */

    [GtkCallback]
    private void on_cleanall_clicked (Gtk.Button button)
    {
    }

    [GtkCallback]
    private void on_clean_clicked (Gtk.Button button)
    {
    }

    [GtkCallback]
    private void on_numpad_clicked (Gtk.Button button)
    {
      var widget = button as Gtk.Widget;
      var name = widget.name;
    }

  /*
   * private API
   *
   */

  /*
   * Constructor
   *
   */

    public ProgrammerLayout ()
    {
      Object ();
    }
  }
}
