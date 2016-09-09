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
                polyhedron_prog_incr_builder \
                polyhedron_prog_normals \
                polyhedron_prog_off \
                polyhedron_prog_point_iterator \
                polyhedron_prog_simple \
                polyhedron_prog_tetra 

polyhedron_prog_incr_builder: polyhedron_prog_incr_builder.o
	$(CGAL_CXX) -o polyhedron_prog_incr_builder polyhedron_prog_incr_builder.o $(LDFLAGS)

polyhedron_prog_normals: polyhedron_prog_normals.o
	$(CGAL_CXX) -o polyhedron_prog_normals polyhedron_prog_normals.o $(LDFLAGS)

polyhedron_prog_off: polyhedron_prog_off.o
	$(CGAL_CXX) -o polyhedron_prog_off polyhedron_prog_off.o $(LDFLAGS)

polyhedron_prog_point_iterator: polyhedron_prog_point_iterator.o
	$(CGAL_CXX) -o polyhedron_prog_point_iterator polyhedron_prog_point_iterator.o $(LDFLAGS)

polyhedron_prog_simple: polyhedron_prog_simple.o
	$(CGAL_CXX) -o polyhedron_prog_simple polyhedron_prog_simple.o $(LDFLAGS)

polyhedron_prog_tetra: polyhedron_prog_tetra.o
	$(CGAL_CXX) -o polyhedron_prog_tetra polyhedron_prog_tetra.o $(LDFLAGS)

clean:
	rm -f *.o \
                   polyhedron_prog_incr_builder \
                   polyhedron_prog_normals \
                   polyhedron_prog_off \
                   polyhedron_prog_point_iterator \
                   polyhedron_prog_simple \
                   polyhedron_prog_tetra \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

