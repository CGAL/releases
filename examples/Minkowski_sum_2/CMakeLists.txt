# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Minkowski_sum_2_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "approx_inset.cpp" )
  create_single_source_cgal_program( "approx_offset.cpp" )
  create_single_source_cgal_program( "exact_inset.cpp" )
  create_single_source_cgal_program( "exact_offset.cpp" )
  create_single_source_cgal_program( "sum_by_decomposition.cpp" )
  create_single_source_cgal_program( "sum_of_holes.cpp" )
  create_single_source_cgal_program( "sum_triangle_square.cpp" )
  create_single_source_cgal_program( "sum_with_holes.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

