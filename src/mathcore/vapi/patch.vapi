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
  [CCode (cname = "MpxValue", cheader_filename = "number_patch.h")]
  public struct MpxValue
  {
    public int type;
    [CCode (cname = "__base")]
    public int @base;

    [CCode (cname = "mpx_value_init")]
    public void init ();
    [CCode (cname = "mpx_value_clear")]
    public void clear ();
    [CCode (cname = "mpx_value_clone")]
    public void clone (out MpxValue value);

    [CCode (cname = "mpx_value_check_type")]
    public bool check_type (int type);

    [CCode (cname = "mpx_value_z2q")]
    public void z2q (ref MpxValue result);
    [CCode (cname = "mpx_value_z2f")]
    public void z2f (ref MpxValue result);
    [CCode (cname = "mpx_value_q2f")]
    public void q2f (ref MpxValue result);

    [CCode (cname = "mpx_value_set_numerator")]
    public void set_numerator (ref MpxValue value);
    [CCode (cname = "mpx_value_get_numerator")]
    public void get_numerator (ref MpxValue result);
    [CCode (cname = "mpx_value_set_denominator")]
    public void set_denominator (ref MpxValue value);
    [CCode (cname = "mpx_value_get_denominator")]
    public void get_denominator (ref MpxValue result);

    [CCode (cname = "mpx_value_set_uint")]
    public void set_uint (uint value);
    [CCode (cname = "mpx_value_set_double")]
    public void set_double (double value);
    [CCode (cname = "mpx_value_set_string")]
    public void set_string (string value);
    [CCode (cname = "mpx_value_get_uint")]
    public uint get_uint ();
    [CCode (cname = "mpx_value_get_double")]
    public double get_double ();
    [CCode (cname = "mpx_value_get_string")]
    public string get_string ();

    [CCode (cname = "mpx_value_add")]
    public static void add (ref MpxValue value1, ref MpxValue value2, ref MpxValue result);
    [CCode (cname = "mpx_value_sub")]
    public static void sub (ref MpxValue value1, ref MpxValue value2, ref MpxValue result);
    [CCode (cname = "mpx_value_mul")]
    public static void mul (ref MpxValue value1, ref MpxValue value2, ref MpxValue result);
    [CCode (cname = "mpx_value_div")]
    public static void div (ref MpxValue value1, ref MpxValue value2, ref MpxValue result);
  }
}
