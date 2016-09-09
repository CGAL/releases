# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Kinetic_data_structures_example )

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.5)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
 
if ( COMMAND cmake_policy )
  cmake_policy( SET CMP0003 NEW )  
endif()
 
find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE ../../include)

  create_single_source_cgal_program( "Kinetic_Delaunay_triangulation_2.cpp" )
  create_single_source_cgal_program( "Kinetic_Delaunay_triangulation_3.cpp" )
  create_single_source_cgal_program( "Kinetic_insert_event.cpp" )
  create_single_source_cgal_program( "Kinetic_regular_triangulation_3.cpp" )
  create_single_source_cgal_program( "Kinetic_sort.cpp" )
  create_single_source_cgal_program( "Kinetic_sweepline.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

