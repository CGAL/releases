cmake_minimum_required(VERSION 3.12...3.29)
project(Surface_mesh_topology_Examples)

find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt6)

# add_definitions(-DCGAL_TRACE_PATH_TESTS)
# add_definitions(-DCGAL_TRACE_CMAP_TOOLS)
# add_definitions("-Wall -Wextra")
# add_definitions("-D_GLIBCXX_DEBUG")

set(SOURCE_FILES
  edgewidth_lcc.cpp
  edgewidth_surface_mesh.cpp
  facewidth.cpp
  map_2_constructor.cpp
  open_path_homotopy.cpp
  path_homotopy.cpp
  path_homotopy_double_torus.cpp
  path_homotopy_torus.cpp
  path_homotopy_with_sm_and_polyhedron.cpp
  path_homotopy_with_symbols_2.cpp
  path_homotopy_with_symbols.cpp
  path_simplicity_double_torus.cpp
  path_simplicity_double_torus_2.cpp
  shortest_noncontractible_cycle_2.cpp
  shortest_noncontractible_cycle.cpp
  unsew_edgewidth_repeatedly.cpp
  )

foreach(cppfile ${SOURCE_FILES})
  create_single_source_cgal_program("${cppfile}")
endforeach()

if(CGAL_Qt6_FOUND)
  target_link_libraries(edgewidth_lcc PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(edgewidth_surface_mesh PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(facewidth PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(open_path_homotopy PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(path_homotopy PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(path_homotopy_double_torus PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(path_homotopy_torus PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(path_homotopy_with_sm_and_polyhedron PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(path_simplicity_double_torus PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(path_simplicity_double_torus_2 PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(shortest_noncontractible_cycle_2 PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(shortest_noncontractible_cycle PUBLIC CGAL::CGAL_Basic_viewer)
  target_link_libraries(unsew_edgewidth_repeatedly PUBLIC CGAL::CGAL_Basic_viewer)
endif()
