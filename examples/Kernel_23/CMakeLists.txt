# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Kernel_23_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "MyKernel.cpp" )
  create_single_source_cgal_program( "cartesian_converter.cpp" )
  create_single_source_cgal_program( "exact.cpp" )
  create_single_source_cgal_program( "intersections.cpp" )
  create_single_source_cgal_program( "points_and_segment.cpp" )
  create_single_source_cgal_program( "surprising.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

