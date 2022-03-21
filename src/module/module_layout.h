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
#ifndef __HCL_MODULE_LAYOUT__
#define __HCL_MODULE_LAYOUT__ 1
#include <gtk/gtk.h>

#define HCL_TYPE_MODULE_LAYOUT (hcl_module_layout_get_type ())
#define HCL_MODULE_LAYOUT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), HCL_TYPE_MODULE_LAYOUT, HclModuleLayout))
#define HCL_MODULE_LAYOUT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), HCL_TYPE_MODULE_LAYOUT, HclModuleLayoutClass))
#define HCL_IS_MODULE_LAYOUT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HCL_TYPE_MODULE_LAYOUT))
#define HCL_IS_MODULE_LAYOUT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), HCL_TYPE_MODULE_LAYOUT))
#define HCL_MODULE_LAYOUT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), HCL_TYPE_MODULE_LAYOUT, HclModuleLayoutClass))

typedef struct _HclModuleLayout HclModuleLayout;
typedef struct _HclModuleLayoutPrivate HclModuleLayoutPrivate;
typedef struct _HclModuleLayoutClass HclModuleLayoutClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
hcl_module_layout_get_type (void) G_GNUC_CONST;

struct _HclModuleLayout
{
  GtkGrid parent_instance;
  HclModuleLayoutPrivate* priv;
};

struct _HclModuleLayoutClass
{
  GtkGridClass parent_class;
  void (*undo) (HclModuleLayout* layout);
  void (*redo) (HclModuleLayout* layout);
  void (*cut) (HclModuleLayout* layout);
  void (*copy) (HclModuleLayout* layout);
  void (*paste) (HclModuleLayout* layout);
};

#if __cplusplus
}
#endif // __cplusplus

#endif // __HCL_MODULE_LAYOUT__
