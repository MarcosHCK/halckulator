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
  errordomain ModuleManagerError
  {
    FAILED,
    MISSING,
    UNDEFINED_INIT,
    INCONSISTENT,
    ALREADY,
  }

  public class ModuleManager : GLib.Object, GLib.Initable
  {
    private GLib.HashTable<string, Hcl.Module> registry;
    private GLib.HashTable<weak GLib.Module, bool> loaded;
    private GenericArray<ModuleEntry> modules;
    private GenericArray<GLib.File> paths;

    private class ModuleEntry
    {
      public Hcl.Module module;
      public GLib.Module handle;
    }

    [CCode (has_target = false, cname = "HclModuleEntryPoint")]
    public delegate Hcl.Module? EntryPoint () throws GLib.Error;

    public GLib.Menu menu { get; private set; }

  /*
   * GLib.Initable
   *
   */

    public bool init (GLib.Cancellable? cancellable = null) throws GLib.Error
    {
      try {
        load_single (null);
      } catch (ModuleManagerError error)
      {
        if (error.code != ModuleManagerError.UNDEFINED_INIT)
          throw error;
      }
    return true;
    }

  /*
   * private API
   *
   */

    private void appendto_menu (ModuleEntry entry)
    {
      var module = entry.module;
      var item = new GLib.MenuItem (module.name, null);

      item.set_action_and_target ("win.Switch", "s", module.id);
      menu.append_item (item);
    }

    private bool load_single (string? filename) throws GLib.Error
    {
      GLib.Module handle = null;
      Hcl.Module module = null;
      EntryPoint initf = null;
      void* symbol = null;
      bool success = true;

      handle =
      GLib.Module.open (filename, GLib.ModuleFlags.LAZY);
      if (unlikely (handle == null))
        {
          var file = GLib.File.new_for_path (filename);
          var info = file.query_info ("standard::content-type", 0);
          var type = info.get_content_type ();
          if (GLib.ContentType.is_a (type, "application/x-sharedlib"))
            {
              var error = GLib.Module.@error ();
              throw new ModuleManagerError.MISSING ("Can't open module '%s': %s", filename, error);
            }
          else
            {
              return false;
            }
        }
      else
        {
          success =
          loaded.lookup_extended (handle, null, null);
          if (success == true)
            {
              warning ("Module '%s' already loaded", handle.name ());
              return true;
            }
        }

      success =
      handle.symbol (Patch.Entry.SIGNATURE, out symbol);
      if (unlikely (success == false || symbol == null))
        {
          throw new ModuleManagerError.UNDEFINED_INIT ("Missing symbol '%s'", Patch.Entry.SIGNATURE);
        }

      initf = (EntryPoint) symbol;
      module = initf ();

      if (unlikely (module == null))
        {
          throw new ModuleManagerError.FAILED ("Unknown error at module initialization");
        }
      if (unlikely (module.is_consistent () == false))
        {
          throw new ModuleManagerError.INCONSISTENT ("Inconsistent module configuration");
        }

      success =
      registry.lookup_extended (module.id, null, null);
      if (unlikely (success == true))
        {
          throw new ModuleManagerError.ALREADY ("Module with id '%s' already loaded", module.id);
        }

      loaded.insert (handle, true);

      var entry = new ModuleEntry ();
      entry.handle = Patch.Steal<GLib.Module>.@get (ref handle);
      entry.module = module;

      registry.insert (module.id, module);
      appendto_menu (entry);
      modules.add (entry);
    return success;
    }

    private bool load_folder (GLib.File folder, GLib.Cancellable? cancellable = null) throws GLib.Error
    {
      GLib.FileEnumerator enumer;
      GLib.FileInfo info;
      GLib.FileType type;
      GLib.File child;

      const string attrs = 
#if DEVELOPER == 1
      "standard::is-symlink," +
#endif // DEVELOPER
      "standard::type";

      enumer =
      folder.enumerate_children (attrs, 0, cancellable);
      for (;;)
        {
          enumer.iterate (out info, out child, cancellable);
          if (child == null)
            break;

          type = info.get_file_type ();
#if DEVELOPER == 1
          var basename = child.get_basename ();
          if (basename != null && basename[0] != '.')
#endif // DEVELOPER
          switch (type)
            {
              case GLib.FileType.REGULAR:
                load_single (child.peek_path ());
                break;
              case GLib.FileType.DIRECTORY:
                load_folder (child, cancellable);
                break;
              default: break;
            }
        }
    return true;
    }

  /*
   * public API
   *
   */

    public void add_path (GLib.File path)
    {
      paths.add (path);
    }

    public bool load (GLib.File file) throws GLib.Error
    {
      var filename = file.peek_path ();
    return load_single (filename);
    }

    public bool load_all () throws GLib.Error
    {
      GLib.Cancellable cancellable = null;
      foreach (var path in paths)
        {
          load_folder (path, cancellable);
        }
    return true;
    }

    public GLib.Menu get_appereance (string id)
    {
      var module = registry.lookup (id) as Module;
      if (unlikely (module == null))
        {
          critical ("Unknown module %s", id);
          assert_not_reached ();
        }
      else
        {
          return module.get_appereance ();
        }
    }

    public Hcl.ModuleLayout get_layout (string id)
    {
      var module = registry.lookup (id) as Module;
      if (unlikely (module == null))
        {
          critical ("Unknown module %s", id);
          assert_not_reached ();
        }
      else
        {
          return module.get_layout ();
        }
    }

  /*
   * Constructor
   *
   */

    public ModuleManager () throws GLib.Error
    {
      Object ();
      this.registry = new GLib.HashTable<string, Hcl.Module> (GLib.str_hash, GLib.str_equal);
      this.loaded = new GLib.HashTable<weak GLib.Module, bool> (GLib.direct_hash, GLib.direct_equal);
      this.modules = new GenericArray<ModuleEntry> ();
      this.paths = new GenericArray<GLib.File> ();
      this.menu = new GLib.Menu ();
      this.init (null);
    }
  }
}
