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
#include <module.h>

G_DEFINE_QUARK
(hcl-module-error-quark,
 hcl_module_error);

#define __invalid_id__ "__invalid_id__"

struct _HclModulePrivate
{
  gchar* id;
  gchar* name;
  gchar* description;
};

enum
{
  prop_0,
  prop_id,
  prop_name,
  prop_description,
  prop_number,
};

static
GParamSpec* properties[prop_number] = {0};

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE
(HclModule,
 hcl_module,
 G_TYPE_OBJECT);

static void
hcl_module_class_set_property (GObject* pself, guint prop_n, const GValue* value, GParamSpec* pspec)
{
  HclModule* self = HCL_MODULE (pself);
  HclModulePrivate* priv = self->priv;
  switch (prop_n)
  {
  case prop_id:
    hcl_module_set_id (self, g_value_get_string (value));
    break;
  case prop_name:
    hcl_module_set_name (self, g_value_get_string (value));
    break;
  case prop_description:
    hcl_module_set_description (self, g_value_get_string (value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (pself, prop_n, pspec);
    break;
  }
}

static void
hcl_module_class_get_property (GObject* pself, guint prop_n, GValue* value, GParamSpec* pspec)
{
  HclModule* self = HCL_MODULE (pself);
  HclModulePrivate* priv = self->priv;
  switch (prop_n)
  {
  case prop_id:
    g_value_set_string (value, hcl_module_get_id (self));
    break;
  case prop_name:
    g_value_set_string (value, hcl_module_get_name (self));
    break;
  case prop_description:
    g_value_set_string (value, hcl_module_get_description (self));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (pself, prop_n, pspec);
    break;
  }
}

static void
hcl_module_class_finalize (GObject* pself)
{
  HclModule* self = HCL_MODULE (pself);
  HclModulePrivate* priv = self->priv;
  g_free (priv->description);
  g_free (priv->name);
  g_free (priv->id);
G_OBJECT_CLASS (hcl_module_parent_class)->finalize (pself);
}

static void
hcl_module_class_dispose (GObject* pself)
{
  HclModule* self = HCL_MODULE (pself);
  HclModulePrivate* priv = self->priv;
G_OBJECT_CLASS (hcl_module_parent_class)->dispose (pself);
}

static void
hcl_module_class_init (HclModuleClass* klass)
{
  GObjectClass* oclass = G_OBJECT_CLASS (klass);

  oclass->set_property = hcl_module_class_set_property;
  oclass->get_property = hcl_module_class_get_property;
  oclass->finalize = hcl_module_class_finalize;
  oclass->dispose = hcl_module_class_dispose;

  properties[prop_id] =
    g_param_spec_string
    ("id",
     "Module id",
     "Module unique identifier",
     __invalid_id__,
     G_PARAM_READWRITE
     | G_PARAM_CONSTRUCT
     | G_PARAM_STATIC_STRINGS);

  properties[prop_name] =
    g_param_spec_string
    ("name",
     "Module name",
     "Module display name",
     NULL,
     G_PARAM_READWRITE
     | G_PARAM_STATIC_STRINGS);

  properties[prop_description] =
    g_param_spec_string
    ("description",
     "Module description",
     "Module display description",
     NULL,
     G_PARAM_READWRITE
     | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties
  (oclass,
   prop_number,
   properties);
}

static void
hcl_module_init (HclModule* self)
{
  self->priv = hcl_module_get_instance_private (self);
}

/*
 * API
 *
 */

void
hcl_module_set_id (HclModule* module, const gchar* value)
{
  g_return_if_fail (HCL_IS_MODULE (module));
  g_return_if_fail (value != NULL);
  HclModulePrivate* priv = module->priv;

  g_clear_pointer (&(priv->id), g_free);
  priv->id = g_strdup (value);
}

void
hcl_module_set_name (HclModule* module, const gchar* value)
{
  g_return_if_fail (HCL_IS_MODULE (module));
  g_return_if_fail (value != NULL);
  HclModulePrivate* priv = module->priv;

  g_clear_pointer (&(priv->name), g_free);
  priv->name = g_strdup (value);
}

void
hcl_module_set_description (HclModule* module, const gchar* value)
{
  g_return_if_fail (HCL_IS_MODULE (module));
  g_return_if_fail (value != NULL);
  HclModulePrivate* priv = module->priv;

  g_clear_pointer (&(priv->description), g_free);
  priv->description = g_strdup (value);
}

const gchar*
hcl_module_get_id (HclModule* module)
{
  g_return_val_if_fail (HCL_IS_MODULE (module), NULL);
return module->priv->id;
}

const gchar*
hcl_module_get_name (HclModule* module)
{
  g_return_val_if_fail (HCL_IS_MODULE (module), NULL);
return module->priv->name;
}

const gchar*
hcl_module_get_description (HclModule* module)
{
  g_return_val_if_fail (HCL_IS_MODULE (module), NULL);
return module->priv->description;
}

GMenu*
hcl_module_get_appereance (HclModule* module)
{
  g_return_val_if_fail (HCL_IS_MODULE (module), NULL);
return HCL_MODULE_GET_CLASS (module)->get_appereance (module);
}

HclModuleLayout*
hcl_module_get_layout (HclModule* module)
{
  g_return_val_if_fail (HCL_IS_MODULE (module), NULL);
return HCL_MODULE_GET_CLASS (module)->get_layout (module);
}

gboolean
hcl_module_is_consistent (HclModule* module)
{
  g_return_val_if_fail (HCL_IS_MODULE (module), FALSE);
return !! g_strcmp0 (module->priv->id, __invalid_id__);
}

enum
{
  BIT_MAYOR,
  BIT_MINOR,
  BIT_MICRO,
  BIT_BUILD,
};

static
guint cur[4] = {0};

#define PRIiBITS "%i.%i.%i.%i"
#define EXPAND_BITS(b) b[0],b[1],b[2],b[3]

gboolean
hcl_module_check_version (const gchar* expected, GError** error)
{
  g_return_val_if_fail (expected != NULL, FALSE);
  g_return_val_if_fail (error == NULL || *error == NULL, FALSE);
  guint bits[4] = {0}, n_bit = 0, i;
  const gchar* bit = expected;

  /*
   * Load version bits
   *
   */

  if (G_UNLIKELY
    (cur[BIT_MAYOR] == 0
  || cur[BIT_MINOR] == 0
  || cur[BIT_MICRO] == 0
  || cur[BIT_BUILD] == 0))
    {
      cur[BIT_MAYOR] = (gint) g_strtod (PACKAGE_VERSION_MAYOR, NULL);
      cur[BIT_MINOR] = (gint) g_strtod (PACKAGE_VERSION_MINOR, NULL);
      cur[BIT_MICRO] = (gint) g_strtod (PACKAGE_VERSION_MICRO, NULL);
      cur[BIT_BUILD] = (gint) g_strtod (PACKAGE_VERSION_BUILD, NULL);
    }

  do
  {
    g_return_val_if_fail (n_bit < 4, FALSE);
    bits[n_bit++] = (gint) g_strtod (bit, NULL);
    bit = g_strstr_len (bit, -1, ".");
  } while (bit && ++bit);

  /*
   * Check if current binary is
   * older than module
   *
   */

  for (i = 0; i < G_N_ELEMENTS (bits); i++)
    {
      if (G_UNLIKELY (bits[i] > cur[i]))
        {
          g_set_error
          (error,
           HCL_MODULE_ERROR,
           HCL_MODULE_ERROR_INCOMPATIBLE_VERSION,
           "Halckulator expected version '" PRIiBITS "' is greater than this build '" PRIiBITS "'\r\n",
           EXPAND_BITS (bits), EXPAND_BITS (cur));
          return FALSE;
        }
    }

  /*
   * Mayor build are expected to
   * be ABI-incompatible
   *
   */

  if G_UNLIKELY(bits[BIT_MAYOR] != cur[BIT_MAYOR])
    {
      g_set_error
      (error,
       HCL_MODULE_ERROR,
       HCL_MODULE_ERROR_INCOMPATIBLE_VERSION,
       "Halckulator expected version '" PRIiBITS "' doesn't match this build '" PRIiBITS "'\r\n",
       EXPAND_BITS(bits), EXPAND_BITS(cur));
      return FALSE;
    }

  /*
   * If version mismatches
   * but reaches this point
   * means module should work
   * correctly, although I don't
   * recommend it so emit a little
   * warning
   *
   */

  for(i = 0;i < G_N_ELEMENTS(bits);i++)
    {
      if G_UNLIKELY(bits[i] > cur[i])
        {
          g_set_error
          (error,
           HCL_MODULE_ERROR,
           HCL_MODULE_ERROR_VERSION_MISMATCH,
           "Halckulator expected version '" PRIiBITS "' doesn't match this build '" PRIiBITS "'\r\n",
           EXPAND_BITS(bits), EXPAND_BITS(cur));
          return FALSE;
        }
    }
return TRUE;
}
