# This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

#CGAL_MAKEFILE = /KM/projects/CGAL/make/makefile_sparc_SunOS-5.5.1_CC-4.1
#CGAL_MAKEFILE = /KM/projects/CGAL/make/makefile_sparc_SunOS-5.5.1_CC-4.1_L
#CGAL_MAKEFILE = /KM/projects/CGAL/make/makefile_sparc_SunOS-5.5.1_CC-4.1_LEDA
#CGAL_MAKEFILE = /KM/projects/CGAL/make/makefile_sparc_SunOS-5.5.1_CC-4.1_L_TDB
#CGAL_MAKEFILE = /KM/projects/CGAL/make/makefile_sparc_SunOS-5.5.1_g++-2.7.2_rtti_L
#CGAL_MAKEFILE = /KM/projects/CGAL/make/makefile_sparc_SunOS-5.5.1_g++-2.7.2_rtti_LEDA
CGAL_MAKEFILE = /KM/projects/ledares/CGAL/make/makefile_sparc_SunOS-5.5.1_CC-4.1_LEDA

include $(CGAL_MAKEFILE)

#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CXXFLAGS = $(CGAL_CXXFLAGS) \
           -g

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = $(CGAL_LDFLAGS)

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#

Segment_generator_example1: Segment_generator_example1.o
	$(CGAL_CXX) -o Segment_generator_example1 Segment_generator_example1.o $(LDFLAGS)

Segment_generator_example2: Segment_generator_example2.o
	$(CGAL_CXX) -o Segment_generator_example2 Segment_generator_example2.o $(LDFLAGS)

circulator_prog1: circulator_prog1.o
	$(CGAL_CXX) -o circulator_prog1 circulator_prog1.o $(LDFLAGS)

circulator_prog2: circulator_prog2.o
	$(CGAL_CXX) -o circulator_prog2 circulator_prog2.o $(LDFLAGS)

circulator_prog3: circulator_prog3.o
	$(CGAL_CXX) -o circulator_prog3 circulator_prog3.o $(LDFLAGS)

example1_Min_circle_2: example1_Min_circle_2.o
	$(CGAL_CXX) -o example1_Min_circle_2 example1_Min_circle_2.o $(LDFLAGS)

example2_Min_circle_2: example2_Min_circle_2.o
	$(CGAL_CXX) -o example2_Min_circle_2 example2_Min_circle_2.o $(LDFLAGS)

example3_Min_circle_2: example3_Min_circle_2.o
	$(CGAL_CXX) -o example3_Min_circle_2 example3_Min_circle_2.o $(LDFLAGS)

generators_example1: generators_example1.o
	$(CGAL_CXX) -o generators_example1 generators_example1.o $(LDFLAGS)

generators_example2: generators_example2.o
	$(CGAL_CXX) -o generators_example2 generators_example2.o $(LDFLAGS)

clean:
	/bin/rm -f  Segment_generator_example1 Segment_generator_example2 circulator_prog1 circulator_prog2 circulator_prog3 example1_Min_circle_2 example2_Min_circle_2 example3_Min_circle_2 generators_example1 generators_example2 *.o core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<
