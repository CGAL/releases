# This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

CGAL_MAKEFILE = /KM/projects/CGAL/make/makefile_sparc_SunOS-5.5.1_g++-2.7.2_rtti_LEDA_351
include $(CGAL_MAKEFILE)

#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CPPFLAGS = $(CGAL_CPPFLAGS) \
           -g

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = $(CGAL_LDFLAGS)

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#

Points: Points.o
	$(CC) -o Points Points.o $(LDFLAGS)

Points3D: Points3D.o
	$(CC) -o Points3D Points3D.o $(LDFLAGS)

demo: demo.o
	$(CC) -o demo demo.o $(CGAL_WINDOW_LDFLAGS)

example: example.o
	$(CC) -o example example.o $(LDFLAGS)

parse: parse.o
	$(CC) -o parse parse.o $(LDFLAGS)

clean:
	/bin/rm  Points Points3D demo example parse *.o core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CC) $(CPPFLAGS) -c $<
