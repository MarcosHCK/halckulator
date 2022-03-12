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
#ifndef __HCL_PATCH__
#define __HCL_PATCH__ 1
#if !__LIBHCLMODULE_INSIDE__
  #error "Private header"
#endif // __LIBHALCKULATOR_INSIDE__
#include <gio/gio.h>

#define HCL_MODULE_ERROR (hcl_module_error_quark ())

typedef enum
{
  HCL_MODULE_ERROR_FAILED,
  HCL_MODULE_ERROR_INCOMPATIBLE_VERSION,
  HCL_MODULE_ERROR_VERSION_MISMATCH,
} HclModuleError;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GQuark
hcl_module_error_quark (void) G_GNUC_CONST;

G_GNUC_INTERNAL
gboolean
_hcl_patch_module_check_version (const gchar* expected, GError** error);

#if __cplusplus
}
#endif // __cplusplus

#endif // __HCL_PATCH__
