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
  public sealed class Core : GLib.Object
  {
    private Math.Stack stack;
    public int item;

  /*
   * private API
   *
   */

    private int validate_index (int index)
    {
      if (index >= 0)
        {
          if (stack.top > index)
            return index;
        }
      else
        {
          return stack.top + index;
        }
    return -1;
    }

  /*
   * internal API
   *
   */

    internal void push (Value value)
    {
      stack.push (value);
    }

    internal unowned Value peek (int index)
      requires ((index = validate_index (index)) >= 0)
    {
      return stack.peek (index);
    }

  /*
   * API
   *
   */

    public int gettop ()
    { 
      return stack.top;
    }

    public void settop (int newtop)
      requires (newtop >= 0)
    {
      int i, top = stack.top;
      if (newtop > top)
      {
        int extra = newtop - top;
        for (i = 0; i < extra; i++)
        {
          stack.push (new Number (NumberKind.INTEGER));
        }
      }
      else
      if (newtop < top)
      {
        int left = top - newtop;
        for (i = 0; i < left; i++)
        {
          stack.pop ();
        }
      }
    }

    public void pop (int n_values)
      requires (n_values >= 0)
    {
      settop (stack.top - n_values);
    }

    public void remove (int index)
      requires ((index = validate_index (index)) >= 0)
    {
      stack.remove (index);
    }

    public void insert (int index)
      requires ((index = validate_index (index)) >= 0)
      requires (0 < stack.top)
    {
      var top = validate_index (-1);
      var value = peek (top);
      stack.pop ();
      stack.insert (value, index);
    }

  /*
   * API::push
   *
   */

    private NumberKind guesstype (string value, out string? converted)
    {
      NumberKind kind = NumberKind.INTEGER;
      unowned var val = value;
      string? next = null;
      ssize_t gotat = -1;
      size_t got = 0;

      converted = null;

      do
        {
          var c = val.get_char ();
          if (c == 0) break;

          switch (c)
          {
          case '.':
            next = ("%.*s%s").printf (got, value, value.offset (1 + (long) got));
            kind = NumberKind.RATIONAL;
            gotat = (ssize_t) got;
            break;
          default: ++got; break;
          }
        }
      while ((val = val.next_char ()) != null);
      switch (kind)
        {
          case NumberKind.INTEGER:
            return kind;
          case NumberKind.RATIONAL:
            var exp = next.length - gotat;
            converted = @"$next/1$(string.nfill (exp, '0'))";
            break;
          case NumberKind.REAL:
            break;
        }
    return kind;
    }

    public void pushnumber_as_string (string value, int @base)
      requires (@base > 0 || @base < 64)
      requires (value.validate ())
    {
      string? converted = null;
      var kind = guesstype (value, out converted);
      var number = new Number (kind);
      if (converted != null)
        number.set_string (converted, @base);
      else
        number.set_string (value, @base);
      push (number);
    }

    public string? tonumber_as_string (int index, int @base)
      requires ((index = validate_index (index)) >= 0)
      requires (@base > 0 || @base < 64)
    {
      var value = peek (index);
    return (value is Number) ? value.get_string (@base) : null;
    }

    public bool checknumber (int index)
      requires ((index = validate_index (index)) >= 0)
    {
      var value = peek (index);
    return (value is Number);
    }

  /*
   * Constructor
   *
   */

    public Core ()
    {
      Object ();
      stack = new Stack ();
    }
  }
}
