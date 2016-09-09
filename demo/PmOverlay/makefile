# This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Put here the right CGAL makefile
#CGAL_MAKEFILE = 
include $(CGAL_MAKEFILE)

#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CXXFLAGS = \
           $(TESTSUITE_CXXFLAGS) \
           $(CGAL_CXXFLAGS) \
           -g  
#-fguiding-decls

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
                ovl_homo_double \
                ovl_homo_gmpz 

ovl_homo_double: ovl_homo_double.o
	$(CGAL_CXX) -o ovl_homo_double ovl_homo_double.o $(LDFLAGS)

ovl_homo_gmpz: ovl_homo_gmpz.o
	$(CGAL_CXX) -o ovl_homo_gmpz ovl_homo_gmpz.o $(LDFLAGS)

clean:
	/bin/rm -f *.o \
                   ovl_homo_double \
                   ovl_homo_gmpz \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

