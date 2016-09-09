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
                ex_aggregated_insertion$(EXE_EXT) \
                ex_batched_point_location$(EXE_EXT) \
                ex_bgl_dual_adapter$(EXE_EXT) \
                ex_bgl_primal_adapter$(EXE_EXT) \
                ex_circles$(EXE_EXT) \
                ex_circular_arcs$(EXE_EXT) \
                ex_conic_multiplicities$(EXE_EXT) \
                ex_conics$(EXE_EXT) \
                ex_consolidated_curve_data$(EXE_EXT) \
                ex_curve_history$(EXE_EXT) \
                ex_dcel_extension$(EXE_EXT) \
                ex_dcel_extension_io$(EXE_EXT) \
                ex_edge_insertion$(EXE_EXT) \
                ex_edge_manipulation$(EXE_EXT) \
                ex_edge_manipulation_curve_history$(EXE_EXT) \
                ex_face_extension$(EXE_EXT) \
                ex_face_extension_overlay$(EXE_EXT) \
                ex_generic_curve_data$(EXE_EXT) \
                ex_global_insertion$(EXE_EXT) \
                ex_global_removal$(EXE_EXT) \
                ex_incremental_insertion$(EXE_EXT) \
                ex_io$(EXE_EXT) \
                ex_io_curve_history$(EXE_EXT) \
                ex_isolated_vertices$(EXE_EXT) \
                ex_observer$(EXE_EXT) \
                ex_overlay$(EXE_EXT) \
                ex_point_location$(EXE_EXT) \
                ex_polylines$(EXE_EXT) \
                ex_predefined_kernel$(EXE_EXT) \
                ex_predefined_kernel_non_intersecting$(EXE_EXT) \
                ex_rational_functions$(EXE_EXT) \
                ex_special_edge_insertion$(EXE_EXT) \
                ex_sweep_line$(EXE_EXT) \
                ex_vertical_ray_shooting$(EXE_EXT) 

ex_aggregated_insertion$(EXE_EXT): ex_aggregated_insertion$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_aggregated_insertion ex_aggregated_insertion$(OBJ_EXT) $(LDFLAGS)

ex_batched_point_location$(EXE_EXT): ex_batched_point_location$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_batched_point_location ex_batched_point_location$(OBJ_EXT) $(LDFLAGS)

ex_bgl_dual_adapter$(EXE_EXT): ex_bgl_dual_adapter$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_bgl_dual_adapter ex_bgl_dual_adapter$(OBJ_EXT) $(LDFLAGS)

ex_bgl_primal_adapter$(EXE_EXT): ex_bgl_primal_adapter$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_bgl_primal_adapter ex_bgl_primal_adapter$(OBJ_EXT) $(LDFLAGS)

ex_circles$(EXE_EXT): ex_circles$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_circles ex_circles$(OBJ_EXT) $(LDFLAGS)

ex_circular_arcs$(EXE_EXT): ex_circular_arcs$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_circular_arcs ex_circular_arcs$(OBJ_EXT) $(LDFLAGS)

ex_conic_multiplicities$(EXE_EXT): ex_conic_multiplicities$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_conic_multiplicities ex_conic_multiplicities$(OBJ_EXT) $(LDFLAGS)

ex_conics$(EXE_EXT): ex_conics$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_conics ex_conics$(OBJ_EXT) $(LDFLAGS)

ex_consolidated_curve_data$(EXE_EXT): ex_consolidated_curve_data$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_consolidated_curve_data ex_consolidated_curve_data$(OBJ_EXT) $(LDFLAGS)

ex_curve_history$(EXE_EXT): ex_curve_history$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_curve_history ex_curve_history$(OBJ_EXT) $(LDFLAGS)

ex_dcel_extension$(EXE_EXT): ex_dcel_extension$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_dcel_extension ex_dcel_extension$(OBJ_EXT) $(LDFLAGS)

ex_dcel_extension_io$(EXE_EXT): ex_dcel_extension_io$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_dcel_extension_io ex_dcel_extension_io$(OBJ_EXT) $(LDFLAGS)

ex_edge_insertion$(EXE_EXT): ex_edge_insertion$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_edge_insertion ex_edge_insertion$(OBJ_EXT) $(LDFLAGS)

ex_edge_manipulation$(EXE_EXT): ex_edge_manipulation$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_edge_manipulation ex_edge_manipulation$(OBJ_EXT) $(LDFLAGS)

ex_edge_manipulation_curve_history$(EXE_EXT): ex_edge_manipulation_curve_history$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_edge_manipulation_curve_history ex_edge_manipulation_curve_history$(OBJ_EXT) $(LDFLAGS)

ex_face_extension$(EXE_EXT): ex_face_extension$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_face_extension ex_face_extension$(OBJ_EXT) $(LDFLAGS)

