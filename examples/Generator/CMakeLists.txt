# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Generator_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "ball_d.cpp" )
  create_single_source_cgal_program( "combination_enumerator.cpp" )
  create_single_source_cgal_program( "cube_d.cpp" )
  create_single_source_cgal_program( "grid_d.cpp" )
  create_single_source_cgal_program( "name_pairs.cpp" )
  create_single_source_cgal_program( "random_convex_hull_2.cpp" )
  create_single_source_cgal_program( "random_convex_set.cpp" )
  create_single_source_cgal_program( "random_degenerate_point_set.cpp" )
  create_single_source_cgal_program( "random_grid.cpp" )
  create_single_source_cgal_program( "random_points_tetrahedron_and_triangle_3.cpp" )
  create_single_source_cgal_program( "random_points_triangle_2.cpp" )
  create_single_source_cgal_program( "random_polygon.cpp" )
  create_single_source_cgal_program( "random_polygon2.cpp" )
  create_single_source_cgal_program( "random_segments1.cpp" )
  create_single_source_cgal_program( "random_segments2.cpp" )
  create_single_source_cgal_program( "sphere_d.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

