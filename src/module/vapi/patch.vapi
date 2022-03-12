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

[CCode (cheader_filename = "hcl_patch.h", lower_case_cprefix = "_hcl_patch_")]
namespace Hcl.Patch
{
  [CCode (cheader_filename = "hcl_module_entry.h")]
  public class Entry
  {
    [CCode (cname = "HCL_MODULE_ENTRY_SIGNATURE")]
    public const string SIGNATURE;
  }

  public class Module
  {
    internal static bool check_version (string expected) throws GLib.Error;
  }

  public class Steal<T>
  {
    [CCode (cname = "g_steal_pointer")]
    internal static T @get (out T pp);
  }

  public errordomain ModuleError
  {
    FAILED,
    INCOMPATIBLE_VERSION,
    VERSION_MISMATCH;
    public static GLib.Quark quark ();
  }
}
