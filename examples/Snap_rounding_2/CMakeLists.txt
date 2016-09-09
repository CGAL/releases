# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Snap_rounding_2_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "snap_rounding.cpp" )
  create_single_source_cgal_program( "snap_rounding_data.cpp" )
  create_single_source_cgal_program( "snap_rounding_to_integer.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

