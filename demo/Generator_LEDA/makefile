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
           $(LONG_NAME_PROBLEM_CXXFLAGS) \
           $(CGAL_CXXFLAGS) \
           -g

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = \
          $(LONG_NAME_PROBLEM_LDFLAGS) \
          $(CGAL_WINDOW_LDFLAGS)

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#

all:            \
                Segment_generator_prog1 \
                Segment_generator_prog2 \
                Triangle_generator_prog1 \
                Triangle_generator_prog2 \
                generators_prog1 \
                generators_prog2 \
                rcs_demo 

Segment_generator_prog1: Segment_generator_prog1.o
	$(CGAL_CXX) -o Segment_generator_prog1 Segment_generator_prog1.o $(LDFLAGS)

Segment_generator_prog2: Segment_generator_prog2.o
	$(CGAL_CXX) -o Segment_generator_prog2 Segment_generator_prog2.o $(LDFLAGS)

Triangle_generator_prog1: Triangle_generator_prog1.o
	$(CGAL_CXX) -o Triangle_generator_prog1 Triangle_generator_prog1.o $(LDFLAGS)

Triangle_generator_prog2: Triangle_generator_prog2.o
	$(CGAL_CXX) -o Triangle_generator_prog2 Triangle_generator_prog2.o $(LDFLAGS)

generators_prog1: generators_prog1.o
	$(CGAL_CXX) -o generators_prog1 generators_prog1.o $(LDFLAGS)

generators_prog2: generators_prog2.o
	$(CGAL_CXX) -o generators_prog2 generators_prog2.o $(LDFLAGS)

rcs_demo: rcs_demo.o
	$(CGAL_CXX) -o rcs_demo rcs_demo.o $(LDFLAGS)

clean:
	rm -f *.o \
                   Segment_generator_prog1 \
                   Segment_generator_prog2 \
                   Triangle_generator_prog1 \
                   Triangle_generator_prog2 \
                   generators_prog1 \
                   generators_prog2 \
                   rcs_demo \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

