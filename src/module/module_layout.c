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
#include <module_layout.h>

static GMutex lock;

struct _HclModuleLayoutPrivate
{
  GtkAccelGroup* accelgroup;
};

enum
{
  sig_undo,
  sig_redo,
  sig_cut,
  sig_copy,
  sig_paste,
  sig_number,
};

static
guint signals[sig_number] = {0};

G_DEFINE_TYPE_EXTENDED
(HclModuleLayout,
 hcl_module_layout,
 GTK_TYPE_GRID,
#if DEVELOPER == 1
 0,
#else //!DEVELOPER
 G_TYPE_FLAG_ABSTRACT,
#endif // DEVELOPER
 G_ADD_PRIVATE
 (HclModuleLayout));

static void
on_hierarchy_changed (GtkWidget* pself, GtkWidget* toplevel, GtkAccelGroup* group)
{
  if (toplevel == NULL)
    {
      toplevel = gtk_widget_get_toplevel (pself);
      gtk_window_add_accel_group ((GtkWindow*) toplevel, group);
    }
  else
    {
      gtk_window_remove_accel_group ((GtkWindow*) toplevel, group);
    }
}

static void
hcl_module_layout_constructed (GObject* pself)
{
  G_OBJECT_CLASS (hcl_module_layout_parent_class)->constructed (pself);
  HclModuleLayout* self = HCL_MODULE_LAYOUT (pself);
  GtkWidget* parent;

  parent =
  gtk_widget_get_parent ((GtkWidget*) self);
  g_assert (parent != NULL);

  g_object_ref (self);
  gtk_container_remove ((GtkContainer*) parent, (GtkWidget*) self);
  g_object_force_floating ((GObject*) self);
  gtk_widget_destroy (parent);

  g_signal_connect
  (self,
   "hierarchy-changed",
   G_CALLBACK (on_hierarchy_changed),
   self->priv->accelgroup);
}

static void
hcl_module_layout_class_finalize (GObject* pself)
{
  HclModuleLayout* self = HCL_MODULE_LAYOUT (pself);
  HclModuleLayoutPrivate* priv = self->priv;
G_OBJECT_CLASS (hcl_module_layout_parent_class)-> finalize (pself);
}

static void
hcl_module_layout_class_dispose (GObject* pself)
{
  HclModuleLayout* self = HCL_MODULE_LAYOUT (pself);
  HclModuleLayoutPrivate* priv = self->priv;
  g_clear_object (&(priv->accelgroup));
G_OBJECT_CLASS (hcl_module_layout_parent_class)-> dispose (pself);
}

static void
hcl_module_layout_class_init (HclModuleLayoutClass* klass)
{
  GObjectClass* oclass = G_OBJECT_CLASS (klass);

  oclass->constructed = hcl_module_layout_constructed;
  oclass->finalize = hcl_module_layout_class_finalize;
  oclass->dispose = hcl_module_layout_class_dispose;

  signals[sig_undo] =
    g_signal_new
    ("undo",
     G_TYPE_FROM_CLASS (klass),
     G_SIGNAL_ACTION,
     G_STRUCT_OFFSET
     (HclModuleLayoutClass,
      undo),
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0,
      G_TYPE_NONE);

  signals[sig_redo] =
    g_signal_new
    ("redo",
     G_TYPE_FROM_CLASS (klass),
     G_SIGNAL_ACTION,
     G_STRUCT_OFFSET
     (HclModuleLayoutClass,
      redo),
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0,
      G_TYPE_NONE);

  signals[sig_cut] =
    g_signal_new
    ("cut",
     G_TYPE_FROM_CLASS (klass),
     G_SIGNAL_ACTION,
     G_STRUCT_OFFSET
     (HclModuleLayoutClass,
      cut),
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0,
      G_TYPE_NONE);

  signals[sig_copy] =
    g_signal_new
    ("copy",
     G_TYPE_FROM_CLASS (klass),
     G_SIGNAL_ACTION,
     G_STRUCT_OFFSET
     (HclModuleLayoutClass,
      copy),
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0,
      G_TYPE_NONE);

  signals[sig_paste] =
    g_signal_new
    ("paste",
     G_TYPE_FROM_CLASS (klass),
     G_SIGNAL_ACTION,
     G_STRUCT_OFFSET
     (HclModuleLayoutClass,
      paste),
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0,
      G_TYPE_NONE);
}

static void
hcl_module_layout_init (HclModuleLayout* self)
{
  self->priv = hcl_module_layout_get_instance_private (self);
  self->priv->accelgroup = gtk_accel_group_new ();

  GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  GtkAccelGroup* group = self->priv->accelgroup;

  gtk_container_add ((GtkContainer*) window, (GtkWidget*) self);
  gtk_window_add_accel_group ((GtkWindow*) window, group);
}
