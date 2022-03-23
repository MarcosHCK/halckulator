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
#include <config.h>
#include <gmodule.h>
#include <module_entry.h>
#include <module_manager.h>

G_DEFINE_QUARK
(hcl-module-manager-error-quark,
 hcl_module_manager_error);

#define QUIET_BOOTUP (1)

#define HCL_MODULE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), HCL_TYPE_MODULE_MANAGER, HclModuleManagerClass))
#define HCL_IS_MODULE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), HCL_TYPE_MODULE_MANAGER))
#define HCL_MODULE_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), HCL_TYPE_MODULE_MANAGER, HclModuleManagerClass))
typedef struct _HclModuleManagerClass HclModuleManagerClass;
typedef struct _Module Module;

#define _g_module_close0(var) (var = (var != NULL) ? (g_module_close (var), NULL) : NULL)
#define _g_object_unref0(var) (var = (var != NULL) ? (g_object_unref (var), NULL) : NULL)

#define HCL_MODULE_ENTRY_NAME G_STRINGIFY (HCL_MODULE_ENTRY_SIGNATURE)

static void
g_initable_iface_init (GInitableIface* iface);
static void
module_free (gpointer pmodule);

struct _HclModuleManager
{
  GObject parent_instance;
  GHashTable* registry;
  GHashTable* loaded;
  GSList* paths;
  GMenu* menu;
};

struct _Module
{
  HclModule* module;
  GModule* handle;
};

struct _HclModuleManagerClass
{
  GObjectClass parent_class;
};

enum
{
  prop_0,
  prop_menu,
  prop_number,
};

static
GParamSpec* properties[prop_number] = {0};

G_DEFINE_FINAL_TYPE_WITH_CODE
(HclModuleManager,
 hcl_module_manager,
 G_TYPE_OBJECT,
 G_IMPLEMENT_INTERFACE
 (G_TYPE_INITABLE,
  g_initable_iface_init));

static gboolean
g_initable_iface_init_sync (GInitable* pself, GCancellable* cancellable, GError** error)
{
  HclModuleManager* self = HCL_MODULE_MANAGER (pself);
return TRUE;
}

static void
g_initable_iface_init (GInitableIface* iface)
{
  iface->init = g_initable_iface_init_sync;
}

static void
hcl_module_manager_class_get_property (GObject* pself, guint prop_n, GValue* value, GParamSpec* pspec)
{
  HclModuleManager* self = HCL_MODULE_MANAGER (pself);
  switch (prop_n)
  {
  case prop_menu:
    g_value_set_object (value, hcl_module_manager_get_menu (self));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (pself, prop_n, pspec);
    break;
  }
}

static void
hcl_module_manager_class_finalize (GObject* pself)
{
  HclModuleManager* self = HCL_MODULE_MANAGER (pself);
  g_hash_table_unref (self->registry);
  g_hash_table_unref (self->loaded);
G_OBJECT_CLASS (hcl_module_manager_parent_class)->finalize (pself);
}

static void
hcl_module_manager_class_dispose (GObject* pself)
{
  HclModuleManager* self = HCL_MODULE_MANAGER (pself);
  g_slist_free_full (self->paths, g_object_unref);
  g_hash_table_remove_all (self->registry);
  g_hash_table_remove_all (self->loaded);
  g_object_unref (self->menu);
G_OBJECT_CLASS (hcl_module_manager_parent_class)->dispose (pself);
}

static void
hcl_module_manager_class_init (HclModuleManagerClass* klass)
{
  GObjectClass* oclass = G_OBJECT_CLASS (klass);

  oclass->get_property = hcl_module_manager_class_get_property;
  oclass->finalize = hcl_module_manager_class_finalize;
  oclass->dispose = hcl_module_manager_class_dispose;

  properties[prop_menu] =
    g_param_spec_object
    ("menu",
     "Layout menu",
     "Layout menu",
     G_TYPE_MENU,
     G_PARAM_READABLE
     | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties
  (oclass,
   prop_number,
   properties);
}

static void
hcl_module_manager_init (HclModuleManager* self)
{
  self->menu = g_menu_new ();
  self->registry = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, module_free);
  self->loaded = g_hash_table_new_full (g_direct_hash, g_direct_equal, NULL, NULL);
  self->paths = NULL;
}

/*
 * private API
 *
 */

static void
module_free (gpointer pmodule)
{
  Module* module = pmodule;
  g_object_unref (module->module);
  g_module_close (module->handle);
  g_slice_free (Module, module);
}

