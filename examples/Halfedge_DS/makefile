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
                hds_prog_color \
                hds_prog_compact \
                hds_prog_compact2 \
                hds_prog_default \
                hds_prog_graph \
                hds_prog_graph2 \
                hds_prog_halfedge_iterator \
                hds_prog_vector 

hds_prog_color: hds_prog_color.o
	$(CGAL_CXX) -o hds_prog_color hds_prog_color.o $(LDFLAGS)

hds_prog_compact: hds_prog_compact.o
	$(CGAL_CXX) -o hds_prog_compact hds_prog_compact.o $(LDFLAGS)

hds_prog_compact2: hds_prog_compact2.o
	$(CGAL_CXX) -o hds_prog_compact2 hds_prog_compact2.o $(LDFLAGS)

hds_prog_default: hds_prog_default.o
	$(CGAL_CXX) -o hds_prog_default hds_prog_default.o $(LDFLAGS)

hds_prog_graph: hds_prog_graph.o
	$(CGAL_CXX) -o hds_prog_graph hds_prog_graph.o $(LDFLAGS)

hds_prog_graph2: hds_prog_graph2.o
	$(CGAL_CXX) -o hds_prog_graph2 hds_prog_graph2.o $(LDFLAGS)

hds_prog_halfedge_iterator: hds_prog_halfedge_iterator.o
	$(CGAL_CXX) -o hds_prog_halfedge_iterator hds_prog_halfedge_iterator.o $(LDFLAGS)

hds_prog_vector: hds_prog_vector.o
	$(CGAL_CXX) -o hds_prog_vector hds_prog_vector.o $(LDFLAGS)

clean:
	rm -f *.o \
                   hds_prog_color \
                   hds_prog_compact \
                   hds_prog_compact2 \
                   hds_prog_default \
                   hds_prog_graph \
                   hds_prog_graph2 \
                   hds_prog_halfedge_iterator \
                   hds_prog_vector \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

