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

modules_LTLIBRARIES=libprogrammer.la

libprogrammer_la_SOURCES=\
	layout.vala \
	module.vala \
	width_button.vala \
	$(VOID)
libprogrammer_la_CFLAGS=\
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	$(GTK_CFLAGS) \
	$(MATHCORE_CFLAGS) \
	$(MATHLIB_CFLAGS) \
	-I${top_builddir}/src/module/ \
	-DG_LOG_DOMAIN=\"Halckulator.Module.Programmer\" \
	-DGAPPNAME=\"org.hck.${PACKAGE_NAME}.programmer\" \
	-DGRESNAME=\"/org/hck/${PACKAGE_NAME}/programmer\" \
	$(VOID)
libprogrammer_la_LIBADD=\
	$(GIO_LIBS) \
	$(GLIB_LIBS) \
	$(GOBJECT_LIBS) \
	$(GTK_LIBS) \
	$(MATHCORE_LIBS) \
	$(MATHLIB_LIBS) \
	gtk/libbundle.la \
	$(VOID)
libprogrammer_la_LDFLAGS=\
	-module \
	-rpath ${modulesdir} \
	-release ${PACKAGE_RELEASE} \
	-version-info ${PACKAGE_VERSION_MAYOR}:${PACKAGE_VERSION_MINOR}:${PACKAGE_VERSION_MICRO} \
	$(VOID)

#
# Vala
#

AM_VALAFLAGS=\
	--vapidir=vapi/ \
	--vapidir=${top_builddir}/src/mathcore/ \
	--vapidir=${top_builddir}/src/mathlib/ \
	--vapidir=${top_builddir}/src/module/ \
	--vapi-comments \
	--hide-internal \
	--abi-stability \
	--pkg config \
	--pkg libhclmodule \
	--pkg libmathcore \
	--pkg libmathlib \
	-D DEBUG=${DEBUG} \
	-D DEVELOPER=${DEVELOPER} \
	--gresources "gtk/resources.gresources.xml" \
	$(VOID)
