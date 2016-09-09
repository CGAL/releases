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
                advanced_hull \
                advanced_hull_2 \
                basic \
                basic_io \
                boundingbox \
                centre_of_mass \
                circulate \
                convex_hull \
                copyex \
                exact_orientation \
                exact_orientation_gmpz \
                file_io \
                incircle \
                inters_check \
                inters_comp \
                listmanip \
                orientation \
                polygon_centre \
                polygon_match \
                templ_centre_of_mass \
                triangulation1 \
                triangulation2 \
                vectorex \
                vectorex1 

advanced_hull: advanced_hull.o
	$(CGAL_CXX) -o advanced_hull advanced_hull.o $(LDFLAGS)

advanced_hull_2: advanced_hull_2.o
	$(CGAL_CXX) -o advanced_hull_2 advanced_hull_2.o $(LDFLAGS)

basic: basic.o
	$(CGAL_CXX) -o basic basic.o $(LDFLAGS)

basic_io: basic_io.o
	$(CGAL_CXX) -o basic_io basic_io.o $(LDFLAGS)

boundingbox: boundingbox.o
	$(CGAL_CXX) -o boundingbox boundingbox.o $(LDFLAGS)

centre_of_mass: centre_of_mass.o
	$(CGAL_CXX) -o centre_of_mass centre_of_mass.o $(LDFLAGS)

circulate: circulate.o
	$(CGAL_CXX) -o circulate circulate.o $(LDFLAGS)

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

inters_check: inters_check.o
	$(CGAL_CXX) -o inters_check inters_check.o $(LDFLAGS)

inters_comp: inters_comp.o
	$(CGAL_CXX) -o inters_comp inters_comp.o $(LDFLAGS)

listmanip: listmanip.o
	$(CGAL_CXX) -o listmanip listmanip.o $(LDFLAGS)

orientation: orientation.o
	$(CGAL_CXX) -o orientation orientation.o $(LDFLAGS)

polygon_centre: polygon_centre.o
	$(CGAL_CXX) -o polygon_centre polygon_centre.o $(LDFLAGS)

polygon_match: polygon_match.o
	$(CGAL_CXX) -o polygon_match polygon_match.o $(LDFLAGS)

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
	rm -f *.o \
                   advanced_hull \
                   advanced_hull_2 \
                   basic \
                   basic_io \
                   boundingbox \
                   centre_of_mass \
                   circulate \
                   convex_hull \
                   copyex \
                   exact_orientation \
                   exact_orientation_gmpz \
                   file_io \
                   incircle \
                   inters_check \
                   inters_comp \
                   listmanip \
                   orientation \
                   polygon_centre \
                   polygon_match \
                   templ_centre_of_mass \
                   triangulation1 \
                   triangulation2 \
                   vectorex \
                   vectorex1 \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

