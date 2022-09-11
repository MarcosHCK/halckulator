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
# - src/module/Makefile.am
# - src/settings/Makefile.am
schemasdir=${pkgdatadir}/schemas

#
# Some variables
#

PACKAGE_NAME=@PACKAGE_NAME@
PACKAGE_RELEASE=@PACKAGE_RELEASE@
PACKAGE_VERSION_MAJOR=@PACKAGE_VERSION_MAJOR@
PACKAGE_VERSION_MINOR=@PACKAGE_VERSION_MINOR@
PACKAGE_VERSION_MICRO=@PACKAGE_VERSION_MICRO@
PACKAGE_VERSION_BUILD=@PACKAGE_VERSION_BUILD@
VOID=

#
# C headers
#

EXTRA_DIST=\
	vapi/patch.vapi \
	patch.h \
	$(VOID)

#
# Binaries and libraries
#

pkglib_LTLIBRARIES=libmodule.la

libmodule_la_SOURCES=\
	layout.vala \
	module.vala \
	patch.c \
	version.vala \
	$(VOID)
libmodule_la_CFLAGS=\
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GMODULE_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	$(GTK_CFLAGS) \
	-DG_LOG_DOMAIN=\"Halckulator.Module\" \
	-DGAPPNAME=\"org.hck.${PACKAGE_NAME}\" \
	-DGRESNAME=\"/org/hck/${PACKAGE_NAME}\" \
	$(VOID)
libmodule_la_LIBADD=\
	$(GIO_LIBS) \
	$(GLIB_LIBS) \
	$(GOBJECT_LIBS) \
	$(GTK_LIBS) \
	$(VOID)
libmodule_la_LDFLAGS=\
	-rpath ${pkglibdir} \
	-release ${PACKAGE_RELEASE} \
	-version-info 0:0:0 \
	$(VOID)

#
# Vala
#

AM_VALAFLAGS=\
	--vapidir=../vapi/ \
	--vapidir=vapi/ \
	--vapi-comments \
	--hide-internal \
	--abi-stability \
	--header libmodule.h \
	--library libmodule \
	--pkg config \
	--pkg patch \
	-D DEBUG=${DEBUG} \
	-D DEVELOPER=${DEVELOPER} \
	$(VOID)
