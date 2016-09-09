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
                data_to_mps$(EXE_EXT) \
                double_qp_solver$(EXE_EXT) \
                integer_qp_solver$(EXE_EXT) \
                qp_solver1$(EXE_EXT) \
                qp_solver2$(EXE_EXT) \
                rational_qp_solver$(EXE_EXT) 

data_to_mps$(EXE_EXT): data_to_mps$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)data_to_mps data_to_mps$(OBJ_EXT) $(LDFLAGS)

double_qp_solver$(EXE_EXT): double_qp_solver$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)double_qp_solver double_qp_solver$(OBJ_EXT) $(LDFLAGS)

integer_qp_solver$(EXE_EXT): integer_qp_solver$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)integer_qp_solver integer_qp_solver$(OBJ_EXT) $(LDFLAGS)

qp_solver1$(EXE_EXT): qp_solver1$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)qp_solver1 qp_solver1$(OBJ_EXT) $(LDFLAGS)

qp_solver2$(EXE_EXT): qp_solver2$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)qp_solver2 qp_solver2$(OBJ_EXT) $(LDFLAGS)

rational_qp_solver$(EXE_EXT): rational_qp_solver$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)rational_qp_solver rational_qp_solver$(OBJ_EXT) $(LDFLAGS)

clean: \
                   data_to_mps.clean \
                   double_qp_solver.clean \
                   integer_qp_solver.clean \
                   qp_solver1.clean \
                   qp_solver2.clean \
                   rational_qp_solver.clean 

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C$(OBJ_EXT):
	$(CGAL_CXX) $(CXXFLAGS) $(OBJ_OPT) $<


.cpp$(OBJ_EXT):
	$(CGAL_CXX) $(CXXFLAGS) $(OBJ_OPT) $<