static void
appendto_menu (HclModuleManager* self, HclModule* module)
{
  GMenuItem* item = NULL;
  const gchar* name = NULL;
  const gchar* id = NULL;

  name = hcl_module_get_name (module);
  id = hcl_module_get_id (module);
  item = g_menu_item_new (name, NULL);

  g_menu_item_set_action_and_target (item, "win.Switch", "s", id);
  g_menu_append_item (self->menu, item);
}

static gboolean
load_single (HclModuleManager* self, GFile* file, GCancellable* cancellable, GError** error)
{
  gboolean success = TRUE;
  GError *tmp_err = NULL;
  HclModuleEntry entry = NULL;
  const gchar* filename = NULL;
  const gchar* id = NULL;
  HclModule* module = NULL;
  GModule* handle = NULL;
  Module* reg = NULL;

  filename =
  g_file_peek_path (file);
  if (filename == NULL)
    {
      gchar* uri = g_file_get_uri (file);
      g_warning ("Unable to lookup file '%s'\r\n", uri);
      g_free (uri);
      return FALSE;
    }

  handle =
  g_module_open (filename, G_MODULE_BIND_LAZY);
  if (G_UNLIKELY (handle == NULL))
    {
      GFileInfo* info = NULL;
      const gchar* type = NULL;
      const gchar* errm = NULL;

      info =
      g_file_query_info (file, G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE, 0, cancellable, &tmp_err);
      if (G_UNLIKELY (tmp_err != NULL))
        {
          g_propagate_error (error, tmp_err);
          _g_object_unref0 (info);
          return FALSE;
        }

      type =
      g_file_info_get_content_type (info);
      if (g_content_type_is_a (type, "application/x-sharedlib"))
        {
          errm = g_module_error ();
          _g_object_unref0 (info);
          g_set_error
          (error,
           HCL_MODULE_MANAGER_ERROR,
           HCL_MODULE_MANAGER_ERROR_MISSING,
           "Can't load module '%s'",
           errm);
          return FALSE;
        }
      else
        {
#if DEBUG == 1 && !QUIET_BOOTUP
          g_warning ("File '%s' is not a loadable module", filename);
#endif // DEBUG
          _g_object_unref0 (info);
          return TRUE;
        }
    }
  else
    {
      success =
      g_hash_table_lookup_extended (self->loaded, handle, NULL, NULL);
      if (success == TRUE)
        {
#if DEBUG == 1 && !QUIET_BOOTUP
          g_warning ("Module '%s' already loaded", filename);
#endif // DEBUG
          goto _error_;
        }
    }

  success =
  g_module_symbol (handle, HCL_MODULE_ENTRY_NAME, (gpointer*) &entry);
  if (G_UNLIKELY (entry == NULL || success == FALSE))
    {
      g_set_error_literal
      (error,
       HCL_MODULE_MANAGER_ERROR,
       HCL_MODULE_MANAGER_ERROR_UNDEFINED_INIT,
       "Missing symbol '" HCL_MODULE_ENTRY_NAME "'");
      success = FALSE;
      goto _error_;
    }

  module = (entry) (&tmp_err);
  if (G_UNLIKELY (tmp_err != NULL))
    {
      g_propagate_error (error, tmp_err);
      success = FALSE;
      goto _error_;
    }
  if (G_UNLIKELY (module == NULL))
    {
      g_set_error
      (error,
       HCL_MODULE_MANAGER_ERROR,
       HCL_MODULE_MANAGER_ERROR_FAILED,
       "Module '%s' initialization function returns nothing",
       filename);
      success = FALSE;
      goto _error_;
    }

  success =
  hcl_module_is_consistent (module);
  if (G_UNLIKELY (success == FALSE))
    {
      g_set_error
      (error,
       HCL_MODULE_MANAGER_ERROR,
       HCL_MODULE_MANAGER_ERROR_INCONSISTENT,
       "Module '%s' returns an inconsistent state",
       filename);
      success = FALSE;
      goto _error_;
    }

  id = hcl_module_get_id (module);

  success = !
  g_hash_table_lookup_extended (self->registry, id, NULL, NULL);
  if (G_UNLIKELY (success == FALSE))
    {
      g_set_error
      (error,
       HCL_MODULE_MANAGER_ERROR,
       HCL_MODULE_MANAGER_ERROR_ALREADY,
       "Already registered a module with id '%s'",
       id);
      goto _error_;
    }
  else
    {
      reg = g_slice_new (Module);
      g_hash_table_insert (self->registry, g_strdup (id), reg);
      g_hash_table_insert (self->loaded, handle, NULL);
      appendto_menu (self, module);
    }

  reg->module = g_steal_pointer (&module);
  reg->handle = g_steal_pointer (&handle);

_error_:
  _g_object_unref0 (module);
  _g_module_close0 (handle);
return success;
}

