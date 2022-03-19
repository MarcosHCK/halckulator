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
  public errordomain BasicoreError
  {
    FAILED,
    UNKNOWN_FUNCTION,
  }

  public class Basicore : GLib.Object
  {
    private Math.Core core;
    private GLib.StringBuilder number1;
    private GLib.StringBuilder number2;
    private GLib.StringBuilder screen;
    private string? operation = null;
    private bool equals = false;

  /*
   * Properties
   *
   */

    public unowned string display
      {
        get
        {
          if (operation == null)
            return number1.str;
          else
            {
              screen.truncate (0);
              screen.append (number1.str);
              screen.append_c (' ');
              screen.append (operation);
              screen.append_c ('\r');
              screen.append_c ('\n');
              screen.append (number2.str);
              return screen.str;
            }
        }
      }

  /*
   * API
   *
   */

    public string calculate (string number1, string number2, string function) throws GLib.Error
    {
      print ("calculate '%s %s %s'\r\n", number1, function, number2);

      core.pushnumber_as_string (number1, 10);
      core.pushnumber_as_string (number2, 10);
      core.pop (2);

      switch (function)
      {
      /*case "/": result = Math.Number.div (number1_, number2_); break;
      case "*": result = Math.Number.mul (number1_, number2_); break;
      case "-": result = Math.Number.sub (number1_, number2_); break;
      case "+": result = Math.Number.add (number1_, number2_); break;*/
      default:
        throw new BasicoreError.UNKNOWN_FUNCTION ("Unknown function '%s'", function);
      }
    return "0";
    }

    private int decimalat (GLib.StringBuilder number)
    {
      unowned var data = number.str;
      var i = number.len;

      for (i = 0; i < number.len; i++)
      if (data[i] == '.')
        return (int) i;
    return -1;
    }

    public void touch (string value) throws GLib.Error
    {
      string? result = null;
      var equals = false;
      char c = value[0];

      switch (c)
      {
        case '0':
        case '1': case '2': case '3':
        case '4': case '5': case '6':
        case '7': case '8': case '9':
          {
            if (this.equals)
              touch ("C");
            if (this.operation == null)
              number1.append_c ((char) c);
            else
              number2.append_c ((char) c);
          }
          break;
        case '.':
          unowned GLib.StringBuilder? number = null;
          if (this.operation == null)
            number = number1;
          else
            number = number2;
          if (decimalat (number) == -1)
            number.append_c ((char) c);
          break;
        case '/': case '*':
        case '-': case '+':
          {
            if (number1.len > 0)
              this.operation = value;
          }
          break;
        case '^': case '&':
          {
            unowned GLib.StringBuilder? number = null;
            if (this.operation == null)
              number = number1;
            else
              number = number2;
            if (number.len > 0) try
              {
                result =
                calculate (number.str, "2", (c == '^') ? "pow" : "root");
                if (this.operation == null)
                  number1.assign (result);
                else
                  number2.assign (result);
              }
            catch (GLib.Error e)
              {
                touch ("C");
                throw e;
              }
          }
          break;
        case '!':
          {
            unowned GLib.StringBuilder? number = null;
            if (this.operation == null)
              number = number1;
            else
              number = number2;
            if (number.len > 0) try
              {
                result =
                calculate ("1", number.str, "/");
                if (this.operation == null)
                  number1.assign (result);
                else
                  number2.assign (result);
              }
            catch (GLib.Error e)
              {
                touch ("C");
                throw e;
              }
          }
          break;
        case '=':
          {
            if (number2.len > 0 && this.operation != null) try
              {
                result =
                calculate (number1.str, number2.str, operation);

                touch ("C");
                number1.assign (result);
                equals = true;
              }
            catch (GLib.Error e)
              {
                touch ("C");
                throw e;
              }
          }
          break;
        case '<':
          if (this.equals)
            touch ("C");
          else
            {
              if (operation == null)
                number1.truncate (number1.len - 1);
              else
                number2.truncate (number2.len - 1);
            }
          break;
        case 'C':
          if (value == "CE")
          {
            if (operation == null)
              number1.truncate (0);
            else
              number2.truncate (0);
          } else
          if (value == "C")
          {
            number1.truncate (0);
            number2.truncate (0);
            operation = null;
          }
          break;
      }

      this.equals = equals;
    }

  /*
   * Constructor
   *
   */

    public Basicore ()
    {
      Object ();
      core = new Math.Core ();
      number1 = new GLib.StringBuilder.sized (64);
      number2 = new GLib.StringBuilder.sized (64);
      screen = new GLib.StringBuilder.sized (64);
    }
  }
}
