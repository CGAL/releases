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
                circulator_prog1 \
                circulator_prog2 \
                circulator_prog3 

circulator_prog1: circulator_prog1.o
	$(CGAL_CXX) -o circulator_prog1 circulator_prog1.o $(LDFLAGS)

circulator_prog2: circulator_prog2.o
	$(CGAL_CXX) -o circulator_prog2 circulator_prog2.o $(LDFLAGS)

circulator_prog3: circulator_prog3.o
	$(CGAL_CXX) -o circulator_prog3 circulator_prog3.o $(LDFLAGS)

clean:
	rm -f *.o \
                   circulator_prog1 \
                   circulator_prog2 \
                   circulator_prog3 \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

