##############################################################################
#
#    file                 : Makefile
#    created              : Tue Oct 28 10:41:07 EDT 2014
#    copyright            : (C) 2002 pauldrews
#
##############################################################################

ROBOT       = racerx
MODULE      = ${ROBOT}.so
MODULEDIR   = drivers/${ROBOT}
SOURCES     = ${ROBOT}.cpp

SHIPDIR     = drivers/${ROBOT}
SHIP        = ${ROBOT}.xml 
SHIPSUBDIRS = 

PKGSUBDIRS  = ${SHIPSUBDIRS}
src-robots-racerx_PKGFILES = $(shell find * -maxdepth 0 -type f -print)
src-robots-racerx_PKGDIR   = ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}
