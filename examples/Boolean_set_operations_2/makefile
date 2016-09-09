# Created by the script cgal_create_makefile
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
                ex_circle_segment$(EXE_EXT) \
                ex_do_intersect$(EXE_EXT) \
                ex_dxf_union$(EXE_EXT) \
                ex_sequence$(EXE_EXT) \
                ex_set_union$(EXE_EXT) \
                ex_simple_join_intersect$(EXE_EXT) \
                ex_symmetric_difference$(EXE_EXT) \
                ex_traits_adapter$(EXE_EXT) 

ex_circle_segment$(EXE_EXT): ex_circle_segment$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_circle_segment ex_circle_segment$(OBJ_EXT) $(LDFLAGS)

ex_do_intersect$(EXE_EXT): ex_do_intersect$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_do_intersect ex_do_intersect$(OBJ_EXT) $(LDFLAGS)

ex_dxf_union$(EXE_EXT): ex_dxf_union$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_dxf_union ex_dxf_union$(OBJ_EXT) $(LDFLAGS)

ex_sequence$(EXE_EXT): ex_sequence$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_sequence ex_sequence$(OBJ_EXT) $(LDFLAGS)

ex_set_union$(EXE_EXT): ex_set_union$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_set_union ex_set_union$(OBJ_EXT) $(LDFLAGS)

ex_simple_join_intersect$(EXE_EXT): ex_simple_join_intersect$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_simple_join_intersect ex_simple_join_intersect$(OBJ_EXT) $(LDFLAGS)

ex_symmetric_difference$(EXE_EXT): ex_symmetric_difference$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_symmetric_difference ex_symmetric_difference$(OBJ_EXT) $(LDFLAGS)

ex_traits_adapter$(EXE_EXT): ex_traits_adapter$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_traits_adapter ex_traits_adapter$(OBJ_EXT) $(LDFLAGS)

clean: \
                   ex_circle_segment.clean \
                   ex_do_intersect.clean \
                   ex_dxf_union.clean \
                   ex_sequence.clean \
                   ex_set_union.clean \
                   ex_simple_join_intersect.clean \
                   ex_symmetric_difference.clean \
                   ex_traits_adapter.clean 

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C$(OBJ_EXT):
	$(CGAL_CXX) $(CXXFLAGS) $(OBJ_OPT) $<


.cpp$(OBJ_EXT):
	$(CGAL_CXX) $(CXXFLAGS) $(OBJ_OPT) $<

