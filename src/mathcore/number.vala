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
  public enum NumberKind
  {
    INTEGER,
    RATIONAL,
    REAL,
  }

  public class Number : GLib.Object
  {
    private MpxValue mpx;

  /*
   * Properties
   *
   */

    public NumberKind kind {
      get { return (NumberKind) mpx.type; }
      construct
        {
          mpx.clear ();
          mpx.type = (int) value;
          mpx.init ();
        }
    }

    public Number numerator {
      owned get {
        var num =
        new Number.from_uint (0);
        mpx.get_numerator (ref num.mpx);
      return num;
      }
      set {
        mpx.set_numerator (ref value.mpx);
      }
    }

    public Number denominator {
      owned get {
        var den =
        new Number.from_uint (0);
        mpx.get_denominator (ref den.mpx);
      return den;
      }
      set {
        mpx.set_denominator (ref value.mpx);
      }
    }

    public uint @uint {
      get { return mpx.get_uint (); }
      set { mpx.set_uint (value); }
    }

    public double @double {
      get { return mpx.get_double (); }
      set { mpx.set_double (value); }
    }

    public string @string {
      owned get { return mpx.get_string (); }
      set { mpx.set_string (value); }
    }

  /*
   * private API
   *
   */

    private bool check_kind (NumberKind kind) { return mpx.check_type (kind); }

  /*
   * API
   *
   */

    public Number clone ()
    {
      var result = new Number.with_kind (kind);
      mpx.clone (out result.mpx);
    return result;
    }

    public Number convert (NumberKind newkind)
      requires (newkind >= kind)
    {
      Number res;
      switch (newkind)
      {
      case NumberKind.INTEGER:
        return clone ();
      case NumberKind.RATIONAL:
        switch (kind)
        {
        case NumberKind.INTEGER:
          res = new Number.with_kind (newkind);
          mpx.z2q (ref res.mpx);
          return res;
        case NumberKind.RATIONAL:
          return clone ();
        case NumberKind.REAL:
          assert_not_reached ();
        }
        break;
      case NumberKind.REAL:
        switch (kind)
        {
        case NumberKind.INTEGER:
          res = new Number.with_kind (newkind);
          mpx.z2f (ref res.mpx);
          return res;
        case NumberKind.RATIONAL:
          res = new Number.with_kind (newkind);
          mpx.q2f (ref res.mpx);
          return res;
        case NumberKind.REAL:
          return clone ();
        }
        break;
      }
    
      assert_not_reached ();
    }

    public static Number add (Number value1, Number value2)
      requires (value1.check_kind (value2.kind))
    {
      var result = new Number.with_kind (value1.kind);
      MpxValue.add (ref value1.mpx, ref value2.mpx, ref result.mpx);
    return result;
    }

    public static Number sub (Number value1, Number value2)
      requires (value1.check_kind (value2.kind))
    {
      var result = new Number.with_kind (value1.kind);
      MpxValue.sub (ref value1.mpx, ref value2.mpx, ref result.mpx);
    return result;
    }

    public static Number mul (Number value1, Number value2)
      requires (value1.check_kind (value2.kind))
    {
      var result = new Number.with_kind (value1.kind);
      MpxValue.mul (ref value1.mpx, ref value2.mpx, ref result.mpx);
    return result;
    }

    public static Number div (Number value1, Number value2)
      requires (value1.check_kind (value2.kind))
    {
      var result = new Number.with_kind (value1.kind);
      MpxValue.div (ref value1.mpx, ref value2.mpx, ref result.mpx);
    return result;
    }

  /*
   * Constructor
   *
   */

    public Number () { Object (kind : NumberKind.INTEGER, @uint : 0); }
    public Number.with_kind (NumberKind kind) { Object (kind : kind); }
    public Number.from_uint (uint initial) { Object (kind : NumberKind.INTEGER, @uint : initial); }
    public Number.from_double (double initial) { Object (kind : NumberKind.INTEGER, @double : initial); }
    public Number.from_string (string initial) { Object (kind : NumberKind.INTEGER, @string : initial); }

    construct { mpx.type = (int) NumberKind.INTEGER; mpx.init (); }
    ~Number () { mpx.clear (); mpx.type = (int) NumberKind.INTEGER; }
  }
}
