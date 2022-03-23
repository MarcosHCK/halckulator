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
#ifndef __HCL_MODULE_MANAGER__
#define __HCL_MODULE_MANAGER__ 1
#include <gio/gio.h>
#include <module_layout.h>

#define HCL_MODULE_MANAGER_ERROR (hcl_module_manager_error_quark ())

typedef enum
{
  HCL_MODULE_MANAGER_ERROR_FAILED,
  HCL_MODULE_MANAGER_ERROR_MISSING,
  HCL_MODULE_MANAGER_ERROR_UNDEFINED_INIT,
  HCL_MODULE_MANAGER_ERROR_INCONSISTENT,
  HCL_MODULE_MANAGER_ERROR_ALREADY,
} HclModuleManagerError;

#define HCL_TYPE_MODULE_MANAGER (hcl_module_manager_get_type ())
#define HCL_MODULE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), HCL_TYPE_MODULE_MANAGER, HclModuleManager))
#define HCL_IS_MODULE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HCL_TYPE_MODULE_MANAGER))
typedef struct _HclModuleManager HclModuleManager;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GQuark
hcl_module_manager_error_quark (void) G_GNUC_CONST;
GType
hcl_module_manager_get_type (void) G_GNUC_CONST;

HclModuleManager*
hcl_module_manager_new (GError** error);
GMenu*
hcl_module_manager_get_menu (HclModuleManager* manager);
void
hcl_module_manager_add_path (HclModuleManager* manager, GFile* path);
gboolean
hcl_module_manager_load (HclModuleManager* manager, GFile* file, GError** error);
gboolean
hcl_module_manager_load_all (HclModuleManager* manager, GError** error);
GMenu*
hcl_module_manager_get_appereance (HclModuleManager* manager, const char* id);
HclModuleLayout*
hcl_module_manager_get_layout (HclModuleManager* manager, const char* id);

#if __cplusplus
}
#endif // __cplusplus

#endif // __HCL_MODULE_MANAGER__
