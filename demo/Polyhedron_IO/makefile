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
           $(LONG_NAME_PROBLEM_CXXFLAGS) \
           $(CGAL_CXXFLAGS) \
           -g

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = \
          $(TESTSUITE_LDFLAGS) \
          $(LONG_NAME_PROBLEM_LDFLAGS) \
          $(CGAL_LDFLAGS)

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#

all:            \
                geomview_demo \
                viewpoint2off 

geomview_demo: geomview_demo.o
	$(CGAL_CXX) -o geomview_demo geomview_demo.o $(LDFLAGS)

viewpoint2off: viewpoint2off.o
	$(CGAL_CXX) -o viewpoint2off viewpoint2off.o $(LDFLAGS)

clean:
	rm -f *.o \
                   geomview_demo \
                   viewpoint2off \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

