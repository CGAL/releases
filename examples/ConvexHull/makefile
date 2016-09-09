# This is the makefile for compiling the CGAL Kernel test.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

CGAL_MAKEFILE = 
include $(CGAL_MAKEFILE)

#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CXXFLAGS = \
           $(TESTSUITE_CXXFLAGS) \
           -I./include \
           $(CGAL_CXXFLAGS) \
           $(EXTRA_FLAGS) 

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
                ch_example_from_cin_to_cout \
                ch_example_timing

ch_example_from_cin_to_cout: ch_example_from_cin_to_cout.o
	$(CGAL_CXX) -o ch_example_from_cin_to_cout ch_example_from_cin_to_cout.o $(LDFLAGS)

ch_example_timing: ch_example_timing.o
	$(CGAL_CXX) -o ch_example_timing ch_example_timing.o $(LDFLAGS)

clean:
	/bin/rm -f ch_example_from_cin_to_cout ch_example_from_cin_to_cout.o
	/bin/rm -f ch_example_timing ch_example_timing.o

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

