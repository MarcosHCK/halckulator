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

namespace Math
{
  [CCode (cheader_filename = "libmathcore.h", ref_function = "math_object_ref", unref_function = "math_object_unref")]
  public class Object
  {
    public uint ref_count;
    [CCode (construct_function = "math_object_new", has_new_function = false)]
    public Object ();
    [ReturnsModifiedPointer ()]
    public void append (Object link);
    [ReturnsModifiedPointer ()]
    public void prepend (Object link);
    [ReturnsModifiedPointer ()]
    public void insert (Object link, uint position);
    [ReturnsModifiedPointer ()]
    public void remove (Object link);
    public unowned Object nth (uint position);
    public uint length ();
  }

  [CCode (cheader_filename = "libmathcore.h")]
  public class Core : GLib.Object
  {
    public Core ();
    public void settop (int newtop);
    public int gettop ();
    public void pop (int n_values);
    public void remove (int index);
    public void insert (int index);
    public bool isnone (int index);
    public void pushnil ();
    public bool isnil (int index);
    public bool isnoneornil (int index);
    public void pushnumber_uint (uint value);
    public uint tonumber_uint (int index);
    public void pushnumber_double (double value);
    public double tonumber_double (int index);
    public bool pushnumber_string (string value, int @base);
    public string tonumber_string (int index, int @base);
  }
}
