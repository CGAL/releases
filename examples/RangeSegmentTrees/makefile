# This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.
PUBLIC = #/net/blabla/export/raid/project/local
CGAL_MAKEFILE = #$(PUBLIC)/src/geometric/CGAL/CGAL-0.9-I-08/make/makefile_mips_IRIX64-6.2_g++-egcs-2.90.27_LEDA

include $(CGAL_MAKEFILE)

#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CXXFLAGS = \
           $(TESTSUITE_CXXFLAGS) \
           -I./include \
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
                range_tree_1 \
                range_tree_2 \
                range_tree_3 \
                range_tree_4 \
                range_tree_map_2 \
                range_tree_set_2 \
                segment_tree_1 \
                segment_tree_2 \
                segment_tree_3 \
                segment_tree_4 \
                segment_tree_map_2 \
                segment_tree_set_2 \
                segment_tree_set_3 


range_tree_1: range_tree_1.o
	$(CGAL_CXX) -o range_tree_1 range_tree_1.o $(LDFLAGS)

range_tree_2: range_tree_2.o
	$(CGAL_CXX) -o range_tree_2 range_tree_2.o $(LDFLAGS)

range_tree_3: range_tree_3.o
	$(CGAL_CXX) -o range_tree_3 range_tree_3.o $(LDFLAGS)

range_tree_4: range_tree_4.o
	$(CGAL_CXX) -o range_tree_4 range_tree_4.o $(LDFLAGS)

range_tree_map_2: range_tree_map_2.o
	$(CGAL_CXX) -o range_tree_map_2 range_tree_map_2.o $(LDFLAGS)

range_tree_set_2: range_tree_set_2.o
	$(CGAL_CXX) -o range_tree_set_2 range_tree_set_2.o $(LDFLAGS)

segment_tree_1: segment_tree_1.o
	$(CGAL_CXX) -o segment_tree_1 segment_tree_1.o $(LDFLAGS)

segment_tree_2: segment_tree_2.o
	$(CGAL_CXX) -o segment_tree_2 segment_tree_2.o $(LDFLAGS)

segment_tree_3: segment_tree_3.o
	$(CGAL_CXX) -o segment_tree_3 segment_tree_3.o $(LDFLAGS)

segment_tree_4: segment_tree_4.o
	$(CGAL_CXX) -o segment_tree_4 segment_tree_4.o $(LDFLAGS)

segment_tree_map_2: segment_tree_map_2.o
	$(CGAL_CXX) -o segment_tree_map_2 segment_tree_map_2.o $(LDFLAGS)

segment_tree_set_2: segment_tree_set_2.o
	$(CGAL_CXX) -o segment_tree_set_2 segment_tree_set_2.o $(LDFLAGS)

segment_tree_set_3: segment_tree_set_3.o
	$(CGAL_CXX) -o segment_tree_set_3 segment_tree_set_3.o $(LDFLAGS)

segment_tree_12: segment_tree_12.o
	$(CGAL_CXX) -o segment_tree_12 segment_tree_12.o $(LDFLAGS)

clean:
	/bin/rm -f *.o \
                   range_tree_1 \
                   range_tree_2 \
                   range_tree_3 \
                   range_tree_4 \
                   range_tree_map_2 \
                   range_tree_set_2 \
                   segment_tree_1 \
                   segment_tree_2 \
                   segment_tree_3 \
                   segment_tree_4 \
                   segment_tree_map_2 \
                   segment_tree_set_2 \
                   segment_tree_set_3 \
                   core

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CXXFLAGS) -c $<






