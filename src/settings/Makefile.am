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

EXTRA_DIST=
VOID=

#
# GSettings cache
#

SCHEMAS=\
	org.hck.halckulator.gschema.xml \
	$(VOID)

schemas_DATA=\
	$(SCHEMAS) \
	gschemas.compiled \
	$(VOID)

gschemas.compiled: $(SCHEMAS)
	$(GLIB_COMPILE_SCHEMAS) ${top_builddir}/src/settings/

CLEANFILES=\
	gschemas.compiled \
	$(VOID)
