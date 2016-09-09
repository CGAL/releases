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
                iv2off \
                off2iv \
                off2off \
                off2vrml \
                off2wav \
                off_bbox \
                off_glue \
                off_transform \
                polyhedron_copy \
                terr_trian 

iv2off: iv2off.o
	$(CGAL_CXX) -o iv2off iv2off.o $(LDFLAGS)

off2iv: off2iv.o
	$(CGAL_CXX) -o off2iv off2iv.o $(LDFLAGS)

off2off: off2off.o
	$(CGAL_CXX) -o off2off off2off.o $(LDFLAGS)

off2vrml: off2vrml.o
	$(CGAL_CXX) -o off2vrml off2vrml.o $(LDFLAGS)

off2wav: off2wav.o
	$(CGAL_CXX) -o off2wav off2wav.o $(LDFLAGS)

off_bbox: off_bbox.o
	$(CGAL_CXX) -o off_bbox off_bbox.o $(LDFLAGS)

off_glue: off_glue.o
	$(CGAL_CXX) -o off_glue off_glue.o $(LDFLAGS)

off_transform: off_transform.o
	$(CGAL_CXX) -o off_transform off_transform.o $(LDFLAGS)

polyhedron_copy: polyhedron_copy.o
	$(CGAL_CXX) -o polyhedron_copy polyhedron_copy.o $(LDFLAGS)

terr_trian: terr_trian.o
	$(CGAL_CXX) -o terr_trian terr_trian.o $(LDFLAGS)

clean:
	rm -f *.o \
                   iv2off \
                   off2iv \
                   off2off \
                   off2vrml \
                   off2wav \
                   off_bbox \
                   off_glue \
                   off_transform \
                   polyhedron_copy \
                   terr_trian \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

