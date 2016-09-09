# This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

include $(CGAL_MAKEFILE)

CXX = g++


#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CXXFLAGS = -I../../include -I$(LOCAL)/C2/include $(CGAL_CXXFLAGS) -DDELAUNAY
           

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
	rm -rf *~ *.o core tr

realclean: clean
	rm -rf points example voronoi Program* Compiler* Error* error.txt

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<
