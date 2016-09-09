# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Generator_example )

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.5)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
 
if ( COMMAND cmake_policy )
  cmake_policy( SET CMP0003 NEW )  
endif()
 
find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  create_single_source_cgal_program( "random_convex_set.cpp" )
  create_single_source_cgal_program( "random_degenerate_point_set.cpp" )
  create_single_source_cgal_program( "random_grid.cpp" )
  create_single_source_cgal_program( "random_polygon.cpp" )
  create_single_source_cgal_program( "random_polygon2.cpp" )
  create_single_source_cgal_program( "random_segments1.cpp" )
  create_single_source_cgal_program( "random_segments2.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

