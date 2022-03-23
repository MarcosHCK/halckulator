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
#include <settings.h>

G_DEFINE_QUARK
(hcl-manager-error-quark,
 hcl_manager_error);

#define HCL_SETTINGS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), HCL_TYPE_SETTINGS, HclSettingsClass))
#define HCL_IS_SETTINGS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), HCL_TYPE_SETTINGS))
#define HCL_SETTINGS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), HCL_TYPE_SETTINGS, HclSettingsClass))
typedef struct _HclSettingsClass HclSettingsClass;

static GWeakRef __default__ = {0};
#define _g_object_unref0(var) (var = (var != NULL) ? (g_object_unref (var), NULL) : NULL)

#ifndef ABSTOPBUILDDIR
# define ABSTOPBUILDDIR "(1)"
#endif // !ABSTOPBUILDDIR

static void
g_initable_iface_init (GInitableIface* iface);

struct _HclSettings
{
  GObject parent_instance;
  GSettingsSchemaSource* source;
  GHashTable* schemas;
};

struct _HclSettingsClass
{
  GObjectClass parent_class;
};

G_DEFINE_FINAL_TYPE_WITH_CODE
(HclSettings,
 hcl_settings,
 G_TYPE_OBJECT,
 G_IMPLEMENT_INTERFACE
 (G_TYPE_INITABLE,
  g_initable_iface_init));

static gboolean
g_initable_iface_init_sync (GInitable* pself, GCancellable* cancellable, GError** error)
{
  HclSettings* self = HCL_SETTINGS (pself);
  HclSettings* default_ = NULL;
  gboolean success = TRUE;
  GError* tmp_err = NULL;

  self->source =
  g_settings_schema_source_new_from_directory
  (
#if DEVELOPER == 1
   ABSTOPBUILDDIR "/src/settings",
#else
   SCHEMASDIR,
#endif // DEVELOPER
   g_settings_schema_source_get_default (),
   TRUE, &tmp_err);
  if (G_UNLIKELY (tmp_err != NULL))
    {
      g_propagate_error (error, tmp_err);
      return FALSE;
    }

  default_ = g_weak_ref_get (&__default__);
  if (G_UNLIKELY (default_ != NULL))
    g_warning ("Overwriting default settings object");
  g_weak_ref_set (&__default__, self);
  _g_object_unref0 (default_);
return success;
}

static void
g_initable_iface_init (GInitableIface* iface)
{
  iface->init = g_initable_iface_init_sync;
}

static void
hcl_settings_class_finalize (GObject* pself)
{
  HclSettings* self = HCL_SETTINGS (pself);
  g_settings_schema_source_unref (self->source);
  g_hash_table_unref (self->schemas);
G_OBJECT_CLASS (hcl_settings_parent_class)->finalize (pself);
}

static void
hcl_settings_class_dispose (GObject* pself)
{
  HclSettings* self = HCL_SETTINGS (pself);
  g_hash_table_remove_all (self->schemas);
G_OBJECT_CLASS (hcl_settings_parent_class)->dispose (pself);
}

static void
hcl_settings_class_init (HclSettingsClass* klass)
{
  GObjectClass* oclass = G_OBJECT_CLASS (klass);

  oclass->finalize = hcl_settings_class_finalize;
  oclass->dispose = hcl_settings_class_dispose;
}

static void
hcl_settings_init (HclSettings* self)
{
  self->schemas =
  g_hash_table_new_full
  (g_str_hash,
   g_str_equal,
   g_free,
   (GDestroyNotify)
   g_settings_schema_unref);
}

/*
 * API
 *
 */

HclSettings*
hcl_settings_new (GError** error)
{
  return
  g_initable_new
  (HCL_TYPE_SETTINGS,
   NULL,
   error,
   NULL);
}

HclSettings *
hcl_settings_get_default()
{
  return
  g_weak_ref_get (&__default__);
}

static GSettingsSchema*
get_schema (HclSettings* self, const gchar* schemaid)
{
  GSettingsSchema* schema = NULL;

  schema =
  g_hash_table_lookup (self->schemas, schemaid);
  if (G_UNLIKELY (schema == NULL))
    {
      schema =
      g_settings_schema_source_lookup (self->source, schemaid, TRUE);
      if (G_UNLIKELY (schema == NULL))
        return NULL;
      g_hash_table_insert (self->schemas, g_strdup (schemaid), schema);
    }
return schema;
}

GSettings*
hcl_settings_get_settings (HclSettings* settings, const gchar* schemaid)
{
  g_return_val_if_fail (HCL_IS_SETTINGS (settings), NULL);
  g_return_val_if_fail (schemaid != NULL, NULL);
  GSettingsSchema* schema = get_schema (settings, schemaid);
return g_settings_new_full (schema, NULL, NULL);
}
