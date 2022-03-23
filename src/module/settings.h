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
#ifndef __HCL_SETTINGS__
#define __HCL_SETTINGS__ 1
#include <gio/gio.h>

#define HCL_SETTINGS_ERROR (hcl_settings_error_quark ())

typedef enum
{
  HCL_SETTINGS_ERROR_FAILED,
} HclSettingsError;

#define HCL_TYPE_SETTINGS (hcl_settings_get_type ())
#define HCL_SETTINGS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), HCL_TYPE_SETTINGS, HclSettings))
#define HCL_IS_SETTINGS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HCL_TYPE_SETTINGS))
typedef struct _HclSettings HclSettings;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GQuark
hcl_settings_error_quark (void) G_GNUC_CONST;
GType
hcl_settings_get_type (void) G_GNUC_CONST;

/*
 * API
 *
 */

HclSettings*
hcl_settings_new (GError** error);
HclSettings*
hcl_settings_get_default ();
GSettings*
hcl_settings_get_settings (HclSettings* settings, const gchar* schemaid);

#if __cplusplus
}
#endif // __cplusplus

#endif // __HCL_SETTINGS__
