# Created by the script create_makefile
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
           -I../../include \
           $(CGAL_CXXFLAGS) \
           $(LONG_NAME_PROBLEM_CXXFLAGS)

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LIBPATH = \
          $(CGAL_LIBPATH)

LDFLAGS = \
          $(LONG_NAME_PROBLEM_LDFLAGS) \
          $(CGAL_LDFLAGS)

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#

all:            \
                svd-count-sites$(EXE_EXT) \
                svd-filtered-traits$(EXE_EXT) \
                svd-voronoi-edges$(EXE_EXT) 

svd-count-sites$(EXE_EXT): svd-count-sites$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)svd-count-sites svd-count-sites$(OBJ_EXT) $(LDFLAGS)

svd-filtered-traits$(EXE_EXT): svd-filtered-traits$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)svd-filtered-traits svd-filtered-traits$(OBJ_EXT) $(LDFLAGS)

svd-voronoi-edges$(EXE_EXT): svd-voronoi-edges$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)svd-voronoi-edges svd-voronoi-edges$(OBJ_EXT) $(LDFLAGS)

clean: \
                   svd-count-sites.clean \
                   svd-filtered-traits.clean \
                   svd-voronoi-edges.clean 

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C$(OBJ_EXT):
	$(CGAL_CXX) $(CXXFLAGS) $(OBJ_OPT) $<

