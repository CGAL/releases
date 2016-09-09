# This is the makefile for compiling a CGAL application.
# Modified by Herve Bronnimann for compiling .C instead of .cpp

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

# CGAL_MAKEFILE = ENTER_YOUR_INCLUDE_MAKEFILE_HERE

include $(CGAL_MAKEFILE)

#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CXXFLAGS = $(CGAL_CXXFLAGS) \
	   -I../../include/ \

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = -lP -lX11 -lL -lG -lW $(CGAL_LDFLAGS) $(CGAL_WINDOW_LDFLAGS)

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#

demo: demo.o  draw_map.o 
	$(CGAL_CXX) -o demo demo.o draw_map.o $(LDFLAGS)

helputil: helputil.o  
	$(CGAL_CXX) -o helputil helputil.o $(LDFLAGS)

all:            \
                demo \
                helputil 

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o
	rm -f demo	
	rm -f helputil
	rm -f ii_files/*











