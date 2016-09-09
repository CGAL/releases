# This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

CGAL_MAKEFILE = ENTER_YOUR_INCLUDE_MAKEFILE_HERE
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

advanced_hull: advanced_hull.o
	$(CGAL_CXX) -o advanced_hull advanced_hull.o $(LDFLAGS)

avh2: avh2.o
	$(CGAL_CXX) -o avh2 avh2.o $(LDFLAGS)

basic: basic.o
	$(CGAL_CXX) -o basic basic.o $(LDFLAGS)

basic_io: basic_io.o
	$(CGAL_CXX) -o basic_io basic_io.o $(LDFLAGS)

centre_of_mass: centre_of_mass.o
	$(CGAL_CXX) -o centre_of_mass centre_of_mass.o $(LDFLAGS)

convex_hull: convex_hull.o
	$(CGAL_CXX) -o convex_hull convex_hull.o $(LDFLAGS)

copyex: copyex.o
	$(CGAL_CXX) -o copyex copyex.o $(LDFLAGS)

exact_orientation: exact_orientation.o
	$(CGAL_CXX) -o exact_orientation exact_orientation.o $(LDFLAGS)

exact_orientation_gmpz: exact_orientation_gmpz.o
	$(CGAL_CXX) -o exact_orientation_gmpz exact_orientation_gmpz.o $(LDFLAGS)

file_io: file_io.o
	$(CGAL_CXX) -o file_io file_io.o $(LDFLAGS)

incircle: incircle.o
	$(CGAL_CXX) -o incircle incircle.o $(LDFLAGS)

listmanip: listmanip.o
	$(CGAL_CXX) -o listmanip listmanip.o $(LDFLAGS)

orientation: orientation.o
	$(CGAL_CXX) -o orientation orientation.o $(LDFLAGS)

templ_centre_of_mass: templ_centre_of_mass.o
	$(CGAL_CXX) -o templ_centre_of_mass templ_centre_of_mass.o $(LDFLAGS)

triangulation1: triangulation1.o
	$(CGAL_CXX) -o triangulation1 triangulation1.o $(LDFLAGS)

triangulation2: triangulation2.o
	$(CGAL_CXX) -o triangulation2 triangulation2.o $(LDFLAGS)

vectorex: vectorex.o
	$(CGAL_CXX) -o vectorex vectorex.o $(LDFLAGS)

vectorex1: vectorex1.o
	$(CGAL_CXX) -o vectorex1 vectorex1.o $(LDFLAGS)

clean:
	/bin/rm -f  advanced_hull avh2 basic basic_io centre_of_mass convex_hull copyex exact_orientation exact_orientation_gmpz file_io incircle listmanip orientation templ_centre_of_mass templ_stack triangulation1 triangulation2 vectorex vectorex1 *.o core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<
