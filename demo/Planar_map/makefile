# This is the makefile for compiling a CGAL application.
# Modified by Herve Bronnimann for compiling .C instead of .cpp

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

#CGAL_MAKEFILE = ENTER_YOUR_INCLUDE_MAKEFILE_HERE
include $(CGAL_MAKEFILE)

#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CXXFLAGS = -I../../include/ \
	$(CGAL_CXXFLAGS) \
	$(TEST_SUITE_FLAGS)


#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = -lP -lX11 -lL -lG -lW $(CGAL_LDFLAGS) $(CGAL_WINDOW_LDFLAGS)

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#

demo: demo.o draw_map.o 
	$(CGAL_CXX) $(CXXFLAGS) -o demo demo.o draw_map.o $(LDFLAGS)

helputil: helputil.o  
	$(CGAL_CXX) $(CXXFLAGS) -o helputil helputil.o $(LDFLAGS)



demo.all:       demo.default.float \
		demo.default.rational \
		demo.naive.float \
		demo.naive.rational

demo.default.float: demo.default.float.o draw_map.default.float.o 
	$(CGAL_CXX) $(CXXFLAGS) -o demo.default.float demo.default.float.o draw_map.default.float.o $(LDFLAGS)

demo.default.rational: demo.default.rational.o draw_map.default.rational.o 
	$(CGAL_CXX) $(CXXFLAGS) -o demo.default.rational demo.default.rational.o draw_map.default.rational.o $(LDFLAGS)

demo.naive.float: demo.naive.float.o draw_map.naive.float.o 
	$(CGAL_CXX) $(CXXFLAGS) -o demo.naive.float demo.naive.float.o draw_map.naive.float.o $(LDFLAGS)

demo.naive.rational: demo.naive.rational.o draw_map.naive.rational.o 
	$(CGAL_CXX) $(CXXFLAGS) -o demo.naive.rational demo.naive.rational.o draw_map.naive.rational.o $(LDFLAGS)

demo.default.rational.o: demo.C draw_map.h
	$(CGAL_CXX) $(CXXFLAGS) -DUSE_RATIONAL -o demo.default.rational.o -c demo.C 

demo.naive.float.o: demo.C draw_map.h
	$(CGAL_CXX) $(CXXFLAGS) -DUSE_NAIVE_POINT_LOCATION -o demo.naive.float.o -c demo.C

demo.naive.rational.o: demo.C draw_map.h
	$(CGAL_CXX) $(CXXFLAGS) -DUSE_NAIVE_POINT_LOCATION -DUSE_RATIONAL -o demo.naive.rational.o -c demo.C

draw_map.default.float.o: draw_map.C draw_map.h
	$(CGAL_CXX) $(CXXFLAGS) -o draw_map.default.float.o -c draw_map.C

draw_map.default.rational.o: draw_map.C draw_map.h
	$(CGAL_CXX) $(CXXFLAGS) -DUSE_RATIONAL -o draw_map.default.rational.o -c draw_map.C 

draw_map.naive.float.o: draw_map.C draw_map.h
	$(CGAL_CXX) $(CXXFLAGS) -DUSE_NAIVE_POINT_LOCATION -o draw_map.naive.float.o -c draw_map.C

draw_map.naive.rational.o: draw_map.C draw_map.h
	$(CGAL_CXX) $(CXXFLAGS) -DUSE_NAIVE_POINT_LOCATION -DUSE_RATIONAL -o draw_map.naive.rational.o -c draw_map.C

all:		demo \
                helputil

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o
	rm -f demo
	rm -f demo.default.float
	rm -f demo.default.rational
	rm -f demo.naive.float
	rm -f demo.naive.rational
	rm -f helputil
	rm -f ii_files/*
	rm -f core











