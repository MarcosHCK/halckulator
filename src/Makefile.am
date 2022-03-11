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

# Keep sync with settings/Makefile.am
schemasdir=${pkgdatadir}/schemas

# Keep sync with src/Makefile.am
girdir=${pkgdatadir}/gir

#
# Some variables
#

PACKAGE_NAME=@PACKAGE_NAME@
PACKAGE_RELEASE=@PACKAGE_RELEASE@
PACKAGE_VERSION_MAYOR=@PACKAGE_VERSION_MAYOR@
PACKAGE_VERSION_MINOR=@PACKAGE_VERSION_MINOR@
PACKAGE_VERSION_MICRO=@PACKAGE_VERSION_MICRO@
PACKAGE_VERSION_BUILD=@PACKAGE_VERSION_BUILD@

EXTRA_DIST=
CLEANFILES=
VOID=

#
# Subdirectories
#

SUBDIRS=\
	gtk \
	settings \
	$(VOID)

#
# C headers
#

EXTRA_DIST+=\
	vapi/config.deps \
	vapi/config.vapi \
	$(VOID)

#
# Binaries and libraries
#

pkglib_LTLIBRARIES=libhalckulator.la
bin_PROGRAMS=halckulator

libhalckulator_la_SOURCES=\
	hcl_application.vala \
	$(VOID)
libhalckulator_la_CFLAGS=\
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GMODULE_CFLAGS) \
	$(GOBJECT_INTROSPECTION_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	$(GTK_CFLAGS) \
	-DG_LOG_DOMAIN=\"Halckulator\" \
	-DABSTOPBUILDDIR=\"${abs_top_builddir}\" \
	-DGIRDIR=\"${girdir}\" \
	-DLOCALEDIR=\"${localedir}\" \
	-DSCHEMASDIR=\"${schemasdir}\" \
	-DPKGLIBDIR=\"${pkglibdir}\" \
	-DGAPPNAME=\"org.hck.${PACKAGE_NAME}\" \
	-DGETTEXT_PACKAGE=\"${GETTEXT_PACKAGE}\" \
	-DGRESNAME=\"/org/hck/${PACKAGE_NAME}\" \
	-D__LIBHALCKULATOR_INSIDE__=1 \
	$(VOID)
libhalckulator_la_LIBADD=\
	$(GIO_LIBS) \
	$(GLIB_LIBS) \
	$(GMODULE_LIBS) \
	$(GOBJECT_INTROSPECTION_LIBS) \
	$(GOBJECT_LIBS) \
	$(GTK_LIBS) \
	gtk/libbundle.la \
	$(VOID)
libhalckulator_la_LDFLAGS=\
	-rpath ${pkglibdir} \
	-release ${PACKAGE_RELEASE} \
	-version-info ${PACKAGE_VERSION_MAYOR}:${PACKAGE_VERSION_MINOR}:${PACKAGE_VERSION_MICRO} \
	$(VOID)

halckulator_SOURCES=\
	hcl_main.c
	$(VOID)
halckulator_CFLAGS=\
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GMODULE_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	$(GTK_CFLAGS) \
	$(LUA_CFLAGS) \
	-DG_LOG_DOMAIN=\"Halckulator\" \
	-DGAPPNAME=\"org.hck.${PACKAGE_NAME}\" \
	-DGRESNAME=\"/org/hck/${PACKAGE_NAME}\" \
	-DGETTEXT_PACKAGE=\"${GETTEXT_PACKAGE}\" \
	$(VOID)
halckulator_LDADD=\
	$(GIO_LIBS) \
	$(GLIB_LIBS) \
	$(GMODULE_LIBS) \
	$(GOBJECT_LIBS) \
	$(GTK_LIBS) \
	$(LUA_LIBS) \
	libhalckulator.la \
	$(VOID)

#
# GObject-Introspection
#

include $(INTROSPECTION_MAKEFILE)

GIR_VERSION=${PACKAGE_VERSION_MAYOR}.${PACKAGE_VERSION_MINOR}
GIR_FILENAME=Hcl-${GIR_VERSION}.gir

INTROSPECTION_COMPILER_ARGS=\
	$(VOID)
SUFFIXES=.typelib .gir

${GIR_FILENAME}: $(VOID)

gir_DATA=\
	${GIR_FILENAME} \
	$(GIR_FILENAME:.gir=.typelib) \
	$(VOID)

#
# Vala
#

AM_VALAFLAGS=\
	--vapidir=vapi/ \
	--vapi-comments \
	--hide-internal \
	--abi-stability \
	--header libhalckulator.h \
	--library libhalckulator \
	--gir ${GIR_FILENAME} \
	--pkg config \
	-D DEBUG=${DEBUG} \
	-D DEVELOPER=${DEVELOPER} \
	--gresources "${top_builddir}/src/gtk/resources.gresources.xml" \
	$(VOID)