ex_face_extension_overlay$(EXE_EXT): ex_face_extension_overlay$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_face_extension_overlay ex_face_extension_overlay$(OBJ_EXT) $(LDFLAGS)

ex_generic_curve_data$(EXE_EXT): ex_generic_curve_data$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_generic_curve_data ex_generic_curve_data$(OBJ_EXT) $(LDFLAGS)

ex_global_insertion$(EXE_EXT): ex_global_insertion$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_global_insertion ex_global_insertion$(OBJ_EXT) $(LDFLAGS)

ex_global_removal$(EXE_EXT): ex_global_removal$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_global_removal ex_global_removal$(OBJ_EXT) $(LDFLAGS)

ex_incremental_insertion$(EXE_EXT): ex_incremental_insertion$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_incremental_insertion ex_incremental_insertion$(OBJ_EXT) $(LDFLAGS)

ex_io$(EXE_EXT): ex_io$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_io ex_io$(OBJ_EXT) $(LDFLAGS)

ex_io_curve_history$(EXE_EXT): ex_io_curve_history$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_io_curve_history ex_io_curve_history$(OBJ_EXT) $(LDFLAGS)

ex_isolated_vertices$(EXE_EXT): ex_isolated_vertices$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_isolated_vertices ex_isolated_vertices$(OBJ_EXT) $(LDFLAGS)

ex_observer$(EXE_EXT): ex_observer$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_observer ex_observer$(OBJ_EXT) $(LDFLAGS)

ex_overlay$(EXE_EXT): ex_overlay$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_overlay ex_overlay$(OBJ_EXT) $(LDFLAGS)

ex_point_location$(EXE_EXT): ex_point_location$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_point_location ex_point_location$(OBJ_EXT) $(LDFLAGS)

ex_polylines$(EXE_EXT): ex_polylines$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_polylines ex_polylines$(OBJ_EXT) $(LDFLAGS)

ex_predefined_kernel$(EXE_EXT): ex_predefined_kernel$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_predefined_kernel ex_predefined_kernel$(OBJ_EXT) $(LDFLAGS)

ex_predefined_kernel_non_intersecting$(EXE_EXT): ex_predefined_kernel_non_intersecting$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_predefined_kernel_non_intersecting ex_predefined_kernel_non_intersecting$(OBJ_EXT) $(LDFLAGS)

ex_rational_functions$(EXE_EXT): ex_rational_functions$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_rational_functions ex_rational_functions$(OBJ_EXT) $(LDFLAGS)

ex_special_edge_insertion$(EXE_EXT): ex_special_edge_insertion$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_special_edge_insertion ex_special_edge_insertion$(OBJ_EXT) $(LDFLAGS)

ex_sweep_line$(EXE_EXT): ex_sweep_line$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_sweep_line ex_sweep_line$(OBJ_EXT) $(LDFLAGS)

ex_vertical_ray_shooting$(EXE_EXT): ex_vertical_ray_shooting$(OBJ_EXT)
	$(CGAL_CXX) $(LIBPATH) $(EXE_OPT)ex_vertical_ray_shooting ex_vertical_ray_shooting$(OBJ_EXT) $(LDFLAGS)

clean: \
                   ex_aggregated_insertion.clean \
                   ex_batched_point_location.clean \
                   ex_bgl_dual_adapter.clean \
                   ex_bgl_primal_adapter.clean \
                   ex_circles.clean \
                   ex_circular_arcs.clean \
                   ex_conic_multiplicities.clean \
                   ex_conics.clean \
                   ex_consolidated_curve_data.clean \
                   ex_curve_history.clean \
                   ex_dcel_extension.clean \
                   ex_dcel_extension_io.clean \
                   ex_edge_insertion.clean \
                   ex_edge_manipulation.clean \
                   ex_edge_manipulation_curve_history.clean \
                   ex_face_extension.clean \
                   ex_face_extension_overlay.clean \
                   ex_generic_curve_data.clean \
                   ex_global_insertion.clean \
                   ex_global_removal.clean \
                   ex_incremental_insertion.clean \
                   ex_io.clean \
                   ex_io_curve_history.clean \
                   ex_isolated_vertices.clean \
                   ex_observer.clean \
                   ex_overlay.clean \
                   ex_point_location.clean \
                   ex_polylines.clean \
                   ex_predefined_kernel.clean \
                   ex_predefined_kernel_non_intersecting.clean \
                   ex_rational_functions.clean \
                   ex_special_edge_insertion.clean \
                   ex_sweep_line.clean \
                   ex_vertical_ray_shooting.clean 

#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C$(OBJ_EXT):
	$(CGAL_CXX) $(CXXFLAGS) $(OBJ_OPT) $<