static gboolean
load_folder (HclModuleManager* self, GFile* file, GCancellable* cancellable, GError** error)
{
  gboolean success = TRUE;
  GError *tmp_err = NULL;
  GFileEnumerator* direnum;
  GFileType type = 0;
  GFileInfo* info = NULL;
  GFile* child = NULL;

  const gchar* attrs =
    {
      G_FILE_ATTRIBUTE_STANDARD_NAME ","
      G_FILE_ATTRIBUTE_STANDARD_TYPE
    };

  direnum =
  g_file_enumerate_children (file, attrs, 0, cancellable, &tmp_err);
  if (G_UNLIKELY (tmp_err != NULL))
    {
      g_propagate_error (error, tmp_err);
      return FALSE;
    }

  do
    {
      success =
      g_file_enumerator_iterate (direnum, &info, &child, cancellable, &tmp_err);
      if (G_UNLIKELY (tmp_err != NULL))
        {
          g_propagate_error (error, tmp_err);
          break;
        }

      if (child != NULL)
        {
          type = g_file_info_get_file_type (info);
#if DEVELOPER == 1
          if (g_file_peek_path (child) [0] == '.')
            continue;
#endif // DEVELOPER

          switch (type)
          {
          case G_FILE_TYPE_REGULAR:
            success =
            load_single (self, child, cancellable, &tmp_err);
            if (G_UNLIKELY (tmp_err != NULL))
              {
                g_propagate_error (error, tmp_err);
                success = FALSE;
              }
            break;
          case G_FILE_TYPE_DIRECTORY:
            success =
            load_folder (self, child, cancellable, &tmp_err);
            if (G_UNLIKELY (tmp_err != NULL))
              {
                g_propagate_error (error, tmp_err);
                success = FALSE;
              }
            break;
          }
        }
      else break;
    }
  while (success == TRUE);
  g_object_unref (direnum);
return success;
}

/*
 * API
 *
 */

HclModuleManager*
hcl_module_manager_new (GError** error)
{
  return
  (HclModuleManager*)
  g_initable_new
  (HCL_TYPE_MODULE_MANAGER,
   NULL,
   error,
   NULL);
}

GMenu*
hcl_module_manager_get_menu (HclModuleManager* manager)
{
  g_return_val_if_fail (HCL_IS_MODULE_MANAGER (manager), NULL);
return manager->menu;
}

void
hcl_module_manager_add_path (HclModuleManager* manager, GFile* path)
{
  g_return_if_fail (HCL_MODULE_MANAGER (manager));
  manager->paths = g_slist_prepend (manager->paths, g_object_ref (path));
}

gboolean
hcl_module_manager_load (HclModuleManager* manager, GFile* file, GError** error)
{
  g_return_val_if_fail (HCL_MODULE_MANAGER (manager), FALSE);
return load_single (manager, file, NULL, error);
}

gboolean
hcl_module_manager_load_all (HclModuleManager* manager, GError** error)
{
  g_return_val_if_fail (HCL_MODULE_MANAGER (manager), FALSE);
  gboolean success = FALSE;
  GError* tmp_err = NULL;
  GSList* list = NULL;

  for (list = manager->paths; list != NULL; list = list->next)
    {
      success =
      load_folder (manager, list->data, NULL, &tmp_err);
      if (G_UNLIKELY (tmp_err != NULL))
        {
          g_propagate_error (error, tmp_err);
          break;
        }
    }
return success;
}

GMenu*
hcl_module_manager_get_appereance (HclModuleManager* manager, const char* id)
{
  g_return_val_if_fail (HCL_MODULE_MANAGER (manager), NULL);
  Module* reg = NULL;
  gboolean found;

  found =
  g_hash_table_lookup_extended (manager->registry, id, NULL, (gpointer*) &reg);
  if (G_UNLIKELY (found == FALSE))
    {
      g_critical ("(%s: %i): Unknown module '%s'", G_STRLOC, __LINE__, id);
      g_assert_not_reached ();
    }
  else
    {
      return hcl_module_get_appereance (reg->module);
    }
return NULL;
}

HclModuleLayout*
hcl_module_manager_get_layout (HclModuleManager* manager, const char* id)
{
  g_return_val_if_fail (HCL_MODULE_MANAGER (manager), NULL);
  Module* reg = NULL;
  gboolean found;

  found =
  g_hash_table_lookup_extended (manager->registry, id, NULL, (gpointer*) &reg);
  if (G_UNLIKELY (found == FALSE))
    {
      g_critical ("(%s: %i): Unknown module '%s'", G_STRLOC, __LINE__, id);
      g_assert_not_reached ();
    }
  else
    {
      return hcl_module_get_layout (reg->module);
    }
return NULL;
}
