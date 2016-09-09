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
           $(CGAL_CXXFLAGS) \
           -g

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = \
          $(CGAL_WINDOW_LDFLAGS)

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#

all:            \
                convex_hull \
                convex_hull_LEDA 

convex_hull: convex_hull.o
	$(CGAL_CXX) -o convex_hull convex_hull.o $(LDFLAGS)

convex_hull_LEDA: convex_hull_LEDA.o
	$(CGAL_CXX) -o convex_hull_LEDA convex_hull_LEDA.o $(LDFLAGS)

clean:
	/bin/rm -f *.o \
                   convex_hull \
                   convex_hull_LEDA \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

