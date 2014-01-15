## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po

printer_message_editordocdir = ${prefix}/doc/printer_message_editor
printer_message_editordoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(printer_message_editordoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(printer_message_editordocdir)
