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
  public errordomain LoadError
  {
    FAILED,
    LOAD,
    UNDEFINED,
    MODULE,
    ALREADY,
  }

  public class Manager : GLib.Object
  {
    private HashTable<string, Module> modules;
    private GenericSet<unowned GLib.Module> loaded;
    private GenericSet<string> paths;

    /*
     * type API
     *
     */

    [CCode (has_target = false)]
    public delegate Hcl.Module? Entry () throws GLib.Error;

    [Compact]
    private class Module
    {
      public Hcl.Module module;
      public GLib.Module handle;
    }

    /*
     * signal API
     *
     */

    public signal void module_added (Hcl.Module module);
    public signal void module_removed (Hcl.Module module);

    /*
     * public API
     *
     */

    public GLib.Menu? get_menu (string id)
    {
      unowned Module block;
      if ((block = modules.lookup (id)) != null)
        return block.module.get_menu ();
    return null;
    }

    public Hcl.Layout? get_layout (string id)
    {
      unowned Module block;
      if ((block = modules.lookup (id)) != null)
        return block.module.get_layout ();
    return null;
    }

    public bool has_module (string id)
    {
      return modules.contains (id);
    }

    public void add_path (string path)
    {
      paths.add (path);
    }

    public bool load (string binary) throws GLib.Error
    {
      var handle = GLib.Module.open (binary, GLib.ModuleFlags.LAZY);
      if (handle == null)
      {
        var message = GLib.Module.error ();
        throw new LoadError.LOAD ("Can't load module: %s", message);
      }
      else
      if (!loaded.contains (handle))
      {
        var symbol = (void*) null;
        var signature = "hcl_module_entry";

        if (!handle.symbol (signature, out symbol))
        {
          var message = @"Undefined symbol '$(signature)'";
          throw new LoadError.UNDEFINED ((owned) message);
        }
        else
        {
          var entry = (Entry) symbol;
          var module = entry ();

          if ((module == null) || (! (module is Hcl.Module)) || (!module.is_consistent ()))
            throw new LoadError.MODULE ("Entry function doesn't return a valid object");

          var id = module.id;
          if (modules.contains (id))
            throw new LoadError.ALREADY ("Already loaded module with id '%s'", id);
          else
          {
            loaded.add (handle);
            module_added (module);

            var block = new Module ();
                block.module = (owned) module;
                block.handle = (owned) handle;
            modules.insert (id, (owned) block);
          }
        }
      }
    return true;
    }

    public bool load_path (string path, bool recurse) throws GLib.Error
    {
      var file = GLib.File.new_for_path (path);
      var attrs = "standard::name,standard::type,standard::content-type";
      var @enum = file.enumerate_children (attrs, 0);

      do
      {
        unowned var child = (GLib.File) null;
        unowned var info = (GLib.FileInfo) null;

        @enum.iterate (out info, out child);
        if (child == null)
          break;
        else
        {
          switch (info.get_file_type ())
          {
          case GLib.FileType.REGULAR:
            {
              var type = info.get_content_type ();
              if (GLib.ContentType.is_a (type, "application/x-sharedlib"))
                load (child.get_path ());
            }
            break;
          case GLib.FileType.DIRECTORY:
            if (recurse)
              load_path (child.get_path (), recurse);
            break;
          }
        }
      } while (true);
    return true;
    }

    public bool load_all () throws GLib.Error
    {
      var iter = paths.iterator ();
      unowned string path;

      while ((path = iter.next_value ()) != null)
        load_path (path, true);
    return true;
    }

    /*
     * Constructors
     *
     */

    public Manager ()
    {
      Object ();
      modules = new HashTable<string, Module> (GLib.str_hash, GLib.str_equal);
      loaded = new GenericSet<unowned GLib.Module> (GLib.direct_hash, GLib.direct_equal);
      paths = new GenericSet<string> (GLib.str_hash, GLib.str_equal);
    }
  }
}
