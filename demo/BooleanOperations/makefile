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
           -I./include \
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
                BooleanOperations_demo \
                Howto_Intersection_demo \
                b-ops-2D-example-1 \
                test_bops \
                test_bops_V2E \
                test_bops_cin \
                test_bops_cin_wout \
                test_bops_wout \
                test_float_bops_cin \
                test_float_bops_cin_wout \
                test_float_bops_wout \
                test_min_sqr \
                tutorial_example 

BooleanOperations_demo: BooleanOperations_demo.o
	$(CGAL_CXX) -o BooleanOperations_demo BooleanOperations_demo.o $(LDFLAGS)

Howto_Intersection_demo: Howto_Intersection_demo.o
	$(CGAL_CXX) -o Howto_Intersection_demo Howto_Intersection_demo.o $(LDFLAGS)

b-ops-2D-example-1: b-ops-2D-example-1.o
	$(CGAL_CXX) -o b-ops-2D-example-1 b-ops-2D-example-1.o $(LDFLAGS)

test_bops: test_bops.o
	$(CGAL_CXX) -o test_bops test_bops.o $(LDFLAGS)

test_bops_V2E: test_bops_V2E.o
	$(CGAL_CXX) -o test_bops_V2E test_bops_V2E.o $(LDFLAGS)

test_bops_cin: test_bops_cin.o
	$(CGAL_CXX) -o test_bops_cin test_bops_cin.o $(LDFLAGS)

test_bops_cin_wout: test_bops_cin_wout.o
	$(CGAL_CXX) -o test_bops_cin_wout test_bops_cin_wout.o $(LDFLAGS)

test_bops_wout: test_bops_wout.o
	$(CGAL_CXX) -o test_bops_wout test_bops_wout.o $(LDFLAGS)

test_float_bops_cin: test_float_bops_cin.o
	$(CGAL_CXX) -o test_float_bops_cin test_float_bops_cin.o $(LDFLAGS)

test_float_bops_cin_wout: test_float_bops_cin_wout.o
	$(CGAL_CXX) -o test_float_bops_cin_wout test_float_bops_cin_wout.o $(LDFLAGS)

test_float_bops_wout: test_float_bops_wout.o
	$(CGAL_CXX) -o test_float_bops_wout test_float_bops_wout.o $(LDFLAGS)

test_min_sqr: test_min_sqr.o
	$(CGAL_CXX) -o test_min_sqr test_min_sqr.o $(LDFLAGS)

tutorial_example: tutorial_example.o
	$(CGAL_CXX) -o tutorial_example tutorial_example.o $(LDFLAGS)

clean:
	/bin/rm -f *.o \
                   BooleanOperations_demo \
                   Howto_Intersection_demo \
                   b-ops-2D-example-1 \
                   test_bops \
                   test_bops_V2E \
                   test_bops_cin \
                   test_bops_cin_wout \
                   test_bops_wout \
                   test_float_bops_cin \
                   test_float_bops_cin_wout \
                   test_float_bops_wout \
                   test_min_sqr \
                   tutorial_example \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

