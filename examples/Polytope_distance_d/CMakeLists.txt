# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Polytope_distance_d_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "all_furthest_neighbors_2.cpp" )
  create_single_source_cgal_program( "polytope_distance_d.cpp" )
  create_single_source_cgal_program( "polytope_distance_d_fast_exact.cpp" )
  create_single_source_cgal_program( "width_simplex.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

