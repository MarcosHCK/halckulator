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
#ifndef __HCL_MODULE__
#define __HCL_MODULE__ 1
#include <gio/gio.h>
#include <module_layout.h>

#define HCL_MODULE_ERROR (hcl_module_error_quark ())

typedef enum
{
  HCL_MODULE_ERROR_FAILED,
  HCL_MODULE_ERROR_INCOMPATIBLE_VERSION,
  HCL_MODULE_ERROR_VERSION_MISMATCH,
} HclModuleError;

#define HCL_TYPE_MODULE (hcl_module_get_type ())
#define HCL_MODULE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), HCL_TYPE_MODULE, HclModule))
#define HCL_MODULE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), HCL_TYPE_MODULE, HclModuleClass))
#define HCL_IS_MODULE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HCL_TYPE_MODULE))
#define HCL_IS_MODULE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), HCL_TYPE_MODULE))
#define HCL_MODULE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), HCL_TYPE_MODULE, HclModuleClass))

typedef struct _HclModule HclModule;
typedef struct _HclModulePrivate HclModulePrivate;
typedef struct _HclModuleClass HclModuleClass;

#if __cplusplus
    extern "C" {
#endif // __cplusplus

GQuark
hcl_module_error_quark (void) G_GNUC_CONST;
GType
hcl_module_get_type (void) G_GNUC_CONST;

struct _HclModule
{
  GObject parent_instance;
  HclModulePrivate* priv;
};

struct _HclModuleClass
{
  GObjectClass parent_class;
  GMenu* (*get_appereance) (HclModule* module);
  HclModuleLayout* (*get_layout) (HclModule* module);
};

/*
 * API
 *
 */

void
hcl_module_set_id (HclModule* module, const gchar* value);
void
hcl_module_set_name (HclModule* module, const gchar* value);
void
hcl_module_set_description (HclModule* module, const gchar* value);
const gchar*
hcl_module_get_id (HclModule* module);
const gchar*
hcl_module_get_name (HclModule* module);
const gchar*
hcl_module_get_description (HclModule* module);
GMenu*
hcl_module_get_appereance (HclModule* module);
HclModuleLayout*
hcl_module_get_layout (HclModule* module);
gboolean
hcl_module_is_consistent (HclModule* module);
gboolean
hcl_module_check_version (const gchar* expected, GError** error);

#if __cplusplus
}
#endif // __cplusplus

#endif // __HCL_MODULE__
