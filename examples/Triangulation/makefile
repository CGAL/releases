# This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

CGAL_MAKEFILE = /KM/projects/CGAL/CGAL-1.0/make/makefile_sparc_SunOS-5.5.1_CC-4.2_LEDA
include $(CGAL_MAKEFILE)

CXX = g++


#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CXXFLAGS = -I. -I../../include $(CGAL_CXXFLAGS) -DDELAUNAY
           

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = $(CGAL_LDFLAGS)
WINDOW_LDFLAGS = $(CGAL_WINDOW_LDFLAGS)

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#

# QUANTIFY = quantify

all: points example voronoi

points: points.o
	$(CGAL_CXX) -o points points.o $(LDFLAGS)

example: example.o
	$(CGAL_CXX) -o example example.o $(LDFLAGS)

voronoi: voronoi.o
	$(CGAL_CXX) -o voronoi voronoi.o $(LDFLAGS)

clean:
	- /bin/rm  *~ *.o core tr

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<
