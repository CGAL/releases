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
                BooleanOperations_example \
                Howto_Intersection_example 

BooleanOperations_example: BooleanOperations_example.o
	$(CGAL_CXX) -o BooleanOperations_example BooleanOperations_example.o $(LDFLAGS)

Howto_Intersection_example: Howto_Intersection_example.o
	$(CGAL_CXX) -o Howto_Intersection_example Howto_Intersection_example.o $(LDFLAGS)

clean:
	/bin/rm -f *.o \
                   BooleanOperations_example \
                   Howto_Intersection_example \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

