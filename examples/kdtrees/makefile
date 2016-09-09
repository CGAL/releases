# This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

#CGAL_MAKEFILE = ENTER_YOUR_INCLUDE_MAKEFILE_HERE

include $(CGAL_MAKEFILE)

#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

TESTSUITE_CXXFLAGS =

CXXFLAGS = -I../../include\
           $(TESTSUITE_CXXFLAGS) \
	   $(EXTRA_FLAGS) \
           $(CGAL_CXXFLAGS) \
	   $(LONG_NAME_PROBLEM_CXXFLAGS)

#long names flag for Sun+egcs platform

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = \
          $(TESTSUITE_LDFLAGS) \
          $(CGAL_LDFLAGS) \
	  $(LONG_NAME_PROBLEM_LDFLAGS)

#long names flag for Sun+egcs platform

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#

all:            \
                example1 \
                example2 \
                example3
#                example4 \
#		example5 \
#		example6


example1: example1.o
	$(CGAL_CXX) -o example1 example1.o $(LDFLAGS)

example2: example2.o
	$(CGAL_CXX) -o example2 example2.o $(LDFLAGS)

example3: example3.o
	$(CGAL_CXX) -o example3 example3.o $(LDFLAGS)

#example4: example4.o
#	$(CGAL_CXX) -o example4 example4.o $(LDFLAGS)

#example5: example5.o
#	$(CGAL_CXX) -o example5 example5.o $(LDFLAGS)

#example6: example6.o
#	$(CGAL_CXX) -o example6 example6.o $(LDFLAGS)

clean:
	/bin/rm -f -r *.o \
	 	   ii_files \
                   example1 \
                   example2 \
                   example3 \
                   example4 \
		   example5 \
		   example6 \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<









