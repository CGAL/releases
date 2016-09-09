# This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

# CGAL_MAKEFILE = ENTER_YOUR_INCLUDE_MAKEFILE_HERE
include $(CGAL_MAKEFILE)

#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CXXFLAGS = \
           $(TESTSUITE_CXXFLAGS) \
           $(CGAL_CXXFLAGS) \
           -g

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = \
          $(TESTSUITE_LDFLAGS) \
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

