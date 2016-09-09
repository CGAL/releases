# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Matrix_search_example )

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.5)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
 
if ( COMMAND cmake_policy )
  cmake_policy( SET CMP0003 NEW )  
endif()
 
find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  create_single_source_cgal_program( "all_furthest_neighbors_2.cpp" )
  create_single_source_cgal_program( "extremal_polygon_2_area.cpp" )
  create_single_source_cgal_program( "extremal_polygon_2_perimeter.cpp" )
  create_single_source_cgal_program( "rectangular_p_center_2.cpp" )
  create_single_source_cgal_program( "sorted_matrix_search.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

