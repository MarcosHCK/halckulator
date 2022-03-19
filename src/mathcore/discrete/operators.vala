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

namespace Math.Discrete
{
  public static void add (Core core)
    requires (core.gettop () >= 2)
  {
    var value1 = core.peek (-1); core.pop (1);
    var value2 = core.peek (-1); core.pop (1);
    var kind = Core.equalize (value1, value2);
    value1 = Core.convert (value1, kind);
    value2 = Core.convert (value2, kind);
    var result = Number.add (value1, value2);
    core.push (result);
  }

  public static void sub (Core core)
    requires (core.gettop () >= 2)
  {
    var value1 = core.peek (-1); core.pop (1);
    var value2 = core.peek (-1); core.pop (1);
    var kind = Core.equalize (value1, value2);
    value1 = Core.convert (value1, kind);
    value2 = Core.convert (value2, kind);
    var result = Number.sub (value1, value2);
    core.push (result);
  }

  public static void mul (Core core)
    requires (core.gettop () >= 2)
  {
    var value1 = core.peek (-1); core.pop (1);
    var value2 = core.peek (-1); core.pop (1);
    var kind = Core.equalize (value1, value2);
    value1 = Core.convert (value1, kind);
    value2 = Core.convert (value2, kind);
    var result = Number.mul (value1, value2);
    core.push (result);
  }
}
