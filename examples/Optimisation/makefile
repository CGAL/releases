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
                example_Min_circle_2 \
                example_Min_ellipse_2 

example_Min_circle_2: example_Min_circle_2.o
	$(CGAL_CXX) -o example_Min_circle_2 example_Min_circle_2.o $(LDFLAGS)

example_Min_ellipse_2: example_Min_ellipse_2.o
	$(CGAL_CXX) -o example_Min_ellipse_2 example_Min_ellipse_2.o $(LDFLAGS)

clean:
	rm -f *.o \
                   example_Min_circle_2 \
                   example_Min_ellipse_2 \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

