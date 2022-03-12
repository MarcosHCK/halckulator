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
#ifndef __HCL_MODULE_ENTRY__
#define __HCL_MODULE_ENTRY__ 1
#include <gio/gio.h>
#include <gmodule.h>

#define HCL_MODULE_ENTRY_SIGNATURE_FUNCTION hcl_module_entry
#define HCL_MODULE_ENTRY_SIGNATURE G_STRINGIFY(HCL_MODULE_ENTRY_SIGNATURE_FUNCTION)

#if __cplusplus
extern "C" {
#endif // __cplusplus

/*
 * Automatically export entry point
 *
 */

G_MODULE_EXPORT
gpointer
HCL_MODULE_ENTRY_SIGNATURE_FUNCTION (GError** error);

#if __cplusplus
}
#endif // __cplusplus

#endif // __HCL_MODULE_ENTRY__
