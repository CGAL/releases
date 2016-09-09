# This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

CGAL_MAKEFILE = /KM/projects/CGAL/CGAL-1.0/make/makefile_sparc_SunOS-5.5.1_CC-4.2_LEDA
include $(CGAL_MAKEFILE)

#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CXXFLAGS = \
           $(CGAL_CXXFLAGS) \
           -g

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = \
          $(CGAL_LDFLAGS)

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#

all:            \
                CustomPoint1 \
                CustomPoint2 \
                Example \
                Polygon 

CustomPoint1: CustomPoint1.o
	$(CGAL_CXX) -o CustomPoint1 CustomPoint1.o $(LDFLAGS)

CustomPoint2: CustomPoint2.o
	$(CGAL_CXX) -o CustomPoint2 CustomPoint2.o $(LDFLAGS)

Example: Example.o
	$(CGAL_CXX) -o Example Example.o $(LDFLAGS)

Polygon: Polygon.o
	$(CGAL_CXX) -o Polygon Polygon.o $(LDFLAGS)

clean:
	rm -f *.o \
                   CustomPoint1 \
                   CustomPoint2 \
                   Example \
                   Polygon \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

