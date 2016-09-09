# This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

#CGAL_MAKEFILE = /u/alcor/0/prisme_util/CGAL/CGAL-1.2-I-13/make/makefile_sparc_SunOS-5.6_eg++-egcs-2.91.57_LEDA
include $(CGAL_MAKEFILE)


#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CXXFLAGS = -I../../include  $(CGAL_CXXFLAGS) $(TESTSUITE_CXXFLAGS) 
           

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = $(CGAL_LDFLAGS) $(TESTSUITE_LDFLAGS)

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
	rm -rf *~ *.o core tr

realclean: clean
	rm -rf points example voronoi Program* Compiler* Error* error.txt

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<
