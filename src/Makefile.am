# Copyright 2021-2025 MarcosHCK
# This file is part of halckulator.
#
# halckulator is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# halckulator is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with halckulator. If not, see <http://www.gnu.org/licenses/>.
#

# Keep sync with
# - src/Makefile.am
# - src/modules/basic/Makefile.am
modulesdir=${pkglibdir}/modules

# Keep sync with
# - src/Makefile.am
# - src/module/Makefile.am
# - src/settings/Makefile.am
schemasdir=${pkgdatadir}/schemas
VOID=

#
# Subdirectories
#

SUBDIRS=\
	module \
	modules \
	resources \
	settings \
	$(VOID)

#
# C headers
#

EXTRA_DIST=\
	vapi/config.deps \
	vapi/config.vapi \
	$(VOID)

#
# Binaries and libraries
#

bin_PROGRAMS=halckulator

halckulator_SOURCES=\
	gtk/application.vala \
	gtk/manager.vala \
	gtk/message.vala \
	gtk/window.vala \
	main.c
	$(VOID)
halckulator_CFLAGS=\
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	$(GTK_CFLAGS) \
	-Imodule/ \
	-DG_LOG_DOMAIN=\"Halckulator\" \
	-DGAPPNAME=\"org.hck.${PACKAGE_NAME}\" \
	-DGRESNAME=\"/org/hck/${PACKAGE_NAME}\" \
	-DGETTEXT_PACKAGE=\"${GETTEXT_PACKAGE}\" \
	-DABSTOPBUILDDIR=\"${abs_top_builddir}\" \
	-DMODULESDIR=\"${modulesdir}\" \
	-DSCHEMASDIR=\"${schemasdir}\" \
	$(VOID)
halckulator_LDADD=\
	$(GIO_LIBS) \
	$(GLIB_LIBS) \
	$(GOBJECT_LIBS) \
	$(GTK_LIBS) \
	module/libmodule.la \
	resources/libbundle.la \
	$(VOID)

#
# Vala
#

AM_VALAFLAGS=\
	--vapidir=vapi/ \
	--vapidir=module/ \
	--vapi-comments \
	--hide-internal \
	--abi-stability \
	--pkg config \
	--pkg libmodule \
	-D DEBUG=${DEBUG} \
	-D DEVELOPER=${DEVELOPER} \
	--gresources "resources/bundle.gresources.xml" \
	$(VOID)
