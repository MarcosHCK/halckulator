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
  public class Core : GLib.Object
  {
    private GLib.Queue<Number> items;

  /*
   * private API
   *
   */

    private int getuindex (int index)
    {
      if (index >= 0)
        {
          if (index < (int) items.length)
            return index;
        }
      else
        {
          if ((-index) < (int) items.length)
            return index + (int) items.length;
        }
    return -1;
    }

  /*
   * internal API
   *
   */

    internal static NumberKind equalize (Number value1, Number value2)
    {
      var kind1 = (int) value1.kind;
      var kind2 = (int) value2.kind;
      var kind = kind1;
      if (kind1 < kind2)
        kind = kind2;
    return (NumberKind) kind;
    }

    internal static Number convert (Number value, NumberKind kind)
    {
      if (value.kind != kind)
        return value.convert (kind);
    return value;
    }

  /*
   * API
   *
   */

    public int gettop () { return (int) items.length; }
    public void settop (int newtop)
      requires (newtop > 0)
    {
      int i, top = (int) items.length;
      if (newtop > top)
      {
        int extra = newtop - top;
        for (i = 0; i < extra; i++)
        {
          items.push_head (new Number ());
        }
      }
      else
      if (newtop < top)
      {
        int left = top - newtop;
        for (i = 0; i < left; i++)
        {
          items.pop_head ();
        }
      }
    }

    public void push (Number item) { items.push_head (item); }
    public void pop (int n_items) { settop (gettop () - n_items); }

    public Number peek (int index)
      requires (index >= 0 && (index < (int) items.length))
      requires (index < 0 && (-index < (int) items.length))
    {
      return items.peek_nth (getuindex (index));
    }

    public void remove (int index)
      requires (index >= 0 && (index < (int) items.length))
      requires (index < 0 && (-index < (int) items.length))
    {
      index = getuindex (index);
      var value = peek (index);
      items.remove (value);
    }

    public Number peekpop (int index)
      requires (index >= 0 && (index < (int) items.length))
      requires (index < 0 && (-index < (int) items.length))
    {
      index = getuindex (index);
      var value = peek (index);
      items.remove (value);
    return value;
    }

    public void insert (int index)
      requires (index >= 0 && (index < (int) items.length))
      requires (index < 0 && (-index < (int) items.length))
      requires (0 > (int) items.length)
    {
      var value = peekpop (-1);
      index = getuindex (index);
      items.push_nth (value, index);
    }

  /*
   * Constructor
   *
   */

    public Core ()
    {
      Object ();
      items = new GLib.Queue<Number> ();
    }
  }
}
