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
  namespace Patch
  {
  }

  [CCode (cheader_filename = "value.h")]
  public abstract class Value
  {
    [CCode (construct_function = "math_value_new", has_new_function = false)]
    private Value ();
    public unowned Value @ref ();
    public void @unref ();
  }

  [CCode (cheader_filename = "stack.h")]
  public sealed class Stack : GLib.Object
  {
    public int depth;
    public int top;
    public Stack ();
    public void push (Value value);
    public void pop ();
    public unowned Value peek (int idx);
    public void insert (Value value, int idx);
    public void remove (int idx);
  }

  [CCode (cheader_filename = "numberkind.h")]
  public enum NumberKind
  {
    INTEGER,
    RATIONAL,
    REAL,
  }

  [CCode (cheader_filename = "number.h")]
  public class Number : Math.Value
  {
    public NumberKind kind;
    public Number (NumberKind kind);
    public void set_uint (uint value);
    public uint get_uint ();
    public void set_num (Number value);
    public Number get_num ();
    public void set_den (Number value);
    public Number get_den ();
    public void set_double (double value);
    public double get_double ();
    public void set_string (string value, int @base);
    public string get_string (int @base);
  }
}
