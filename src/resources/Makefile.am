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

EXTRA_DIST=
VOID=

#
# Resources
#

RESOURCES=\
	$(shell $(GLIB_COMPILE_RESOURCES) --generate-dependencies bundle.gresources.xml) \
	$(VOID)

EXTRA_DIST+=\
	$(RESOURCES) \
	$(VOID)
	
CLEANFILES=\
	bundle.c \
	bundle.h \
	$(VOID)

#
# *.gresources.xml to *.c and *.h make target
#

SUFFIXES=.gresources.xml .c .h

.gresources.xml.c:
	$(GLIB_COMPILE_RESOURCES) --target=$@ --generate-source $<
.gresources.xml.h:
	$(GLIB_COMPILE_RESOURCES) --target=$@ --generate-header $<

#
# Binaries and libraries
#

noinst_LTLIBRARIES=libbundle.la

noinst_DATA=\
	bundle.h \
	$(VOID)

libbundle_la_SOURCES=\
	bundle.c \
	$(VOID)
libbundle_la_CFLAGS=\
	$(GIO_CFLAGS) \
	$(VOID)
libbundle_la_LIBADD=\
	$(GIO_LIBS) \
	$(VOID)
libbundle_la_LDFLAGS=\
	-static \
	$(VOID)
