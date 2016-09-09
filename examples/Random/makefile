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
                Segment_generator_example1 \
                Segment_generator_example2 \
                generators_example1 \
                generators_example2 

Segment_generator_example1: Segment_generator_example1.o
	$(CGAL_CXX) -o Segment_generator_example1 Segment_generator_example1.o $(LDFLAGS)

Segment_generator_example2: Segment_generator_example2.o
	$(CGAL_CXX) -o Segment_generator_example2 Segment_generator_example2.o $(LDFLAGS)

generators_example1: generators_example1.o
	$(CGAL_CXX) -o generators_example1 generators_example1.o $(LDFLAGS)

generators_example2: generators_example2.o
	$(CGAL_CXX) -o generators_example2 generators_example2.o $(LDFLAGS)

clean:
	rm -f *.o \
                   Segment_generator_example1 \
                   Segment_generator_example2 \
                   generators_example1 \
                   generators_example2 \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

